#include "native_private_snapshots.hpp"
#include "../hdrs/Gd__gd_core__CoreItemData.hpp"
#include <cmath>
#include <typeinfo>
#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#include "../../native_event_kernel.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core_items__Gems__Gem.hpp"
#include "../hdrs/Gd__gd_core__CoreContext.hpp"
#include "../hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "../hdrs/Gd__gd_core__CoreItem.hpp"
#include "../hdrs/Gd__gd_core__BloodGoobert.hpp"
#include "../hdrs/Gd__gd_core__CoreBuff.hpp"
#include "../hdrs/Gd__gd_core__CoreItem__INNER__CoreSignalConnection.hpp"
#include "../hdrs/Gd__gd_core__CoreItem.hpp"
#include "../hdrs/Gd__gd_core__DancingDragon.hpp"
#include "../hdrs/Gd__gd_core__FannyPack.hpp"
#include "../hdrs/Gd__gd_core__HolyArmor.hpp"
#include "../hdrs/Gd__gd_core__ManaOrb.hpp"
#include "../hdrs/Gd__gd_core__PoisonGoobert.hpp"
#include "../hdrs/Gd__gd_core__SpectralDagger.hpp"
#include "../hdrs/Gd__gd_core_items__StoneSkinPotion.hpp"
#include "../hdrs/Gd__gd_core__WoodenSword.hpp"
#include "../hdrs/Gd__gd_core_items__Dagger.hpp"
#include "../hdrs/Gd__gd_core_items__Crown.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmethystWhelp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ArmoredCouragePuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Bewitchment.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BrassKnuckles.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cheese.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChessMaster.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Daggerang.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DragonscaleArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Everburning.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FriendlyFire.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Hardwood.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__InnerPower.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LightningStaff.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Markswoman.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__OilLamp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Pop.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertEngineer.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SapphireEgg.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SliceofBread.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpellScrollIce.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StoneBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ThunderDrake.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Wand.hpp"
#include "../hdrs/Gd__gd_core_items__FlyAgaric.hpp"
#include "../hdrs/Gd__gd_core_items__HeroicPotion.hpp"
#include "../hdrs/Gd__gd_core_items__ManaOrb.hpp"
#include "../hdrs/Gd__gd_core_items__ProtectivePurse.hpp"
#include "../hdrs/Gd__gd_core_items__StrongDemonicFlask.hpp"
#include "../hdrs/Gd__gd_core_items__WoodenSword.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"", 0u, 2166136261u},
    {"onCombatStart", 13u, 1517519996u},
    {"getGatedDescriptor", 18u, 2615109165u},
    {"getReplaceDescriptor", 20u, 3678354556u},
    {"onChargeReceived", 16u, 1513811791u},
    {"onChargeLeft", 12u, 164060557u},
    {"chargedItemStatChange", 21u, 700881358u},
    {"onPreDealDamage_early", 21u, 1141032398u},
    {"onPreDealDamage_late", 20u, 4290954099u},
    {"onDealtDamage", 13u, 1467360435u},
    {"getTriggerPriority", 18u, 380150781u},
    {"used_stamina", 12u, 2801525262u},
    {"flickerPlayAni", 14u, 3538297413u},
    {"FLKREG", 6u, 3353518206u},
    {"/ot", 3u, 3885608693u},
    {"st=", 3u, 290213357u},
    {"ITEMREADY", 9u, 1257168517u},
    {"FLKFIRE", 7u, 153382368u},
    {"TRIG", 4u, 2113748091u},
    {"tt=", 3u, 3962276952u},
    {" cd=", 4u, 3284839575u},
    {" spd=", 5u, 2399789615u},
    {" t=", 3u, 157815812u},
    {"CDX", 3u, 1062646318u},
    {"t=", 2u, 340066234u},
    {"doCooldownEffect", 16u, 2915457452u},
    {"activated", 9u, 2866667388u},
    {"ANIM", 4u, 3412022864u},
    {"hit=", 4u, 146314677u},
    {"Hammer", 6u, 3178970599u},
    {"ROLLW", 5u, 87484651u},
    {"ch=", 3u, 1099301385u},
    {"res=", 4u, 2713504428u},
    {"gave_block", 10u, 905150934u},
    {"attacked", 8u, 3381721668u},
    {"pre_deal_damage_early", 21u, 2143897571u},
    {"pre_deal_damage_late", 20u, 1012238672u},
    {"dealt_damage", 12u, 3227693047u},
    {"isAffectingDistinct", 19u, 724237616u},
    {"affectsEmpty", 12u, 1861735642u},
    {"SPD+", 4u, 166051111u},
    {"@", 1u, 3305896031u},
    {" ot=", 4u, 675800099u},
    {"now=", 4u, 3650530302u},
    {"-", 1u, 671913016u},
    {"canAffect", 9u, 3127812344u},
    {"canAffect_secondary", 19u, 676391793u},
    {"canAffect_tertiary", 18u, 614928355u},
    {"canAffect_lightning", 19u, 1897734309u},
    {"heal", 4u, 979982427u},
    {"lifesteal", 9u, 1515578962u},
    {"maxhealth", 9u, 429334299u},
    {"onChargeEnteredCell", 19u, 244630983u},
    {"CHRG", 4u, 2696917545u},
    {"last=", 5u, 1619476652u},
    {"null", 4u, 1996966820u},
    {" cur=", 5u, 6565546u},
    {" del=", 5u, 484259719u},
    {" add=", 5u, 2193804165u},
    {"Items/Item.gd:5642", 18u, 1241571835u},
    {"sort", 4u, 69978321u},
    {"LABEL", 5u, 1625091293u},
    {"getAffectedCellsAfterRotate_primary", 35u, 3161798524u},
    {"getAffectedCellsAfterRotate_secondary", 37u, 1803264340u},
    {"reactToItemTypeChange", 21u, 260162482u},
    {"ready_deferred", 14u, 4137164438u},
    {"MiniActivate_consumed", 21u, 1639018722u},
    {"MiniActivate", 12u, 1297821147u},
    {"rotateTo", 8u, 1542854799u},
    {"Activate", 8u, 999227792u},
    {"dam", 3u, 4031722721u},
    {"vampirism", 9u, 773404377u},
    {"gain", 4u, 458499838u},
    {"SRC", 3u, 370604265u},
    {"gain_label", 10u, 2477846011u},
    {"partial", 7u, 3310188186u},
    {"amt", 3u, 556245093u},
    {"lose", 4u, 3509868664u},
    {"(%s@%s)", 7u, 3652594408u},
    {"BLND", 4u, 1836659873u},
    {"p", 1u, 4111221743u},
    {" ty", 3u, 3311905016u},
    {" ", 1u, 621580159u},
    {"len=", 4u, 3677818403u},
    {" ntp=", 5u, 619456614u},
    {" tm=", 4u, 2271234795u},
    {"/", 1u, 705468254u},
    {" fr=", 4u, 4290167426u},
    {"fire", 4u, 2393577177u},
    {"timeout", 7u, 2549515144u},
    {"rearm", 5u, 1445478314u},
    {"delay=", 6u, 4185901951u},
    {" et=", 4u, 3964192169u},
    {" now=", 5u, 1913828892u},
    {"character_heat_changed", 22u, 2413560104u},
    {"onHeatChanged", 13u, 775078454u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckyChanged", 14u, 1760969932u},
    {"Bagtacular", 10u, 2131747329u},
    {"speed", 5u, 2072037248u},
    {"onItemActivated", 15u, 1109670618u},
    {"character_mana_changed", 22u, 798563205u},
    {"onManaChanged", 13u, 3105672029u},
    {"character_block_changed", 23u, 4278945901u},
    {"onBlockChanged", 14u, 2151465311u},
    {"character_stunned", 17u, 4164697708u},
    {"onStun", 6u, 2496468248u},
    {"checkTrigger", 12u, 3751686889u},
    {"character_invulnerable_end", 26u, 3350240732u},
    {"onInvuEnded", 11u, 2135122486u},
    {"dur_invu", 8u, 277695711u},
    {"BuffTimer", 9u, 194754125u},
    {"buffEnded", 9u, 3457903416u},
    {"mana", 4u, 3650585354u},
    {"$n_nature", 9u, 3887268331u},
    {"$n_dark", 7u, 3365736372u},
    {"$n_ice", 6u, 1331838383u},
    {"n_nature", 8u, 233140773u},
    {"n_dark", 6u, 2718798678u},
    {"n_ice", 5u, 2788820689u},
    {"manat", 5u, 126091098u},
    {"debuffs", 7u, 504032524u},
    {"poison", 6u, 3470992305u},
    {"blind", 5u, 274826164u},
    {"cold", 4u, 3930381583u},
    {"dur_stun", 8u, 1388942617u},
    {"battle_rage_started", 19u, 3997014835u},
    {"onBattleRageStarted", 19u, 3330696088u},
    {"battle_rage_ended", 17u, 4230921894u},
    {"onBattleRageEnded", 17u, 1252110145u},
    {"Chess Board", 11u, 1363195651u},
    {"stamina", 7u, 3875003702u},
    {"Flame", 5u, 739594656u},
    {"heat", 4u, 577319571u},
    {"Burning Sword", 13u, 1910756649u},
    {"Burning Blade", 13u, 2424721050u},
    {"onLuckChanged", 13u, 1398589215u},
    {"character_empower_changed", 25u, 2356601027u},
    {"onEmpowerChanged", 16u, 1778241301u},
    {"luck", 4u, 4145017712u},
    {"empower", 7u, 2037162760u},
    {"healamp", 7u, 54482251u},
    {"max1", 4u, 2641074168u},
    {"max2", 4u, 2691407025u},
    {"charge_emitted", 14u, 395874890u},
    {"dur", 3u, 3509645056u},
    {"dam_flat", 8u, 1144621229u},
    {"dam_tile", 8u, 1425854686u},
    {"num", 3u, 242376115u},
    {"acc", 3u, 1112172186u},
    {"accuracy", 8u, 1889185700u},
    {"max", 3u, 3617776409u},
    {"regen", 5u, 16724762u},
    {"dambonus", 8u, 2769252496u},
    {"staminat", 8u, 3660664550u},
    {"pre_take_damage_late", 20u, 571519801u},
    {"onCharacterAttacked", 19u, 1493935206u},
    {"onShieldOrArmorActivated", 24u, 2984191170u},
    {"goldvalue", 9u, 2237135600u},
    {"hits", 4u, 1253637531u},
    {"onBuffEnded", 11u, 3550706743u},
    {"luckt", 5u, 4061892428u},
    {"regent", 6u, 4290639402u},
    {"use", 3u, 1469170932u},
    {"character_pre_use_stamina", 25u, 4061960724u},
    {"checkStamina", 12u, 3432866148u},
    {"[", 1u, 3725336506u},
    {"=", 1u, 940354920u},
    {" p", 2u, 1640314013u},
    {"]", 1u, 3624670792u},
    {",", 1u, 688690635u},
    {"AFFL", 4u, 292489516u},
    {" aff=", 5u, 2844077393u},
    {"block", 5u, 3943480674u},
    {"character_damaged", 17u, 745527748u},
    {"onPlayerDamaged", 15u, 677000780u},
    {"onOpponentDamaged", 17u, 568571164u},
    {"n=", 2u, 271970020u},
    {"HealingReductionTimer", 21u, 2282847931u},
    {"healingReductionTimeout", 23u, 3865003293u},
    {"ownhpt", 6u, 3210869041u},
    {"opphpt", 6u, 4039152086u},
};
}

void Gd__gd_core__CoreItem::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_descriptor = gd::GdVal::null();
    this->f_ctx = gd::GdVal::null();
    this->f_character_ = gd::GdVal::null();
    gd::native_timer_fields_changed(this->rt_ctx_); this->f_inventory = gd::GdVal::null();
    this->f_placed = gd::GdVal::from_bool(false);
    this->f_name = gd::GdVal::from_str(&battle_string_literals[0]);
    this->f_chargeFrame = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2(0.0, 0.0)}));
    this->f_speedScale = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMinDam = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_critChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critSeverity = gd::gd_coerce_float(Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_BASE_CRIT_SEVERITY_0));
    this->f_bonusChancePercent_mult = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusAccuracy = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_buffPowers = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_buffAmplificationChances = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_damageSource = gd::GdVal::null();
    this->f_doubleActivationChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleAttackEffectChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_paramMult = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_paramAdd = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_numCharges = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_chanceRng = gd::GdVal::null();
    this->f_damageRangeRng = gd::GdVal::null();
    this->f_statDisplayOverrides = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_lastActivationTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_activationsThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_lastTriggerTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_triggersThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_triggerTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_iterationCooldown = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_itemMetrics = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::native_timer_fields_changed(this->rt_ctx_); this->f_gems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__grid = gd::GdVal::null();
    this->f__behavior = gd::GdVal::null();
    gd::native_active_cooldown_store(this->rt_ctx_,this->f__cooldown_active,gd::GdVal::from_bool(false));
    this->f__cooldown_changed_epoch = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f__cooldown_blocked_epoch = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_dynamicTypes = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_combatConnections = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_ownerType = gd::gd_coerce_int(gd::GdVal::from_int(13LL));
    this->f_placedByPlayer = gd::GdVal::from_bool(false);
    this->f_dragged = gd::GdVal::from_bool(false);
    this->f_occupiedCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_collisionCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_extensionCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_affectedExtensionCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_affectedCellsCache = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_currentAffectedItems = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_cachedAffectedItems = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_affectedTileCells = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_consumed = gd::GdVal::from_bool(false);
    this->f_hasPreDealDamageEarlyEffect = gd::GdVal::from_bool(false);
    this->f_hasPreDealDamageLateEffect = gd::GdVal::from_bool(false);
    this->f_hasDealtDamageEffect = gd::GdVal::from_bool(false);
    this->f_hasOnChargeReceivedEffect = gd::GdVal::from_bool(false);
    this->f_hasOnChargeLeftEffect = gd::GdVal::from_bool(false);
    // Native bridge items live until the battle arena resets. Other contexts keep arena headers.
    if (gd_ctx.native_inline_timer_headers && !this->native_timer_header_used_ &&
            gd_ctx.arena.owns_storage(this, sizeof(*this))) {
        this->native_timer_header_used_ = true;
        gd::native_timer_fields_changed(this->rt_ctx_); this->f_timers = gd::GdVal::from_arr(&this->native_timer_header_);
    } else {
        gd::native_timer_fields_changed(this->rt_ctx_); this->f_timers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    this->f_buffLabelPositionTimestamps = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_float(0.0), gd::GdVal::from_float(0.0), gd::GdVal::from_float(0.0), gd::GdVal::from_float(0.0), gd::GdVal::from_float(0.0)}));
    this->f_replacementPending = gd::GdVal::from_bool(false);
    this->f_faceDirection = gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP));
    this->f_rotation = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
}
const gd::GdClassMeta* Gd__gd_core__CoreItem::meta() const { return &META_Gd__gd_core__CoreItem; }
gd::GdVal Gd__gd_core__CoreItem::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_BASE_CRIT_SEVERITY_0: return gd::GdVal::from_float(2.0);
        case SYM_GEN_cdEncodingFactor_1: return gd::GdVal::from_float(100000.0);
        case SYM_GEN_SELF_BEHAVIOR_METHODS_61: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(&battle_string_literals[1]), gd::GdVal::from_str(&battle_string_literals[2]), gd::GdVal::from_str(&battle_string_literals[3]), gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_str(&battle_string_literals[5]), gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_str(&battle_string_literals[7]), gd::GdVal::from_str(&battle_string_literals[8]), gd::GdVal::from_str(&battle_string_literals[9])}));
        case SYM_GEN_CoreElectricalCharge_507: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge);
        case SYM_GEN_CoreSignalConnection_508: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreItem::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_BASE_CRIT_SEVERITY_0: out = gd::GdVal::from_float(2.0); return true;
        case SYM_GEN_cdEncodingFactor_1: out = gd::GdVal::from_float(100000.0); return true;
        case SYM_GEN_CoreElectricalCharge_507: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge); return true;
        case SYM_GEN_CoreSignalConnection_508: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreItem::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_descriptor_2: out = this->f_descriptor; return true;
        case SYM_GEN_ctx_3: out = this->f_ctx; return true;
        case SYM_GEN_character__4: out = this->f_character_; return true;
        case SYM_GEN_inventory_5: out = this->f_inventory; return true;
        case SYM_GEN_placed_6: out = this->f_placed; return true;
        case SYM_GEN_name_7: out = this->f_name; return true;
        case SYM_GEN_chargeFrame_8: out = this->f_chargeFrame; return true;
        case SYM_GEN_speedScale_9: out = this->f_speedScale; return true;
        case SYM_GEN_bonusMaxDam_10: out = this->f_bonusMaxDam; return true;
        case SYM_GEN_bonusMinDam_11: out = this->f_bonusMinDam; return true;
        case SYM_GEN_removableDam_12: out = this->f_removableDam; return true;
        case SYM_GEN_bonusDamageFactor_13: out = this->f_bonusDamageFactor; return true;
        case SYM_GEN_staminaFactor_14: out = this->f_staminaFactor; return true;
        case SYM_GEN_critChancePercent_15: out = this->f_critChancePercent; return true;
        case SYM_GEN_critTokens_16: out = this->f_critTokens; return true;
        case SYM_GEN_critSeverity_17: out = this->f_critSeverity; return true;
        case SYM_GEN_bonusChancePercent_mult_18: out = this->f_bonusChancePercent_mult; return true;
        case SYM_GEN_bonusChancePercent_additive1_19: out = this->f_bonusChancePercent_additive1; return true;
        case SYM_GEN_bonusChancePercent_additive2_20: out = this->f_bonusChancePercent_additive2; return true;
        case SYM_GEN_bonusAccuracy_21: out = this->f_bonusAccuracy; return true;
        case SYM_GEN_buffPowers_22: out = this->f_buffPowers; return true;
        case SYM_GEN_buffAmplificationChances_23: out = this->f_buffAmplificationChances; return true;
        case SYM_GEN_damageSource_24: out = this->f_damageSource; return true;
        case SYM_GEN_doubleActivationChance_25: out = this->f_doubleActivationChance; return true;
        case SYM_GEN_doubleAttackEffectChance_26: out = this->f_doubleAttackEffectChance; return true;
        case SYM_GEN_paramMult_27: out = this->f_paramMult; return true;
        case SYM_GEN_paramAdd_28: out = this->f_paramAdd; return true;
        case SYM_GEN_numCharges_29: out = this->f_numCharges; return true;
        case SYM_GEN_baseCooldownOverride_30: out = this->f_baseCooldownOverride; return true;
        case SYM_GEN_chanceRng_31: out = this->f_chanceRng; return true;
        case SYM_GEN_damageRangeRng_32: out = this->f_damageRangeRng; return true;
        case SYM_GEN_statDisplayOverrides_33: out = this->f_statDisplayOverrides; return true;
        case SYM_GEN_lastActivationTime_34: out = this->f_lastActivationTime; return true;
        case SYM_GEN_activationsThisFrame_35: out = this->f_activationsThisFrame; return true;
        case SYM_GEN_lastTriggerTime_36: out = this->f_lastTriggerTime; return true;
        case SYM_GEN_triggersThisFrame_37: out = this->f_triggersThisFrame; return true;
        case SYM_GEN_triggerTime_38: out = this->f_triggerTime; return true;
        case SYM_GEN_iterationCooldown_39: out = this->f_iterationCooldown; return true;
        case SYM_GEN_itemMetrics_40: out = this->f_itemMetrics; return true;
        case SYM_GEN_gems_41: out = this->f_gems; return true;
        case SYM_GEN__grid_42: out = this->f__grid; return true;
        case SYM_GEN__behavior_43: out = this->f__behavior; return true;
        case SYM_GEN__cooldown_active_44: out = this->f__cooldown_active; return true;
        case SYM_GEN__cooldown_changed_epoch_45: out = this->f__cooldown_changed_epoch; return true;
        case SYM_GEN__cooldown_blocked_epoch_46: out = this->f__cooldown_blocked_epoch; return true;
        case SYM_GEN_dynamicTypes_47: out = this->f_dynamicTypes; return true;
        case SYM_GEN_combatConnections_48: out = this->f_combatConnections; return true;
        case SYM_GEN_ownerType_49: out = this->f_ownerType; return true;
        case SYM_GEN_placedByPlayer_50: out = this->f_placedByPlayer; return true;
        case SYM_GEN_dragged_51: out = this->f_dragged; return true;
        case SYM_GEN_occupiedCells_52: out = this->f_occupiedCells; return true;
        case SYM_GEN_collisionCells_53: out = this->f_collisionCells; return true;
        case SYM_GEN_extensionCells_54: out = this->f_extensionCells; return true;
        case SYM_GEN_affectedExtensionCells_55: out = this->f_affectedExtensionCells; return true;
        case SYM_GEN_affectedCellsCache_56: out = this->f_affectedCellsCache; return true;
        case SYM_GEN_currentAffectedItems_57: out = this->f_currentAffectedItems; return true;
        case SYM_GEN_cachedAffectedItems_58: out = this->f_cachedAffectedItems; return true;
        case SYM_GEN_affectedTileCells_59: out = this->f_affectedTileCells; return true;
        case SYM_GEN_consumed_60: out = this->f_consumed; return true;
        case SYM_GEN_hasPreDealDamageEarlyEffect_62: out = this->f_hasPreDealDamageEarlyEffect; return true;
        case SYM_GEN_hasPreDealDamageLateEffect_63: out = this->f_hasPreDealDamageLateEffect; return true;
        case SYM_GEN_hasDealtDamageEffect_64: out = this->f_hasDealtDamageEffect; return true;
        case SYM_GEN_hasOnChargeReceivedEffect_65: out = this->f_hasOnChargeReceivedEffect; return true;
        case SYM_GEN_hasOnChargeLeftEffect_66: out = this->f_hasOnChargeLeftEffect; return true;
        case SYM_GEN_timers_67: out = this->f_timers; return true;
        case SYM_GEN_buffLabelPositionTimestamps_68: out = this->f_buffLabelPositionTimestamps; return true;
        case SYM_GEN_replacementPending_69: out = this->f_replacementPending; return true;
        case SYM_GEN_faceDirection_70: out = this->f_faceDirection; return true;
        case SYM_GEN_rotation_71: out = this->f_rotation; return true;
        case SYM_GEN_CoreElectricalCharge_507: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge); return true;
        case SYM_GEN_CoreSignalConnection_508: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection); return true;
        case SYM_GEN_BASE_CRIT_SEVERITY_0: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_cdEncodingFactor_1: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_SELF_BEHAVIOR_METHODS_61: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_descriptor_2: this->f_descriptor = val; return true;
        case SYM_GEN_ctx_3: this->f_ctx = val; return true;
        case SYM_GEN_character__4: this->f_character_ = val; return true;
        case SYM_GEN_inventory_5: gd::native_timer_fields_changed(this->rt_ctx_); this->f_inventory = val; return true;
        case SYM_GEN_placed_6: this->f_placed = val; return true;
        case SYM_GEN_name_7: this->f_name = val; return true;
        case SYM_GEN_chargeFrame_8: this->f_chargeFrame = val; return true;
        case SYM_GEN_speedScale_9: this->f_speedScale = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusMaxDam_10: this->f_bonusMaxDam = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusMinDam_11: this->f_bonusMinDam = gd::gd_coerce_float(val); return true;
        case SYM_GEN_removableDam_12: this->f_removableDam = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusDamageFactor_13: this->f_bonusDamageFactor = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaFactor_14: this->f_staminaFactor = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critChancePercent_15: this->f_critChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critTokens_16: this->f_critTokens = gd::gd_coerce_int(val); return true;
        case SYM_GEN_critSeverity_17: this->f_critSeverity = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusChancePercent_mult_18: this->f_bonusChancePercent_mult = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusChancePercent_additive1_19: this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusChancePercent_additive2_20: this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusAccuracy_21: this->f_bonusAccuracy = gd::gd_coerce_float(val); return true;
        case SYM_GEN_buffPowers_22: this->f_buffPowers = val; return true;
        case SYM_GEN_buffAmplificationChances_23: this->f_buffAmplificationChances = val; return true;
        case SYM_GEN_damageSource_24: this->f_damageSource = val; return true;
        case SYM_GEN_doubleActivationChance_25: this->f_doubleActivationChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_doubleAttackEffectChance_26: this->f_doubleAttackEffectChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_paramMult_27: this->f_paramMult = val; return true;
        case SYM_GEN_paramAdd_28: this->f_paramAdd = val; return true;
        case SYM_GEN_numCharges_29: this->f_numCharges = gd::gd_coerce_int(val); return true;
        case SYM_GEN_baseCooldownOverride_30: this->f_baseCooldownOverride = gd::gd_coerce_float(val); return true;
        case SYM_GEN_chanceRng_31: this->f_chanceRng = val; return true;
        case SYM_GEN_damageRangeRng_32: this->f_damageRangeRng = val; return true;
        case SYM_GEN_statDisplayOverrides_33: this->f_statDisplayOverrides = val; return true;
        case SYM_GEN_lastActivationTime_34: this->f_lastActivationTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_activationsThisFrame_35: this->f_activationsThisFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_lastTriggerTime_36: this->f_lastTriggerTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_triggersThisFrame_37: this->f_triggersThisFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_triggerTime_38: this->f_triggerTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_iterationCooldown_39: this->f_iterationCooldown = gd::gd_coerce_float(val); return true;
        case SYM_GEN_itemMetrics_40: this->f_itemMetrics = val; return true;
        case SYM_GEN_gems_41: gd::native_timer_fields_changed(this->rt_ctx_); this->f_gems = val; return true;
        case SYM_GEN__grid_42: this->f__grid = val; return true;
        case SYM_GEN__behavior_43: this->f__behavior = val; return true;
        case SYM_GEN__cooldown_active_44: gd::native_active_cooldown_store(this->rt_ctx_,this->f__cooldown_active,val); return true;
        case SYM_GEN__cooldown_changed_epoch_45: this->f__cooldown_changed_epoch = val; return true;
        case SYM_GEN__cooldown_blocked_epoch_46: this->f__cooldown_blocked_epoch = val; return true;
        case SYM_GEN_dynamicTypes_47: this->f_dynamicTypes = val; return true;
        case SYM_GEN_combatConnections_48: this->f_combatConnections = val; return true;
        case SYM_GEN_ownerType_49: this->f_ownerType = gd::gd_coerce_int(val); return true;
        case SYM_GEN_placedByPlayer_50: this->f_placedByPlayer = val; return true;
        case SYM_GEN_dragged_51: this->f_dragged = val; return true;
        case SYM_GEN_occupiedCells_52: this->f_occupiedCells = val; return true;
        case SYM_GEN_collisionCells_53: this->f_collisionCells = val; return true;
        case SYM_GEN_extensionCells_54: this->f_extensionCells = val; return true;
        case SYM_GEN_affectedExtensionCells_55: this->f_affectedExtensionCells = val; return true;
        case SYM_GEN_affectedCellsCache_56: this->f_affectedCellsCache = val; return true;
        case SYM_GEN_currentAffectedItems_57: this->f_currentAffectedItems = val; return true;
        case SYM_GEN_cachedAffectedItems_58: this->f_cachedAffectedItems = val; return true;
        case SYM_GEN_affectedTileCells_59: this->f_affectedTileCells = val; return true;
        case SYM_GEN_consumed_60: this->f_consumed = val; return true;
        case SYM_GEN_hasPreDealDamageEarlyEffect_62: this->f_hasPreDealDamageEarlyEffect = val; return true;
        case SYM_GEN_hasPreDealDamageLateEffect_63: this->f_hasPreDealDamageLateEffect = val; return true;
        case SYM_GEN_hasDealtDamageEffect_64: this->f_hasDealtDamageEffect = val; return true;
        case SYM_GEN_hasOnChargeReceivedEffect_65: this->f_hasOnChargeReceivedEffect = val; return true;
        case SYM_GEN_hasOnChargeLeftEffect_66: this->f_hasOnChargeLeftEffect = val; return true;
        case SYM_GEN_timers_67: gd::native_timer_fields_changed(this->rt_ctx_); this->f_timers = val; return true;
        case SYM_GEN_buffLabelPositionTimestamps_68: this->f_buffLabelPositionTimestamps = val; return true;
        case SYM_GEN_replacementPending_69: this->f_replacementPending = val; return true;
        case SYM_GEN_faceDirection_70: this->f_faceDirection = gd::gd_coerce_int(val); return true;
        case SYM_GEN_rotation_71: this->f_rotation = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_setup_72: return true;
        case SYM_GEN_hasCharacter_73: return true;
        case SYM_GEN_character_74: return true;
        case SYM_GEN_opponent_75: return true;
        case SYM_GEN_isPlaced_76: return true;
        case SYM_GEN_isCoreItem_77: return true;
        case SYM_GEN_isPlayer_78: return true;
        case SYM_GEN_hasType_79: return true;
        case SYM_GEN_getTypeMultiplicity_80: return true;
        case SYM_GEN_hasTag_81: return true;
        case SYM_GEN_isWeapon_82: return true;
        case SYM_GEN_isBag_83: return true;
        case SYM_GEN_isGem_84: return true;
        case SYM_GEN_isBattleRageItem_85: return true;
        case SYM_GEN_gainsStack_86: return true;
        case SYM_GEN_removesStack_87: return true;
        case SYM_GEN_usesStack_88: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_canDamage_89: return true;
        case SYM_GEN_canBeEmpowered_90: return true;
        case SYM_GEN_canActivate_91: return true;
        case SYM_GEN_getSpeed_92: return true;
        case SYM_GEN_speed_93: return true;
        case SYM_GEN_getStackSpeedMods_94: return true;
        case SYM_GEN_hasCooldown_95: return true;
        case SYM_GEN_isCooldownActive_96: return true;
        case SYM_GEN_setCooldownActive_97: return true;
        case SYM_GEN_activateCooldown_98: return true;
        case SYM_GEN_deactivateCooldown_99: return true;
        case SYM_GEN_getBaseCooldown_100: return true;
        case SYM_GEN_getBaseCooldownIndex_101: return true;
        case SYM_GEN_getCooldown_102: return true;
        case SYM_GEN_getCooldownIndex_103: return true;
        case SYM_GEN_getModifiedCooldown_104: return true;
        case SYM_GEN_getModifiedCooldownIndex_105: return true;
        case SYM_GEN_getCooldownEncoded_106: return true;
        case SYM_GEN_adjustCooldown_107: return true;
        case SYM_GEN_setBaseCooldown_108: return true;
        case SYM_GEN_resetBaseCooldown_109: return true;
        case SYM_GEN_updateBaseCooldown_110: return true;
        case SYM_GEN_getBaseStaminaCost_111: return true;
        case SYM_GEN_getStaminaCost_112: return true;
        case SYM_GEN_isStaminaModified_113: return true;
        case SYM_GEN_isStatModified_114: return true;
        case SYM_GEN_setStat_115: return true;
        case SYM_GEN_useStamina_116: return true;
        case SYM_GEN_drainStamina_117: return true;
        case SYM_GEN_playOutOfStaminaAnimation_118: return true;
        case SYM_GEN_cacheAffectedItemsForCombat_119: return true;
        case SYM_GEN_addToInventory_120: return true;
        case SYM_GEN_registerWithInventory_121: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_preCombatStart_124: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_hasStartofBattle_126: return true;
        case SYM_GEN_combatStart_127: return true;
        case SYM_GEN_postCombatStart_128: return true;
        case SYM_GEN_onPostCombatStart_129: return true;
        case SYM_GEN_repeatCombatStart_130: return true;
        case SYM_GEN_combatEnd_131: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_resetCombatState_133: return true;
        case SYM_GEN_physicsTick_134: return true;
        case SYM_GEN_newItemTimer_135: return true;
        case SYM_GEN_getTimer_136: return true;
        case SYM_GEN__tickTimers_137: return true;
        case SYM_GEN_tickTimersPass_138: return true;
        case SYM_GEN_rebuildTimerSeen_139: return true;
        case SYM_GEN__readyInit_140: return true;
        case SYM_GEN_flickerPlayAni_141: return true;
        case SYM_GEN_checkTriggerCount_142: return true;
        case SYM_GEN_trigger_143: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onAfterEffectFinished_145: return true;
        case SYM_GEN_advanceCooldownPercent_146: return true;
        case SYM_GEN_advanceCooldownSeconds_147: return true;
        case SYM_GEN_playActivationSound_148: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN_activate_150: return true;
        case SYM_GEN_checkActivationLimit_151: return true;
        case SYM_GEN_getBaseMinDamage_152: return true;
        case SYM_GEN_getBaseMaxDamage_153: return true;
        case SYM_GEN_getBaseAverageDamage_154: return true;
        case SYM_GEN_getTypedDamageFactor_155: return true;
        case SYM_GEN_getMinDamage_156: return true;
        case SYM_GEN_getMaxDamage_157: return true;
        case SYM_GEN_getAverageDamage_158: return true;
        case SYM_GEN_randDamage_159: return true;
        case SYM_GEN_getModifiedEffectDamage_160: return true;
        case SYM_GEN_addBonusDamage_161: return true;
        case SYM_GEN_changeVaryingDamage_162: return true;
        case SYM_GEN_addMinDamage_163: return true;
        case SYM_GEN_addMaxDamage_164: return true;
        case SYM_GEN_getRemovableDamage_165: return true;
        case SYM_GEN_removeBonusDamage_166: return true;
        case SYM_GEN_setBonusDamageFactor_167: return true;
        case SYM_GEN_getBaseChance_168: return true;
        case SYM_GEN_getBaseChance2_169: return true;
        case SYM_GEN_applyBonusChance_170: return true;
        case SYM_GEN_getChance_171: return true;
        case SYM_GEN_getChance2_172: return true;
        case SYM_GEN_rollChance_173: return true;
        case SYM_GEN_rollChance2_174: return true;
        case SYM_GEN_addBonusChance_175: return true;
        case SYM_GEN_addBonusChance_additive_176: return true;
        case SYM_GEN_addAccuracy_177: return true;
        case SYM_GEN_getCritChancePercent_178: return true;
        case SYM_GEN_addCritChancePercent_179: return true;
        case SYM_GEN_reduceCritChancePercent_180: return true;
        case SYM_GEN_changeCritChancePercent_181: return true;
        case SYM_GEN_getCritTokens_182: return true;
        case SYM_GEN_addCritTokens_183: return true;
        case SYM_GEN_useCritToken_184: return true;
        case SYM_GEN_addCritSeverity_185: return true;
        case SYM_GEN_getCritSeverity_186: return true;
        case SYM_GEN_rollDoubleAttackEffect_187: return true;
        case SYM_GEN_getP_188: return true;
        case SYM_GEN_getP_m_189: return true;
        case SYM_GEN_getParamModified_190: return true;
        case SYM_GEN_modifyParam_191: return true;
        case SYM_GEN_modifyParam_add_192: return true;
        case SYM_GEN_getBaseAccuracy_193: return true;
        case SYM_GEN_getAccuracy_194: return true;
        case SYM_GEN_getAmplificationChancePercent_195: return true;
        case SYM_GEN_changeAmplificiationChancePercent_196: return true;
        case SYM_GEN_changeAmplificiationChancePercent_allBuffs_197: return true;
        case SYM_GEN_changeAmplificiationChancePercent_allDebuffs_198: return true;
        case SYM_GEN_changeNullifyChancePercent_199: return true;
        case SYM_GEN_giveReflectStacks_200: return true;
        case SYM_GEN_giveStacks_201: return true;
        case SYM_GEN_giveStacksTemporary_202: return true;
        case SYM_GEN_giveBlock_203: return true;
        case SYM_GEN_getBlock_204: return true;
        case SYM_GEN_removeBlock_205: return true;
        case SYM_GEN_loseBlock_206: return true;
        case SYM_GEN_useBlock_207: return true;
        case SYM_GEN_stealStack_208: return true;
        case SYM_GEN_giveSpikes_209: return true;
        case SYM_GEN_giveVampirism_210: return true;
        case SYM_GEN_inflictPoison_211: return true;
        case SYM_GEN_selfInflictPoison_212: return true;
        case SYM_GEN_inflictBlind_213: return true;
        case SYM_GEN_giveRegeneration_214: return true;
        case SYM_GEN_giveLucky_215: return true;
        case SYM_GEN_giveMana_216: return true;
        case SYM_GEN_giveEmpower_217: return true;
        case SYM_GEN_giveHeat_218: return true;
        case SYM_GEN_giveCold_219: return true;
        case SYM_GEN_dealDamage_220: return true;
        case SYM_GEN_dealEffectDamage_221: return true;
        case SYM_GEN_preDealDamage_early_222: return true;
        case SYM_GEN_preDealDamage_late_223: return true;
        case SYM_GEN_dealtDamage_224: return true;
        case SYM_GEN_countDamage_225: return true;
        case SYM_GEN_addMetric_230: return true;
        case SYM_GEN_getMetric_231: return true;
        case SYM_GEN_stackChanged_232: return true;
        case SYM_GEN_staminaChanged_233: return true;
        case SYM_GEN_getName_234: return true;
        case SYM_GEN_getIndex_235: return true;
        case SYM_GEN_getRarity_236: return true;
        case SYM_GEN_getShopChance_237: return true;
        case SYM_GEN_getMainType_238: return true;
        case SYM_GEN_getNumStaticTypes_239: return true;
        case SYM_GEN_getTypes_240: return true;
        case SYM_GEN_hasDynamicType_241: return true;
        case SYM_GEN_addDynamicType_242: return true;
        case SYM_GEN_removeDynamicType_243: return true;
        case SYM_GEN_clearDynamicTypes_244: return true;
        case SYM_GEN_isA_245: return true;
        case SYM_GEN_isNeutral_246: return true;
        case SYM_GEN_isTreasure_247: return true;
        case SYM_GEN_isClassItem_248: return true;
        case SYM_GEN_isSubclassItem_249: return true;
        case SYM_GEN_isOwnable_250: return true;
        case SYM_GEN_isOwnedByOpponent_251: return true;
        case SYM_GEN_isGateItem_252: return true;
        case SYM_GEN_isShowCaseItem_253: return true;
        case SYM_GEN_isAffectingDistinct_254: return true;
        case SYM_GEN_affectsEmpty_255: return true;
        case SYM_GEN_hasOpponent_256: return true;
        case SYM_GEN_getEffectiveOwnerType_257: return true;
        case SYM_GEN_isBaseItem_258: return true;
        case SYM_GEN_isBusy_259: return true;
        case SYM_GEN_isBoundAsIngredient_260: return true;
        case SYM_GEN_getStat_261: return true;
        case SYM_GEN_getP_check_262: return true;
        case SYM_GEN_getP1_263: return true;
        case SYM_GEN_getP2_264: return true;
        case SYM_GEN_getP3_265: return true;
        case SYM_GEN_getP4_266: return true;
        case SYM_GEN_getP5_267: return true;
        case SYM_GEN_getP6_268: return true;
        case SYM_GEN_getP7_269: return true;
        case SYM_GEN_getP8_270: return true;
        case SYM_GEN_getP9_271: return true;
        case SYM_GEN_getP10_272: return true;
        case SYM_GEN_addSpeed_273: return true;
        case SYM_GEN_reduceSpeed_274: return true;
        case SYM_GEN_getDPS_275: return true;
        case SYM_GEN_isDPSModified_276: return true;
        case SYM_GEN_getDamageRange_277: return true;
        case SYM_GEN_isCooldownModified_278: return true;
        case SYM_GEN_isAccuracyModified_279: return true;
        case SYM_GEN_isChance1Modified_280: return true;
        case SYM_GEN_isChance2Modified_281: return true;
        case SYM_GEN_isDamageModified_282: return true;
        case SYM_GEN_getBaseStaminaPerSecond_283: return true;
        case SYM_GEN_getStaminaPerSecond_284: return true;
        case SYM_GEN_isStaminaPerSecondModified_285: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_canAffect_tertiary_288: return true;
        case SYM_GEN_canAffect_lightning_289: return true;
        case SYM_GEN_canAffect_color_290: return true;
        case SYM_GEN_canBlock_291: return true;
        case SYM_GEN_canHealOrLifesteal_292: return true;
        case SYM_GEN_canModifyChance_293: return true;
        case SYM_GEN_canUseStamina_294: return true;
        case SYM_GEN_hasAttackEffect_295: return true;
        case SYM_GEN_gainsBuffs_296: return true;
        case SYM_GEN_usesBuffs_297: return true;
        case SYM_GEN_inflictsDebuffs_298: return true;
        case SYM_GEN_reactsToCharges_299: return true;
        case SYM_GEN_fillUpStamina_300: return true;
        case SYM_GEN_getRelativeOpponentHealth_301: return true;
        case SYM_GEN_getRelativeHealth_302: return true;
        case SYM_GEN_giveBuffPower_303: return true;
        case SYM_GEN_changeHealAmp_304: return true;
        case SYM_GEN_changeStaminaFactor_305: return true;
        case SYM_GEN_addBonusDamageFactor_306: return true;
        case SYM_GEN_reduceBonusDamageFactor_307: return true;
        case SYM_GEN_reduceMinDamage_308: return true;
        case SYM_GEN_reduceMaxDamage_309: return true;
        case SYM_GEN_reduceBonusDamage_310: return true;
        case SYM_GEN_purgeDamage_311: return true;
        case SYM_GEN_giveDoubleActivationChance_312: return true;
        case SYM_GEN_giveDoubleAttackEffectChance_313: return true;
        case SYM_GEN_giveCritTokens_314: return true;
        case SYM_GEN_giveMaxStamina_315: return true;
        case SYM_GEN_giveMaxStaminaTemporary_316: return true;
        case SYM_GEN_giveMaxHealth_317: return true;
        case SYM_GEN_giveStamina_318: return true;
        case SYM_GEN_inflictFatigueDamage_319: return true;
        case SYM_GEN_sendCharge_320: return true;
        case SYM_GEN__chargeInventoryCells_321: return true;
        case SYM_GEN__rotVecQuarterTurns_322: return true;
        case SYM_GEN__chargeEnterCell_323: return true;
        case SYM_GEN_chargeReceived_324: return true;
        case SYM_GEN_chargeLeft_325: return true;
        case SYM_GEN_changeChargedItemStat_326: return true;
        case SYM_GEN_heal_327: return true;
        case SYM_GEN_healthToBlock_328: return true;
        case SYM_GEN_stealLife_329: return true;
        case SYM_GEN_stun_330: return true;
        case SYM_GEN_checkMana_331: return true;
        case SYM_GEN_useMana_332: return true;
        case SYM_GEN_tryUseMana_333: return true;
        case SYM_GEN_removeMana_334: return true;
        case SYM_GEN_giveMana_capped_335: return true;
        case SYM_GEN_removeSpikes_336: return true;
        case SYM_GEN_useSpikes_337: return true;
        case SYM_GEN_loseSpikes_338: return true;
        case SYM_GEN_removeVampirism_339: return true;
        case SYM_GEN_useVampirism_340: return true;
        case SYM_GEN_loseVampirism_341: return true;
        case SYM_GEN_cleansePoison_342: return true;
        case SYM_GEN_selfInflictBlind_343: return true;
        case SYM_GEN_cleanseBlind_344: return true;
        case SYM_GEN_removeRegeneration_345: return true;
        case SYM_GEN_useRegeneration_346: return true;
        case SYM_GEN_tryUseLucky_347: return true;
        case SYM_GEN_loseLucky_348: return true;
        case SYM_GEN_removeLucky_349: return true;
        case SYM_GEN_useLucky_350: return true;
        case SYM_GEN_inflictCold_351: return true;
        case SYM_GEN_cleanseCold_352: return true;
        case SYM_GEN_loseHeat_353: return true;
        case SYM_GEN_useHeat_354: return true;
        case SYM_GEN_loseEmpower_355: return true;
        case SYM_GEN_cleanseRandomDebuffs_356: return true;
        case SYM_GEN_inflictRandomDebuffs_357: return true;
        case SYM_GEN_pickRandomStacks_358: return true;
        case SYM_GEN_pickRandomStacksToGive_359: return true;
        case SYM_GEN_getLeastStacks_360: return true;
        case SYM_GEN_getMostStacks_361: return true;
        case SYM_GEN_getStackFraction_362: return true;
        case SYM_GEN_multiplyBuffsLimit_363: return true;
        case SYM_GEN_removeBuffsFraction_364: return true;
        case SYM_GEN_stealBuffsFraction_365: return true;
        case SYM_GEN_giveLeastBuffs_366: return true;
        case SYM_GEN_giveMostBuffs_367: return true;
        case SYM_GEN_removeMostBuffs_368: return true;
        case SYM_GEN_giveRandomBuffs_369: return true;
        case SYM_GEN_giveAllBuffs_370: return true;
        case SYM_GEN_useRandomBuffs_371: return true;
        case SYM_GEN_removeRandomBuffs_372: return true;
        case SYM_GEN_stealRandomBuff_373: return true;
        case SYM_GEN_connectToCharacterBuffs_374: return true;
        case SYM_GEN_connectToCharacterDebuffs_375: return true;
        case SYM_GEN_connectToOpponentDebuffs_376: return true;
        case SYM_GEN_connectToOpponentBuffs_377: return true;
        case SYM_GEN_getNextFreeLabelPosition_378: return true;
        case SYM_GEN_spawnLabel_379: return true;
        case SYM_GEN_spawnLabel_other_380: return true;
        case SYM_GEN_consume_381: return true;
        case SYM_GEN_setState_382: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_onTemporaryStacksTimeout_384: return true;
        case SYM_GEN_empowerEnd_385: return true;
        case SYM_GEN_hasSockets_386: return true;
        case SYM_GEN_getNumSockets_387: return true;
        case SYM_GEN_initSockets_388: return true;
        case SYM_GEN_getItem_389: return true;
        case SYM_GEN_hasGems_390: return true;
        case SYM_GEN_getGemsOfItems_391: return true;
        case SYM_GEN_getPrice_392: return true;
        case SYM_GEN_getBaseSellPrice_393: return true;
        case SYM_GEN_getSellPrice_394: return true;
        case SYM_GEN_getSalePrice_395: return true;
        case SYM_GEN_setGem_396: return true;
        case SYM_GEN_pushGemsToStorage_397: return true;
        case SYM_GEN_pushItemsInsideToStorage_398: return true;
        case SYM_GEN_returnToSocket_399: return true;
        case SYM_GEN_getOwnOrPlayerInventory_400: return true;
        case SYM_GEN_getCellsForGlobalPositions_401: return true;
        case SYM_GEN_getGlobalPointsForCells_402: return true;
        case SYM_GEN_getGlobalPointsForCells_noRotate_403: return true;
        case SYM_GEN_getCollisionCells_404: return true;
        case SYM_GEN_getExtensionCells_405: return true;
        case SYM_GEN_getCollisionPoints_406: return true;
        case SYM_GEN_getExtensionPoints_407: return true;
        case SYM_GEN_getAffectedCells_tilemap_408: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_409: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_410: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_secondary_411: return true;
        case SYM_GEN_getAffectedCells_noRotate_412: return true;
        case SYM_GEN_getAffectedPoints_413: return true;
        case SYM_GEN_getAffectedCellsInInventory_414: return true;
        case SYM_GEN_getAffectedCellsInInventory_cached_415: return true;
        case SYM_GEN_cacheAffectedCells_416: return true;
        case SYM_GEN_cleanCachedAffectedItems_417: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_getAffectedItems_420: return true;
        case SYM_GEN_getAffectedItems_nocache_421: return true;
        case SYM_GEN_getItemsInAffectedCells_422: return true;
        case SYM_GEN_getItemsInAffectedCells_cached_423: return true;
        case SYM_GEN_countItemsInAffectedCells_cached_424: return true;
        case SYM_GEN_isItemAffected_425: return true;
        case SYM_GEN_getNumEmptyAffectedCells_426: return true;
        case SYM_GEN_getNumAffectedItems_427: return true;
        case SYM_GEN_getFirstAffectedItem_428: return true;
        case SYM_GEN_getNumAffected_type_429: return true;
        case SYM_GEN_getNumDistinctAffectedItems_430: return true;
        case SYM_GEN_getNumAffectedCells_431: return true;
        case SYM_GEN_activateExtendedAffectedCells_432: return true;
        case SYM_GEN_deactivateExtendedAffectedCells_433: return true;
        case SYM_GEN_canAffectDraggedItem_434: return true;
        case SYM_GEN_onAffectedItemAdded_435: return true;
        case SYM_GEN_onAffectedItemRemoved_436: return true;
        case SYM_GEN_onItemAdded_437: return true;
        case SYM_GEN_onItemRemoved_438: return true;
        case SYM_GEN_getNumOccupiedCells_439: return true;
        case SYM_GEN_getNumBagCells_440: return true;
        case SYM_GEN_getNumCells_441: return true;
        case SYM_GEN_getSizeInCells_442: return true;
        case SYM_GEN_getTopLeftCell_443: return true;
        case SYM_GEN_getNormalizedCollisionCells_444: return true;
        case SYM_GEN_canCombine_445: return true;
        case SYM_GEN_prepareReplacement_446: return true;
        case SYM_GEN_finishReplacement_447: return true;
        case SYM_GEN_placeGeneratedItem_448: return true;
        case SYM_GEN_moveTo_449: return true;
        case SYM_GEN_resetZ_450: return true;
        case SYM_GEN_onGateItemRoll_451: return true;
        case SYM_GEN_insertCounter_452: return true;
        case SYM_GEN_queue_free_453: return true;
        case SYM_GEN_shift_454: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_onSold_456: return true;
        case SYM_GEN_reactToItemTypeChange_457: return true;
        case SYM_GEN_onItemTypeChanged_458: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_countAllPlacedOfType_460: return true;
        case SYM_GEN_getTouchedBagsCounted_461: return true;
        case SYM_GEN_getHeightRange_462: return true;
        case SYM_GEN_ready_deferred_463: return true;
        case SYM_GEN_rotationFromFaceDirection_464: return true;
        case SYM_GEN_getFaceDirection_465: return true;
        case SYM_GEN_getGlobalFaceDirection_466: return true;
        case SYM_GEN_setFaceDirectionInstant_467: return true;
        case SYM_GEN_setRotation_468: return true;
        case SYM_GEN_changeAllItemsCritRate_469: return true;
        case SYM_GEN_miniActivate_470: return true;
        case SYM_GEN_previewCellCollision_471: return true;
        case SYM_GEN_previewCells_472: return true;
        case SYM_GEN_previewCanAffect_473: return true;
        case SYM_GEN_rotateRight_474: return true;
        case SYM_GEN_rotateLeft_475: return true;
        case SYM_GEN_rotateTo_476: return true;
        case SYM_GEN_rotateToDeferred_477: return true;
        case SYM_GEN_setFaceDirection_478: return true;
        case SYM_GEN_correctInsideItemFacedirection_479: return true;
        case SYM_GEN_getBagEffect_480: return true;
        case SYM_GEN_getGemData_481: return true;
        case SYM_GEN_setGemData_482: return true;
        case SYM_GEN_reconstructCooldown_483: return true;
        case SYM_GEN_findBondsWithAffectedItems_484: return true;
        case SYM_GEN_rotateProgress_485: return true;
        case SYM_GEN_cacheCollisionCells_486: return true;
        case SYM_GEN_isBaseItemForShopItem_487: return true;
        case SYM_GEN_activateFromEvent_488: return true;
        case SYM_GEN_getNeighborItemsAndGems_489: return true;
        case SYM_GEN_getTouchedBags_490: return true;
        case SYM_GEN_getBusyNeighbors_491: return true;
        case SYM_GEN_getCraftableNeighbors_492: return true;
        case SYM_GEN_isAvailableForCrafting_493: return true;
        case SYM_GEN_getAffectedGoldValue_494: return true;
        case SYM_GEN_countTypes_495: return true;
        case SYM_GEN_hasSameOrientationAsPickup_496: return true;
        case SYM_GEN_getGemsNoNull_497: return true;
        case SYM_GEN_getGems_498: return true;
        case SYM_GEN_buildDamageSource_499: return true;
        case SYM_GEN_connectForCombat_500: return true;
        case SYM_GEN_connectForCombat_signal_501: return true;
        case SYM_GEN_disconnectCombat_502: return true;
        case SYM_GEN__hasBehaviorMethod_503: return true;
        case SYM_GEN__behavior_call_504: return true;
        case SYM_GEN__tickChargePath_506: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_setup_72: out = fn_setup(args, argc); return true;
        case SYM_GEN_hasCharacter_73: out = fn_hasCharacter(args, argc); return true;
        case SYM_GEN_character_74: out = fn_character(args, argc); return true;
        case SYM_GEN_opponent_75: out = fn_opponent(args, argc); return true;
        case SYM_GEN_isPlaced_76: out = fn_isPlaced(args, argc); return true;
        case SYM_GEN_isCoreItem_77: out = fn_isCoreItem(args, argc); return true;
        case SYM_GEN_isPlayer_78: out = fn_isPlayer(args, argc); return true;
        case SYM_GEN_hasType_79: out = fn_hasType(args, argc); return true;
        case SYM_GEN_getTypeMultiplicity_80: out = fn_getTypeMultiplicity(args, argc); return true;
        case SYM_GEN_hasTag_81: out = fn_hasTag(args, argc); return true;
        case SYM_GEN_isWeapon_82: out = fn_isWeapon(args, argc); return true;
        case SYM_GEN_isBag_83: out = fn_isBag(args, argc); return true;
        case SYM_GEN_isGem_84: out = fn_isGem(args, argc); return true;
        case SYM_GEN_isBattleRageItem_85: out = fn_isBattleRageItem(args, argc); return true;
        case SYM_GEN_gainsStack_86: out = fn_gainsStack(args, argc); return true;
        case SYM_GEN_removesStack_87: out = fn_removesStack(args, argc); return true;
        case SYM_GEN_usesStack_88: out = fn_usesStack(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_canDamage_89: out = fn_canDamage(args, argc); return true;
        case SYM_GEN_canBeEmpowered_90: out = fn_canBeEmpowered(args, argc); return true;
        case SYM_GEN_canActivate_91: out = fn_canActivate(args, argc); return true;
        case SYM_GEN_getSpeed_92: out = fn_getSpeed(args, argc); return true;
        case SYM_GEN_speed_93: out = fn_speed(args, argc); return true;
        case SYM_GEN_getStackSpeedMods_94: out = fn_getStackSpeedMods(args, argc); return true;
        case SYM_GEN_hasCooldown_95: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_isCooldownActive_96: out = fn_isCooldownActive(args, argc); return true;
        case SYM_GEN_setCooldownActive_97: out = fn_setCooldownActive(args, argc); return true;
        case SYM_GEN_activateCooldown_98: out = fn_activateCooldown(args, argc); return true;
        case SYM_GEN_deactivateCooldown_99: out = fn_deactivateCooldown(args, argc); return true;
        case SYM_GEN_getBaseCooldown_100: out = fn_getBaseCooldown(args, argc); return true;
        case SYM_GEN_getBaseCooldownIndex_101: out = fn_getBaseCooldownIndex(args, argc); return true;
        case SYM_GEN_getCooldown_102: out = fn_getCooldown(args, argc); return true;
        case SYM_GEN_getCooldownIndex_103: out = fn_getCooldownIndex(args, argc); return true;
        case SYM_GEN_getModifiedCooldown_104: out = fn_getModifiedCooldown(args, argc); return true;
        case SYM_GEN_getModifiedCooldownIndex_105: out = fn_getModifiedCooldownIndex(args, argc); return true;
        case SYM_GEN_getCooldownEncoded_106: out = fn_getCooldownEncoded(args, argc); return true;
        case SYM_GEN_adjustCooldown_107: out = fn_adjustCooldown(args, argc); return true;
        case SYM_GEN_setBaseCooldown_108: out = fn_setBaseCooldown(args, argc); return true;
        case SYM_GEN_resetBaseCooldown_109: out = fn_resetBaseCooldown(args, argc); return true;
        case SYM_GEN_updateBaseCooldown_110: out = fn_updateBaseCooldown(args, argc); return true;
        case SYM_GEN_getBaseStaminaCost_111: out = fn_getBaseStaminaCost(args, argc); return true;
        case SYM_GEN_getStaminaCost_112: out = fn_getStaminaCost(args, argc); return true;
        case SYM_GEN_isStaminaModified_113: out = fn_isStaminaModified(args, argc); return true;
        case SYM_GEN_isStatModified_114: out = fn_isStatModified(args, argc); return true;
        case SYM_GEN_setStat_115: out = fn_setStat(args, argc); return true;
        case SYM_GEN_useStamina_116: out = fn_useStamina(args, argc); return true;
        case SYM_GEN_drainStamina_117: out = fn_drainStamina(args, argc); return true;
        case SYM_GEN_playOutOfStaminaAnimation_118: out = fn_playOutOfStaminaAnimation(args, argc); return true;
        case SYM_GEN_cacheAffectedItemsForCombat_119: out = fn_cacheAffectedItemsForCombat(args, argc); return true;
        case SYM_GEN_addToInventory_120: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_registerWithInventory_121: out = fn_registerWithInventory(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preCombatStart_124: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_hasStartofBattle_126: out = fn_hasStartofBattle(args, argc); return true;
        case SYM_GEN_combatStart_127: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_postCombatStart_128: out = fn_postCombatStart(args, argc); return true;
        case SYM_GEN_onPostCombatStart_129: out = fn_onPostCombatStart(args, argc); return true;
        case SYM_GEN_repeatCombatStart_130: out = fn_repeatCombatStart(args, argc); return true;
        case SYM_GEN_combatEnd_131: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_resetCombatState_133: out = fn_resetCombatState(args, argc); return true;
        case SYM_GEN_physicsTick_134: out = fn_physicsTick(args, argc); return true;
        case SYM_GEN_newItemTimer_135: out = fn_newItemTimer(args, argc); return true;
        case SYM_GEN_getTimer_136: out = fn_getTimer(args, argc); return true;
        case SYM_GEN__tickTimers_137: out = fn__tickTimers(args, argc); return true;
        case SYM_GEN_tickTimersPass_138: out = fn_tickTimersPass(args, argc); return true;
        case SYM_GEN_rebuildTimerSeen_139: out = fn_rebuildTimerSeen(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        case SYM_GEN_flickerPlayAni_141: out = fn_flickerPlayAni(args, argc); return true;
        case SYM_GEN_checkTriggerCount_142: out = fn_checkTriggerCount(args, argc); return true;
        case SYM_GEN_trigger_143: out = fn_trigger(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onAfterEffectFinished_145: out = fn_onAfterEffectFinished(args, argc); return true;
        case SYM_GEN_advanceCooldownPercent_146: out = fn_advanceCooldownPercent(args, argc); return true;
        case SYM_GEN_advanceCooldownSeconds_147: out = fn_advanceCooldownSeconds(args, argc); return true;
        case SYM_GEN_playActivationSound_148: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_activate_150: out = fn_activate(args, argc); return true;
        case SYM_GEN_checkActivationLimit_151: out = fn_checkActivationLimit(args, argc); return true;
        case SYM_GEN_getBaseMinDamage_152: out = fn_getBaseMinDamage(args, argc); return true;
        case SYM_GEN_getBaseMaxDamage_153: out = fn_getBaseMaxDamage(args, argc); return true;
        case SYM_GEN_getBaseAverageDamage_154: out = fn_getBaseAverageDamage(args, argc); return true;
        case SYM_GEN_getTypedDamageFactor_155: out = fn_getTypedDamageFactor(args, argc); return true;
        case SYM_GEN_getMinDamage_156: out = fn_getMinDamage(args, argc); return true;
        case SYM_GEN_getMaxDamage_157: out = fn_getMaxDamage(args, argc); return true;
        case SYM_GEN_getAverageDamage_158: out = fn_getAverageDamage(args, argc); return true;
        case SYM_GEN_randDamage_159: out = fn_randDamage(args, argc); return true;
        case SYM_GEN_getModifiedEffectDamage_160: out = fn_getModifiedEffectDamage(args, argc); return true;
        case SYM_GEN_addBonusDamage_161: out = fn_addBonusDamage(args, argc); return true;
        case SYM_GEN_changeVaryingDamage_162: out = fn_changeVaryingDamage(args, argc); return true;
        case SYM_GEN_addMinDamage_163: out = fn_addMinDamage(args, argc); return true;
        case SYM_GEN_addMaxDamage_164: out = fn_addMaxDamage(args, argc); return true;
        case SYM_GEN_getRemovableDamage_165: out = fn_getRemovableDamage(args, argc); return true;
        case SYM_GEN_removeBonusDamage_166: out = fn_removeBonusDamage(args, argc); return true;
        case SYM_GEN_setBonusDamageFactor_167: out = fn_setBonusDamageFactor(args, argc); return true;
        case SYM_GEN_getBaseChance_168: out = fn_getBaseChance(args, argc); return true;
        case SYM_GEN_getBaseChance2_169: out = fn_getBaseChance2(args, argc); return true;
        case SYM_GEN_applyBonusChance_170: out = fn_applyBonusChance(args, argc); return true;
        case SYM_GEN_getChance_171: out = fn_getChance(args, argc); return true;
        case SYM_GEN_getChance2_172: out = fn_getChance2(args, argc); return true;
        case SYM_GEN_rollChance_173: out = fn_rollChance(args, argc); return true;
        case SYM_GEN_rollChance2_174: out = fn_rollChance2(args, argc); return true;
        case SYM_GEN_addBonusChance_175: out = fn_addBonusChance(args, argc); return true;
        case SYM_GEN_addBonusChance_additive_176: out = fn_addBonusChance_additive(args, argc); return true;
        case SYM_GEN_addAccuracy_177: out = fn_addAccuracy(args, argc); return true;
        case SYM_GEN_getCritChancePercent_178: out = fn_getCritChancePercent(args, argc); return true;
        case SYM_GEN_addCritChancePercent_179: out = fn_addCritChancePercent(args, argc); return true;
        case SYM_GEN_reduceCritChancePercent_180: out = fn_reduceCritChancePercent(args, argc); return true;
        case SYM_GEN_changeCritChancePercent_181: out = fn_changeCritChancePercent(args, argc); return true;
        case SYM_GEN_getCritTokens_182: out = fn_getCritTokens(args, argc); return true;
        case SYM_GEN_addCritTokens_183: out = fn_addCritTokens(args, argc); return true;
        case SYM_GEN_useCritToken_184: out = fn_useCritToken(args, argc); return true;
        case SYM_GEN_addCritSeverity_185: out = fn_addCritSeverity(args, argc); return true;
        case SYM_GEN_getCritSeverity_186: out = fn_getCritSeverity(args, argc); return true;
        case SYM_GEN_rollDoubleAttackEffect_187: out = fn_rollDoubleAttackEffect(args, argc); return true;
        case SYM_GEN_getP_188: out = fn_getP(args, argc); return true;
        case SYM_GEN_getP_m_189: out = fn_getP_m(args, argc); return true;
        case SYM_GEN_getParamModified_190: out = fn_getParamModified(args, argc); return true;
        case SYM_GEN_modifyParam_191: out = fn_modifyParam(args, argc); return true;
        case SYM_GEN_modifyParam_add_192: out = fn_modifyParam_add(args, argc); return true;
        case SYM_GEN_getBaseAccuracy_193: out = fn_getBaseAccuracy(args, argc); return true;
        case SYM_GEN_getAccuracy_194: out = fn_getAccuracy(args, argc); return true;
        case SYM_GEN_getAmplificationChancePercent_195: out = fn_getAmplificationChancePercent(args, argc); return true;
        case SYM_GEN_changeAmplificiationChancePercent_196: out = fn_changeAmplificiationChancePercent(args, argc); return true;
        case SYM_GEN_changeAmplificiationChancePercent_allBuffs_197: out = fn_changeAmplificiationChancePercent_allBuffs(args, argc); return true;
        case SYM_GEN_changeAmplificiationChancePercent_allDebuffs_198: out = fn_changeAmplificiationChancePercent_allDebuffs(args, argc); return true;
        case SYM_GEN_changeNullifyChancePercent_199: out = fn_changeNullifyChancePercent(args, argc); return true;
        case SYM_GEN_giveReflectStacks_200: out = fn_giveReflectStacks(args, argc); return true;
        case SYM_GEN_giveStacks_201: out = fn_giveStacks(args, argc); return true;
        case SYM_GEN_giveStacksTemporary_202: out = fn_giveStacksTemporary(args, argc); return true;
        case SYM_GEN_giveBlock_203: out = fn_giveBlock(args, argc); return true;
        case SYM_GEN_getBlock_204: out = fn_getBlock(args, argc); return true;
        case SYM_GEN_removeBlock_205: out = fn_removeBlock(args, argc); return true;
        case SYM_GEN_loseBlock_206: out = fn_loseBlock(args, argc); return true;
        case SYM_GEN_useBlock_207: out = fn_useBlock(args, argc); return true;
        case SYM_GEN_stealStack_208: out = fn_stealStack(args, argc); return true;
        case SYM_GEN_giveSpikes_209: out = fn_giveSpikes(args, argc); return true;
        case SYM_GEN_giveVampirism_210: out = fn_giveVampirism(args, argc); return true;
        case SYM_GEN_inflictPoison_211: out = fn_inflictPoison(args, argc); return true;
        case SYM_GEN_selfInflictPoison_212: out = fn_selfInflictPoison(args, argc); return true;
        case SYM_GEN_inflictBlind_213: out = fn_inflictBlind(args, argc); return true;
        case SYM_GEN_giveRegeneration_214: out = fn_giveRegeneration(args, argc); return true;
        case SYM_GEN_giveLucky_215: out = fn_giveLucky(args, argc); return true;
        case SYM_GEN_giveMana_216: out = fn_giveMana(args, argc); return true;
        case SYM_GEN_giveEmpower_217: out = fn_giveEmpower(args, argc); return true;
        case SYM_GEN_giveHeat_218: out = fn_giveHeat(args, argc); return true;
        case SYM_GEN_giveCold_219: out = fn_giveCold(args, argc); return true;
        case SYM_GEN_dealDamage_220: out = fn_dealDamage(args, argc); return true;
        case SYM_GEN_dealEffectDamage_221: out = fn_dealEffectDamage(args, argc); return true;
        case SYM_GEN_preDealDamage_early_222: out = fn_preDealDamage_early(args, argc); return true;
        case SYM_GEN_preDealDamage_late_223: out = fn_preDealDamage_late(args, argc); return true;
        case SYM_GEN_dealtDamage_224: out = fn_dealtDamage(args, argc); return true;
        case SYM_GEN_countDamage_225: out = fn_countDamage(args, argc); return true;
        case SYM_GEN_getNumNonStackItemMetrics_226: out = sf_getNumNonStackItemMetrics(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumItemMetrics_227: out = sf_getNumItemMetrics(gd_ctx, args, argc); return true;
        case SYM_GEN_getStackMetricIndex_228: out = sf_getStackMetricIndex(gd_ctx, args, argc); return true;
        case SYM_GEN_getMultiMetricIndex_229: out = sf_getMultiMetricIndex(gd_ctx, args, argc); return true;
        case SYM_GEN_addMetric_230: out = fn_addMetric(args, argc); return true;
        case SYM_GEN_getMetric_231: out = fn_getMetric(args, argc); return true;
        case SYM_GEN_stackChanged_232: out = fn_stackChanged(args, argc); return true;
        case SYM_GEN_staminaChanged_233: out = fn_staminaChanged(args, argc); return true;
        case SYM_GEN_getName_234: out = fn_getName(args, argc); return true;
        case SYM_GEN_getIndex_235: out = fn_getIndex(args, argc); return true;
        case SYM_GEN_getRarity_236: out = fn_getRarity(args, argc); return true;
        case SYM_GEN_getShopChance_237: out = fn_getShopChance(args, argc); return true;
        case SYM_GEN_getMainType_238: out = fn_getMainType(args, argc); return true;
        case SYM_GEN_getNumStaticTypes_239: out = fn_getNumStaticTypes(args, argc); return true;
        case SYM_GEN_getTypes_240: out = fn_getTypes(args, argc); return true;
        case SYM_GEN_hasDynamicType_241: out = fn_hasDynamicType(args, argc); return true;
        case SYM_GEN_addDynamicType_242: out = fn_addDynamicType(args, argc); return true;
        case SYM_GEN_removeDynamicType_243: out = fn_removeDynamicType(args, argc); return true;
        case SYM_GEN_clearDynamicTypes_244: out = fn_clearDynamicTypes(args, argc); return true;
        case SYM_GEN_isA_245: out = fn_isA(args, argc); return true;
        case SYM_GEN_isNeutral_246: out = fn_isNeutral(args, argc); return true;
        case SYM_GEN_isTreasure_247: out = fn_isTreasure(args, argc); return true;
        case SYM_GEN_isClassItem_248: out = fn_isClassItem(args, argc); return true;
        case SYM_GEN_isSubclassItem_249: out = fn_isSubclassItem(args, argc); return true;
        case SYM_GEN_isOwnable_250: out = fn_isOwnable(args, argc); return true;
        case SYM_GEN_isOwnedByOpponent_251: out = fn_isOwnedByOpponent(args, argc); return true;
        case SYM_GEN_isGateItem_252: out = fn_isGateItem(args, argc); return true;
        case SYM_GEN_isShowCaseItem_253: out = fn_isShowCaseItem(args, argc); return true;
        case SYM_GEN_isAffectingDistinct_254: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_affectsEmpty_255: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_hasOpponent_256: out = fn_hasOpponent(args, argc); return true;
        case SYM_GEN_getEffectiveOwnerType_257: out = fn_getEffectiveOwnerType(args, argc); return true;
        case SYM_GEN_isBaseItem_258: out = fn_isBaseItem(args, argc); return true;
        case SYM_GEN_isBusy_259: out = fn_isBusy(args, argc); return true;
        case SYM_GEN_isBoundAsIngredient_260: out = fn_isBoundAsIngredient(args, argc); return true;
        case SYM_GEN_getStat_261: out = fn_getStat(args, argc); return true;
        case SYM_GEN_getP_check_262: out = fn_getP_check(args, argc); return true;
        case SYM_GEN_getP1_263: out = fn_getP1(args, argc); return true;
        case SYM_GEN_getP2_264: out = fn_getP2(args, argc); return true;
        case SYM_GEN_getP3_265: out = fn_getP3(args, argc); return true;
        case SYM_GEN_getP4_266: out = fn_getP4(args, argc); return true;
        case SYM_GEN_getP5_267: out = fn_getP5(args, argc); return true;
        case SYM_GEN_getP6_268: out = fn_getP6(args, argc); return true;
        case SYM_GEN_getP7_269: out = fn_getP7(args, argc); return true;
        case SYM_GEN_getP8_270: out = fn_getP8(args, argc); return true;
        case SYM_GEN_getP9_271: out = fn_getP9(args, argc); return true;
        case SYM_GEN_getP10_272: out = fn_getP10(args, argc); return true;
        case SYM_GEN_addSpeed_273: out = fn_addSpeed(args, argc); return true;
        case SYM_GEN_reduceSpeed_274: out = fn_reduceSpeed(args, argc); return true;
        case SYM_GEN_getDPS_275: out = fn_getDPS(args, argc); return true;
        case SYM_GEN_isDPSModified_276: out = fn_isDPSModified(args, argc); return true;
        case SYM_GEN_getDamageRange_277: out = fn_getDamageRange(args, argc); return true;
        case SYM_GEN_isCooldownModified_278: out = fn_isCooldownModified(args, argc); return true;
        case SYM_GEN_isAccuracyModified_279: out = fn_isAccuracyModified(args, argc); return true;
        case SYM_GEN_isChance1Modified_280: out = fn_isChance1Modified(args, argc); return true;
        case SYM_GEN_isChance2Modified_281: out = fn_isChance2Modified(args, argc); return true;
        case SYM_GEN_isDamageModified_282: out = fn_isDamageModified(args, argc); return true;
        case SYM_GEN_getBaseStaminaPerSecond_283: out = fn_getBaseStaminaPerSecond(args, argc); return true;
        case SYM_GEN_getStaminaPerSecond_284: out = fn_getStaminaPerSecond(args, argc); return true;
        case SYM_GEN_isStaminaPerSecondModified_285: out = fn_isStaminaPerSecondModified(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_canAffect_tertiary_288: out = fn_canAffect_tertiary(args, argc); return true;
        case SYM_GEN_canAffect_lightning_289: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_canAffect_color_290: out = fn_canAffect_color(args, argc); return true;
        case SYM_GEN_canBlock_291: out = fn_canBlock(args, argc); return true;
        case SYM_GEN_canHealOrLifesteal_292: out = fn_canHealOrLifesteal(args, argc); return true;
        case SYM_GEN_canModifyChance_293: out = fn_canModifyChance(args, argc); return true;
        case SYM_GEN_canUseStamina_294: out = fn_canUseStamina(args, argc); return true;
        case SYM_GEN_hasAttackEffect_295: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_gainsBuffs_296: out = fn_gainsBuffs(args, argc); return true;
        case SYM_GEN_usesBuffs_297: out = fn_usesBuffs(args, argc); return true;
        case SYM_GEN_inflictsDebuffs_298: out = fn_inflictsDebuffs(args, argc); return true;
        case SYM_GEN_reactsToCharges_299: out = fn_reactsToCharges(args, argc); return true;
        case SYM_GEN_fillUpStamina_300: out = fn_fillUpStamina(args, argc); return true;
        case SYM_GEN_getRelativeOpponentHealth_301: out = fn_getRelativeOpponentHealth(args, argc); return true;
        case SYM_GEN_getRelativeHealth_302: out = fn_getRelativeHealth(args, argc); return true;
        case SYM_GEN_giveBuffPower_303: out = fn_giveBuffPower(args, argc); return true;
        case SYM_GEN_changeHealAmp_304: out = fn_changeHealAmp(args, argc); return true;
        case SYM_GEN_changeStaminaFactor_305: out = fn_changeStaminaFactor(args, argc); return true;
        case SYM_GEN_addBonusDamageFactor_306: out = fn_addBonusDamageFactor(args, argc); return true;
        case SYM_GEN_reduceBonusDamageFactor_307: out = fn_reduceBonusDamageFactor(args, argc); return true;
        case SYM_GEN_reduceMinDamage_308: out = fn_reduceMinDamage(args, argc); return true;
        case SYM_GEN_reduceMaxDamage_309: out = fn_reduceMaxDamage(args, argc); return true;
        case SYM_GEN_reduceBonusDamage_310: out = fn_reduceBonusDamage(args, argc); return true;
        case SYM_GEN_purgeDamage_311: out = fn_purgeDamage(args, argc); return true;
        case SYM_GEN_giveDoubleActivationChance_312: out = fn_giveDoubleActivationChance(args, argc); return true;
        case SYM_GEN_giveDoubleAttackEffectChance_313: out = fn_giveDoubleAttackEffectChance(args, argc); return true;
        case SYM_GEN_giveCritTokens_314: out = fn_giveCritTokens(args, argc); return true;
        case SYM_GEN_giveMaxStamina_315: out = fn_giveMaxStamina(args, argc); return true;
        case SYM_GEN_giveMaxStaminaTemporary_316: out = fn_giveMaxStaminaTemporary(args, argc); return true;
        case SYM_GEN_giveMaxHealth_317: out = fn_giveMaxHealth(args, argc); return true;
        case SYM_GEN_giveStamina_318: out = fn_giveStamina(args, argc); return true;
        case SYM_GEN_inflictFatigueDamage_319: out = fn_inflictFatigueDamage(args, argc); return true;
        case SYM_GEN_sendCharge_320: out = fn_sendCharge(args, argc); return true;
        case SYM_GEN__chargeInventoryCells_321: out = fn__chargeInventoryCells(args, argc); return true;
        case SYM_GEN__rotVecQuarterTurns_322: out = fn__rotVecQuarterTurns(args, argc); return true;
        case SYM_GEN__chargeEnterCell_323: out = fn__chargeEnterCell(args, argc); return true;
        case SYM_GEN_chargeReceived_324: out = fn_chargeReceived(args, argc); return true;
        case SYM_GEN_chargeLeft_325: out = fn_chargeLeft(args, argc); return true;
        case SYM_GEN_changeChargedItemStat_326: out = fn_changeChargedItemStat(args, argc); return true;
        case SYM_GEN_heal_327: out = fn_heal(args, argc); return true;
        case SYM_GEN_healthToBlock_328: out = fn_healthToBlock(args, argc); return true;
        case SYM_GEN_stealLife_329: out = fn_stealLife(args, argc); return true;
        case SYM_GEN_stun_330: out = fn_stun(args, argc); return true;
        case SYM_GEN_checkMana_331: out = fn_checkMana(args, argc); return true;
        case SYM_GEN_useMana_332: out = fn_useMana(args, argc); return true;
        case SYM_GEN_tryUseMana_333: out = fn_tryUseMana(args, argc); return true;
        case SYM_GEN_removeMana_334: out = fn_removeMana(args, argc); return true;
        case SYM_GEN_giveMana_capped_335: out = fn_giveMana_capped(args, argc); return true;
        case SYM_GEN_removeSpikes_336: out = fn_removeSpikes(args, argc); return true;
        case SYM_GEN_useSpikes_337: out = fn_useSpikes(args, argc); return true;
        case SYM_GEN_loseSpikes_338: out = fn_loseSpikes(args, argc); return true;
        case SYM_GEN_removeVampirism_339: out = fn_removeVampirism(args, argc); return true;
        case SYM_GEN_useVampirism_340: out = fn_useVampirism(args, argc); return true;
        case SYM_GEN_loseVampirism_341: out = fn_loseVampirism(args, argc); return true;
        case SYM_GEN_cleansePoison_342: out = fn_cleansePoison(args, argc); return true;
        case SYM_GEN_selfInflictBlind_343: out = fn_selfInflictBlind(args, argc); return true;
        case SYM_GEN_cleanseBlind_344: out = fn_cleanseBlind(args, argc); return true;
        case SYM_GEN_removeRegeneration_345: out = fn_removeRegeneration(args, argc); return true;
        case SYM_GEN_useRegeneration_346: out = fn_useRegeneration(args, argc); return true;
        case SYM_GEN_tryUseLucky_347: out = fn_tryUseLucky(args, argc); return true;
        case SYM_GEN_loseLucky_348: out = fn_loseLucky(args, argc); return true;
        case SYM_GEN_removeLucky_349: out = fn_removeLucky(args, argc); return true;
        case SYM_GEN_useLucky_350: out = fn_useLucky(args, argc); return true;
        case SYM_GEN_inflictCold_351: out = fn_inflictCold(args, argc); return true;
        case SYM_GEN_cleanseCold_352: out = fn_cleanseCold(args, argc); return true;
        case SYM_GEN_loseHeat_353: out = fn_loseHeat(args, argc); return true;
        case SYM_GEN_useHeat_354: out = fn_useHeat(args, argc); return true;
        case SYM_GEN_loseEmpower_355: out = fn_loseEmpower(args, argc); return true;
        case SYM_GEN_cleanseRandomDebuffs_356: out = fn_cleanseRandomDebuffs(args, argc); return true;
        case SYM_GEN_inflictRandomDebuffs_357: out = fn_inflictRandomDebuffs(args, argc); return true;
        case SYM_GEN_pickRandomStacks_358: out = fn_pickRandomStacks(args, argc); return true;
        case SYM_GEN_pickRandomStacksToGive_359: out = fn_pickRandomStacksToGive(args, argc); return true;
        case SYM_GEN_getLeastStacks_360: out = fn_getLeastStacks(args, argc); return true;
        case SYM_GEN_getMostStacks_361: out = fn_getMostStacks(args, argc); return true;
        case SYM_GEN_getStackFraction_362: out = fn_getStackFraction(args, argc); return true;
        case SYM_GEN_multiplyBuffsLimit_363: out = fn_multiplyBuffsLimit(args, argc); return true;
        case SYM_GEN_removeBuffsFraction_364: out = fn_removeBuffsFraction(args, argc); return true;
        case SYM_GEN_stealBuffsFraction_365: out = fn_stealBuffsFraction(args, argc); return true;
        case SYM_GEN_giveLeastBuffs_366: out = fn_giveLeastBuffs(args, argc); return true;
        case SYM_GEN_giveMostBuffs_367: out = fn_giveMostBuffs(args, argc); return true;
        case SYM_GEN_removeMostBuffs_368: out = fn_removeMostBuffs(args, argc); return true;
        case SYM_GEN_giveRandomBuffs_369: out = fn_giveRandomBuffs(args, argc); return true;
        case SYM_GEN_giveAllBuffs_370: out = fn_giveAllBuffs(args, argc); return true;
        case SYM_GEN_useRandomBuffs_371: out = fn_useRandomBuffs(args, argc); return true;
        case SYM_GEN_removeRandomBuffs_372: out = fn_removeRandomBuffs(args, argc); return true;
        case SYM_GEN_stealRandomBuff_373: out = fn_stealRandomBuff(args, argc); return true;
        case SYM_GEN_connectToCharacterBuffs_374: out = fn_connectToCharacterBuffs(args, argc); return true;
        case SYM_GEN_connectToCharacterDebuffs_375: out = fn_connectToCharacterDebuffs(args, argc); return true;
        case SYM_GEN_connectToOpponentDebuffs_376: out = fn_connectToOpponentDebuffs(args, argc); return true;
        case SYM_GEN_connectToOpponentBuffs_377: out = fn_connectToOpponentBuffs(args, argc); return true;
        case SYM_GEN_getNextFreeLabelPosition_378: out = fn_getNextFreeLabelPosition(args, argc); return true;
        case SYM_GEN_spawnLabel_379: out = fn_spawnLabel(args, argc); return true;
        case SYM_GEN_spawnLabel_other_380: out = fn_spawnLabel_other(args, argc); return true;
        case SYM_GEN_consume_381: out = fn_consume(args, argc); return true;
        case SYM_GEN_setState_382: out = fn_setState(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_onTemporaryStacksTimeout_384: out = fn_onTemporaryStacksTimeout(args, argc); return true;
        case SYM_GEN_empowerEnd_385: out = fn_empowerEnd(args, argc); return true;
        case SYM_GEN_hasSockets_386: out = fn_hasSockets(args, argc); return true;
        case SYM_GEN_getNumSockets_387: out = fn_getNumSockets(args, argc); return true;
        case SYM_GEN_initSockets_388: out = fn_initSockets(args, argc); return true;
        case SYM_GEN_getItem_389: out = fn_getItem(args, argc); return true;
        case SYM_GEN_hasGems_390: out = fn_hasGems(args, argc); return true;
        case SYM_GEN_getGemsOfItems_391: out = fn_getGemsOfItems(args, argc); return true;
        case SYM_GEN_getPrice_392: out = fn_getPrice(args, argc); return true;
        case SYM_GEN_getBaseSellPrice_393: out = fn_getBaseSellPrice(args, argc); return true;
        case SYM_GEN_getSellPrice_394: out = fn_getSellPrice(args, argc); return true;
        case SYM_GEN_getSalePrice_395: out = fn_getSalePrice(args, argc); return true;
        case SYM_GEN_setGem_396: out = fn_setGem(args, argc); return true;
        case SYM_GEN_pushGemsToStorage_397: out = fn_pushGemsToStorage(args, argc); return true;
        case SYM_GEN_pushItemsInsideToStorage_398: out = fn_pushItemsInsideToStorage(args, argc); return true;
        case SYM_GEN_returnToSocket_399: out = fn_returnToSocket(args, argc); return true;
        case SYM_GEN_getOwnOrPlayerInventory_400: out = fn_getOwnOrPlayerInventory(args, argc); return true;
        case SYM_GEN_getCellsForGlobalPositions_401: out = fn_getCellsForGlobalPositions(args, argc); return true;
        case SYM_GEN_getGlobalPointsForCells_402: out = fn_getGlobalPointsForCells(args, argc); return true;
        case SYM_GEN_getGlobalPointsForCells_noRotate_403: out = fn_getGlobalPointsForCells_noRotate(args, argc); return true;
        case SYM_GEN_getCollisionCells_404: out = fn_getCollisionCells(args, argc); return true;
        case SYM_GEN_getExtensionCells_405: out = fn_getExtensionCells(args, argc); return true;
        case SYM_GEN_getCollisionPoints_406: out = fn_getCollisionPoints(args, argc); return true;
        case SYM_GEN_getExtensionPoints_407: out = fn_getExtensionPoints(args, argc); return true;
        case SYM_GEN_getAffectedCells_tilemap_408: out = fn_getAffectedCells_tilemap(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_409: out = fn_getAffectedCellsAfterRotate(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_410: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_secondary_411: out = fn_getAffectedCellsAfterRotate_secondary(args, argc); return true;
        case SYM_GEN_getAffectedCells_noRotate_412: out = fn_getAffectedCells_noRotate(args, argc); return true;
        case SYM_GEN_getAffectedPoints_413: out = fn_getAffectedPoints(args, argc); return true;
        case SYM_GEN_getAffectedCellsInInventory_414: out = fn_getAffectedCellsInInventory(args, argc); return true;
        case SYM_GEN_getAffectedCellsInInventory_cached_415: out = fn_getAffectedCellsInInventory_cached(args, argc); return true;
        case SYM_GEN_cacheAffectedCells_416: out = fn_cacheAffectedCells(args, argc); return true;
        case SYM_GEN_cleanCachedAffectedItems_417: out = fn_cleanCachedAffectedItems(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_getAffectedItems_420: out = fn_getAffectedItems(args, argc); return true;
        case SYM_GEN_getAffectedItems_nocache_421: out = fn_getAffectedItems_nocache(args, argc); return true;
        case SYM_GEN_getItemsInAffectedCells_422: out = fn_getItemsInAffectedCells(args, argc); return true;
        case SYM_GEN_getItemsInAffectedCells_cached_423: out = fn_getItemsInAffectedCells_cached(args, argc); return true;
        case SYM_GEN_countItemsInAffectedCells_cached_424: out = fn_countItemsInAffectedCells_cached(args, argc); return true;
        case SYM_GEN_isItemAffected_425: out = fn_isItemAffected(args, argc); return true;
        case SYM_GEN_getNumEmptyAffectedCells_426: out = fn_getNumEmptyAffectedCells(args, argc); return true;
        case SYM_GEN_getNumAffectedItems_427: out = fn_getNumAffectedItems(args, argc); return true;
        case SYM_GEN_getFirstAffectedItem_428: out = fn_getFirstAffectedItem(args, argc); return true;
        case SYM_GEN_getNumAffected_type_429: out = fn_getNumAffected_type(args, argc); return true;
        case SYM_GEN_getNumDistinctAffectedItems_430: out = fn_getNumDistinctAffectedItems(args, argc); return true;
        case SYM_GEN_getNumAffectedCells_431: out = fn_getNumAffectedCells(args, argc); return true;
        case SYM_GEN_activateExtendedAffectedCells_432: out = fn_activateExtendedAffectedCells(args, argc); return true;
        case SYM_GEN_deactivateExtendedAffectedCells_433: out = fn_deactivateExtendedAffectedCells(args, argc); return true;
        case SYM_GEN_canAffectDraggedItem_434: out = fn_canAffectDraggedItem(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_435: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_436: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onItemAdded_437: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_438: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_getNumOccupiedCells_439: out = fn_getNumOccupiedCells(args, argc); return true;
        case SYM_GEN_getNumBagCells_440: out = fn_getNumBagCells(args, argc); return true;
        case SYM_GEN_getNumCells_441: out = fn_getNumCells(args, argc); return true;
        case SYM_GEN_getSizeInCells_442: out = fn_getSizeInCells(args, argc); return true;
        case SYM_GEN_getTopLeftCell_443: out = fn_getTopLeftCell(args, argc); return true;
        case SYM_GEN_getNormalizedCollisionCells_444: out = fn_getNormalizedCollisionCells(args, argc); return true;
        case SYM_GEN_canCombine_445: out = fn_canCombine(args, argc); return true;
        case SYM_GEN_prepareReplacement_446: out = fn_prepareReplacement(args, argc); return true;
        case SYM_GEN_finishReplacement_447: out = fn_finishReplacement(args, argc); return true;
        case SYM_GEN_placeGeneratedItem_448: out = fn_placeGeneratedItem(args, argc); return true;
        case SYM_GEN_moveTo_449: out = fn_moveTo(args, argc); return true;
        case SYM_GEN_resetZ_450: out = fn_resetZ(args, argc); return true;
        case SYM_GEN_onGateItemRoll_451: out = fn_onGateItemRoll(args, argc); return true;
        case SYM_GEN_insertCounter_452: out = fn_insertCounter(args, argc); return true;
        case SYM_GEN_queue_free_453: out = fn_queue_free(args, argc); return true;
        case SYM_GEN_shift_454: out = fn_shift(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_onSold_456: out = fn_onSold(args, argc); return true;
        case SYM_GEN_reactToItemTypeChange_457: out = fn_reactToItemTypeChange(args, argc); return true;
        case SYM_GEN_onItemTypeChanged_458: out = fn_onItemTypeChanged(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_countAllPlacedOfType_460: out = fn_countAllPlacedOfType(args, argc); return true;
        case SYM_GEN_getTouchedBagsCounted_461: out = fn_getTouchedBagsCounted(args, argc); return true;
        case SYM_GEN_getHeightRange_462: out = fn_getHeightRange(args, argc); return true;
        case SYM_GEN_ready_deferred_463: out = fn_ready_deferred(args, argc); return true;
        case SYM_GEN_rotationFromFaceDirection_464: out = fn_rotationFromFaceDirection(args, argc); return true;
        case SYM_GEN_getFaceDirection_465: out = fn_getFaceDirection(args, argc); return true;
        case SYM_GEN_getGlobalFaceDirection_466: out = fn_getGlobalFaceDirection(args, argc); return true;
        case SYM_GEN_setFaceDirectionInstant_467: out = fn_setFaceDirectionInstant(args, argc); return true;
        case SYM_GEN_setRotation_468: out = fn_setRotation(args, argc); return true;
        case SYM_GEN_changeAllItemsCritRate_469: out = fn_changeAllItemsCritRate(args, argc); return true;
        case SYM_GEN_miniActivate_470: out = fn_miniActivate(args, argc); return true;
        case SYM_GEN_previewCellCollision_471: out = fn_previewCellCollision(args, argc); return true;
        case SYM_GEN_previewCells_472: out = fn_previewCells(args, argc); return true;
        case SYM_GEN_previewCanAffect_473: out = fn_previewCanAffect(args, argc); return true;
        case SYM_GEN_rotateRight_474: out = fn_rotateRight(args, argc); return true;
        case SYM_GEN_rotateLeft_475: out = fn_rotateLeft(args, argc); return true;
        case SYM_GEN_rotateTo_476: out = fn_rotateTo(args, argc); return true;
        case SYM_GEN_rotateToDeferred_477: out = fn_rotateToDeferred(args, argc); return true;
        case SYM_GEN_setFaceDirection_478: out = fn_setFaceDirection(args, argc); return true;
        case SYM_GEN_correctInsideItemFacedirection_479: out = fn_correctInsideItemFacedirection(args, argc); return true;
        case SYM_GEN_getBagEffect_480: out = fn_getBagEffect(args, argc); return true;
        case SYM_GEN_getGemData_481: out = fn_getGemData(args, argc); return true;
        case SYM_GEN_setGemData_482: out = fn_setGemData(args, argc); return true;
        case SYM_GEN_reconstructCooldown_483: out = fn_reconstructCooldown(args, argc); return true;
        case SYM_GEN_findBondsWithAffectedItems_484: out = fn_findBondsWithAffectedItems(args, argc); return true;
        case SYM_GEN_rotateProgress_485: out = fn_rotateProgress(args, argc); return true;
        case SYM_GEN_cacheCollisionCells_486: out = fn_cacheCollisionCells(args, argc); return true;
        case SYM_GEN_isBaseItemForShopItem_487: out = fn_isBaseItemForShopItem(args, argc); return true;
        case SYM_GEN_activateFromEvent_488: out = fn_activateFromEvent(args, argc); return true;
        case SYM_GEN_getNeighborItemsAndGems_489: out = fn_getNeighborItemsAndGems(args, argc); return true;
        case SYM_GEN_getTouchedBags_490: out = fn_getTouchedBags(args, argc); return true;
        case SYM_GEN_getBusyNeighbors_491: out = fn_getBusyNeighbors(args, argc); return true;
        case SYM_GEN_getCraftableNeighbors_492: out = fn_getCraftableNeighbors(args, argc); return true;
        case SYM_GEN_isAvailableForCrafting_493: out = fn_isAvailableForCrafting(args, argc); return true;
        case SYM_GEN_getAffectedGoldValue_494: out = fn_getAffectedGoldValue(args, argc); return true;
        case SYM_GEN_countTypes_495: out = fn_countTypes(args, argc); return true;
        case SYM_GEN_hasSameOrientationAsPickup_496: out = fn_hasSameOrientationAsPickup(args, argc); return true;
        case SYM_GEN_getGemsNoNull_497: out = fn_getGemsNoNull(args, argc); return true;
        case SYM_GEN_getGems_498: out = fn_getGems(args, argc); return true;
        case SYM_GEN_buildDamageSource_499: out = fn_buildDamageSource(args, argc); return true;
        case SYM_GEN_connectForCombat_500: out = fn_connectForCombat(args, argc); return true;
        case SYM_GEN_connectForCombat_signal_501: out = fn_connectForCombat_signal(args, argc); return true;
        case SYM_GEN_disconnectCombat_502: out = fn_disconnectCombat(args, argc); return true;
        case SYM_GEN__hasBehaviorMethod_503: out = fn__hasBehaviorMethod(args, argc); return true;
        case SYM_GEN__behavior_call_504: out = fn__behavior_call(args, argc); return true;
        case SYM_GEN__f32eng_505: out = sf__f32eng(gd_ctx, args, argc); return true;
        case SYM_GEN__tickChargePath_506: out = fn__tickChargePath(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getNumNonStackItemMetrics_226: out = sf_getNumNonStackItemMetrics(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumItemMetrics_227: out = sf_getNumItemMetrics(gd_ctx, args, argc); return true;
        case SYM_GEN_getStackMetricIndex_228: out = sf_getStackMetricIndex(gd_ctx, args, argc); return true;
        case SYM_GEN_getMultiMetricIndex_229: out = sf_getMultiMetricIndex(gd_ctx, args, argc); return true;
        case SYM_GEN__f32eng_505: out = sf__f32eng(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreItem::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__ctx = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv__descriptor = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv__character = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__descriptor, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv__ctx, lv__descriptor, lv__character}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setup_72, _ca, 3); })();
    return gd::GdVal::null();
}
namespace gd {
void native_static_setup_hit(unsigned);
inline bool native_setup_empty_stack_tables(BattleCtx& ctx, const GdVal& powers, const GdVal& chances) {
    if (powers.kind != GdVal::Kind::Dict || chances.kind != GdVal::Kind::Dict || !powers.dict || !chances.dict || powers.dict == chances.dict) return false;
    auto* a = powers.dict; auto* b = chances.dict;
    if (a->len || a->cap || a->entries || a->buckets || a->bucket_cap || b->len || b->cap || b->entries || b->buckets || b->bucket_cap) return false;
    a->entries = ctx.arena.alloc_array<GdDictEntry>(16); a->cap = 16;
    b->entries = ctx.arena.alloc_array<GdDictEntry>(16); b->cap = 16;
    a->buckets = ctx.arena.alloc_array<int32_t>(32); a->bucket_cap = 32;
    b->buckets = ctx.arena.alloc_array<int32_t>(32); b->bucket_cap = 32;
    std::memset(a->buckets, -1, 32 * sizeof(int32_t));
    std::memset(b->buckets, -1, 32 * sizeof(int32_t));
    for (uint32_t i = 0; i < 11; ++i) {
        const auto key = GdVal::from_int(100 + i); const auto hash = gd_val_hash(key);
        a->entries[i] = {key, GdVal::from_float(1.0), hash}; ++a->len;
        b->entries[i] = {key, GdVal::from_float(0.0), hash}; ++b->len;
        uint32_t position = uint32_t(hash) & 31;
        while (a->buckets[position] >= 0) position = (position + 1) & 31;
        a->buckets[position] = b->buckets[position] = int32_t(i);
    }
    if (ctx.native_resolved_collect) native_static_setup_hit(0);
    return true;
}
}

gd::GdVal Gd__gd_core__CoreItem::fn_setup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__ctx = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__descriptor = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__character = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_ctx = lv__ctx;
    this->f_descriptor = lv__descriptor;
    this->f_character_ = lv__character;
    this->f_name = gd::native_inline_get_prop(gd_ctx, lv__descriptor, SYM_GEN_name_7);
    this->f_chanceRng = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRng_1749), gd::SYM_new, _ca, 1); })();
    this->f_damageRangeRng = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRange_1750), gd::SYM_new, _ca, 1); })();
    {
        gd::GdVal _t1 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_sub(gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_sceneDepth_1703)), gd::GdVal::from_int(1LL)))}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t2 = (_t1.kind == gd::GdVal::Kind::Arr) ? _t1.arr : nullptr;
        uint32_t _len__t3 = _t2 ? _t2->len : 0u;
        for (uint32_t _t3 = 0; _t3 < _len__t3; ++_t3) {
            gd::GdVal lv__i = _t2->data[_t3];
            this->f_chanceRng = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_BalancedRng_1749), gd::SYM_new, _ca, 1); })();
        }
    }
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::native_inline_get_prop(gd_ctx, lv__descriptor, SYM_GEN_cd_1679));
    if (gd_ctx.native_resolved_dispatch) {
        if (!gd::native_setup_empty_stack_tables(gd_ctx, this->f_buffPowers, this->f_buffAmplificationChances)) {
            if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(1);
            for (int64_t stack = 100; stack <= 110; ++stack) {
                gd::GdVal lv_buff = gd::GdVal::from_int(stack);
                { gd::GdVal target = this->f_buffPowers; gd::native_array_set_index(gd_ctx, target, lv_buff, gd::GdVal::from_float(1.0)); }
                { gd::GdVal target = this->f_buffAmplificationChances; gd::native_array_set_index(gd_ctx, target, lv_buff, gd::GdVal::from_float(0.0)); }
            }
        }
    } else {
        gd::GdVal _t4 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getStacks_1023, nullptr, 0));
        gd::GdArr* _t5 = (_t4.kind == gd::GdVal::Kind::Arr) ? _t4.arr : nullptr;
        uint32_t _len__t6 = _t5 ? _t5->len : 0u;
        for (uint32_t _t6 = 0; _t6 < _len__t6; ++_t6) {
            gd::GdVal lv_buff = _t5->data[_t6];
            { gd::GdVal _t7 = this->f_buffPowers; gd::GdVal _t8 = lv_buff; gd::native_array_set_index(gd_ctx, _t7, _t8, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t9 = this->f_buffAmplificationChances; gd::GdVal _t10 = lv_buff; gd::native_array_set_index(gd_ctx, _t9, _t10, gd::GdVal::from_float(0.0)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getNumItemMetrics_227, nullptr, 0, _out); return _out; })()}; return gd::native_inline_call(gd_ctx, this->f_itemMetrics, gd::SYM_resize, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, this->f_itemMetrics, gd::SYM_fill, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1398), gd::SYM_size, nullptr, 0)}; return gd::native_inline_call(gd_ctx, this->f_statDisplayOverrides, gd::SYM_resize, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, this->f_statDisplayOverrides, gd::SYM_fill, _ca, 1); })();
    if (gd_ctx.native_resolved_dispatch) {
        if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(3);
        for (int64_t color = 0; color < 4; ++color) {
            gd::GdVal lv_color = gd::GdVal::from_int(color);
            { gd::GdVal _t14 = this->f_currentAffectedItems; gd::GdVal _t15 = lv_color; gd::native_array_set_index(gd_ctx, _t14, _t15, gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))); }
        }
    } else {
        gd::GdVal _t11 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t12 = (_t11.kind == gd::GdVal::Kind::Arr) ? _t11.arr : nullptr;
        uint32_t _len__t13 = _t12 ? _t12->len : 0u;
        for (uint32_t _t13 = 0; _t13 < _len__t13; ++_t13) {
            gd::GdVal lv_color = _t12->data[_t13];
            { gd::GdVal _t14 = this->f_currentAffectedItems; gd::GdVal _t15 = lv_color; gd::native_array_set_index(gd_ctx, _t14, _t15, gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))); }
        }
    }
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasCharacter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_placed) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_character_, gd::GdVal::null())))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_character(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_character_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_opponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_character_}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_otherCharacter_1477, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isPlaced(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_placed;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isCoreItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isPlayer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_character_, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, this->f_character_, SYM_GEN_playerId_1046), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    return (gd::gd_truth(gd::gd_in(lv_type, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_types_1544))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(lv_type, this->f_dynamicTypes))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTypeMultiplicity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_type}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })()) ? (gd::GdVal::from_int(1LL)) : (gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasTag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_tag = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_tag}; return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_hasTag_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_isWeapon_82, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isGem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBattleRageItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_hasBattleRageEffect_1690);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_gainsStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_bitand(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gainedStacks_1714), lv_stackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removesStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_bitand(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_removedStacks_1715), lv_stackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_usesStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_bitand(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_usedStacks_1716), lv_stackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })());
    }
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_152, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasTag_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canBeEmpowered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_82, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canDamage_89, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canActivate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_canActivate_91);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getSpeed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::native_array_index(gd_ctx, this->f_statDisplayOverrides, gd::GdVal::from_int(3LL));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_73, nullptr, 0))) {
        gd::GdVal lv_speed_ = gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_speed_93, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStackSpeedMods_94, nullptr, 0));
        gd::GdVal lv_modifiedSpeed = gd::GdVal::from_float(0.0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_speed_, gd::GdVal::from_int(0LL))))) {
            lv_modifiedSpeed = gd::gd_coerce_float(gd::gd_add(gd_ctx, gd::GdVal::from_float(1.0), lv_speed_));
        }
        else {
            lv_modifiedSpeed = gd::gd_coerce_float(gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), gd::gd_sub(gd::GdVal::from_float(1.0), lv_speed_)));
        }
        lv_modifiedSpeed = gd::gd_coerce_float(gd::gd_clamp(lv_modifiedSpeed, gd::GdVal::from_float(0.1), gd::GdVal::from_float(10.0)));
        return lv_modifiedSpeed;
    }
    else {
        return gd::GdVal::from_float(1.0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_speed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_speedScale;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStackSpeedMods(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ch = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0);
    return gd::gd_mul(gd::gd_sub(gd::native_inline_call(gd_ctx, lv_ch, SYM_GEN_getHeat_1251, nullptr, 0), gd::native_inline_call(gd_ctx, lv_ch, SYM_GEN_getCold_1254, nullptr, 0)), gd::GdVal::from_float(0.02));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1679), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isCooldownActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f__cooldown_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setCooldownActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_active = gd::gd_coerce_bool(lv_active);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f__cooldown_active, lv_active))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_in_item_physics_pass_1447))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_epoch = gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f__cooldown_changed_epoch, lv_epoch)))) {
            this->f__cooldown_changed_epoch = lv_epoch;
            if (gd::gd_truth(lv_active)) {
                this->f__cooldown_blocked_epoch = lv_epoch;
            }
        }
    }
    gd::native_active_cooldown_store(this->rt_ctx_,this->f__cooldown_active,lv_active);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_activateCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCooldownActive_97, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_deactivateCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCooldownActive_97, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_baseCooldownOverride;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseCooldownIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_index = gd::gd_coerce_int(lv_index);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_index, gd::GdVal::from_int(0LL))))) {
        return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1679);
    }
    else {
        return gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_extraCds_1680), gd::gd_sub(lv_index, gd::GdVal::from_int(1LL)));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::native_array_index(gd_ctx, this->f_statDisplayOverrides, gd::GdVal::from_int(4LL));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    return this->f_baseCooldownOverride;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCooldownIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_index = gd::gd_coerce_int(lv_index);
    return ([&]() { gd::GdVal _ca[] = {lv_index}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_101, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getModifiedCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_102, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getModifiedCooldownIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_index = gd::gd_coerce_int(lv_index);
    return gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_index}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldownIndex_103, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCooldownEncoded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_iterationCooldown, gd::GdVal::from_int(0LL))))) {
        return gd::gd_neg(gd::GdVal::from_int(1LL));
    }
    gd::GdVal lv_relProgress = gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_triggerTime, this->f_iterationCooldown));
    gd::GdVal lv_progressPerSecond = gd::GdVal::from_float(0.0);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_96, nullptr, 0))) {
        lv_progressPerSecond = gd::gd_coerce_float(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0), this->f_iterationCooldown));
    }
    else {
        lv_progressPerSecond = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    }
    gd::GdVal lv_value = gd::gd_shl(gd::gd_coerce_int(gd::gd_mul(lv_relProgress, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_cdEncodingFactor_1))), gd::GdVal::from_int(32LL));
    lv_value = gd::gd_add(gd_ctx, lv_value, gd::gd_coerce_int(gd::gd_mul(lv_progressPerSecond, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_cdEncodingFactor_1))));
    return lv_value;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_adjustCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_adjustedCooldown = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_102, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(3LL)))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_below_master_1414)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_lobbies_mode_1416)))))) : gd::GdVal::from_bool(false)))) {
        lv_adjustedCooldown = gd::gd_mul(lv_adjustedCooldown, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.975), gd::GdVal::from_float(1.05)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })());
    }
    else {
        lv_adjustedCooldown = gd::gd_mul(lv_adjustedCooldown, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.95), gd::GdVal::from_float(1.05)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })());
    }
    return lv_adjustedCooldown;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setBaseCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newBaseCd = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_baseCooldownOverride = gd::gd_coerce_float(lv_newBaseCd);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBaseCooldown_110, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_resetBaseCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1679)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBaseCooldown_108, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_updateBaseCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cdProgress = gd::gd_div(gd_ctx, this->f_triggerTime, this->f_iterationCooldown);
    this->f_iterationCooldown = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_107, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_mul(lv_cdProgress, this->f_iterationCooldown));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(4LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseStaminaCost(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_staminaCost_1677);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStaminaCost(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::native_array_index(gd_ctx, this->f_statDisplayOverrides, gd::GdVal::from_int(2LL));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    return gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaCost_111, nullptr, 0), this->f_staminaFactor);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isStaminaModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaCost_111, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_112, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isStatModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_statVal = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_statVal, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_int(0LL);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_statVal, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_int(1LL);
    }
    else {
        return gd::GdVal::from_int(2LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t16 = this->f_statDisplayOverrides; gd::GdVal _t17 = lv_stat; gd::native_array_set_index(gd_ctx, _t16, _t17, lv_value); }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_queueTooltipUpdate_708, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_amount, gd::GdVal::null())))) {
        lv_amount = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_112, nullptr, 0);
    }
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStamina_116, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_res, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(7LL), gd::GdVal::from_int(1LL), gd::GdVal::null(), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_230, _ca, 4); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_OutOfStamina_1373, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playOutOfStaminaAnimation_118, nullptr, 0);
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[11]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_amount}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_int(4LL), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_staminaChanged_233, _ca, 3); })();
    }
    return lv_res;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_drainStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_drainStamina_117, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_playOutOfStaminaAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isPlayer_78, nullptr, 0))) {
        gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_out_of_stamina_count_1432, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_out_of_stamina_count_1432), gd::GdVal::from_int(1LL)));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playOutOfStaminaAnimation_118, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cacheAffectedItemsForCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t18 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t19 = (_t18.kind == gd::GdVal::Kind::Arr) ? _t18.arr : nullptr;
        uint32_t _len__t20 = _t19 ? _t19->len : 0u;
        for (uint32_t _t20 = 0; _t20 < _len__t20; ++_t20) {
            gd::GdVal lv_color = _t19->data[_t20];
            { gd::GdVal _t21 = this->f_cachedAffectedItems; gd::GdVal _t22 = lv_color; gd::native_array_set_index(gd_ctx, _t21, _t22, gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_currentAffectedItems, lv_color), gd::SYM_keys, nullptr, 0)); }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    this->f_placedByPlayer = lv__placedByPlayer;
    this->f_placed = gd::GdVal::from_bool(true);
    gd::native_timer_fields_changed(this->rt_ctx_); this->f_inventory = lv__inventory;
    this->f_occupiedCells = lv__occupiedCells;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_ownerType, gd::GdVal::from_int(10LL))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_inventory, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), SYM_GEN_inventory_5))))) : gd::GdVal::from_bool(false)))) {
            this->f_ownerType = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
        }
        else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_75), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_inventory, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_75), SYM_GEN_inventory_5))))) : gd::GdVal::from_bool(false)))) {
            this->f_ownerType = gd::gd_coerce_int(gd::GdVal::from_int(3LL));
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedCells_416, nullptr, 0);
    {
        gd::GdVal _t23 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t24 = (_t23.kind == gd::GdVal::Kind::Arr) ? _t23.arr : nullptr;
        uint32_t _len__t25 = _t24 ? _t24->len : 0u;
        for (uint32_t _t25 = 0; _t25 < _len__t25; ++_t25) {
            gd::GdVal lv_color = _t24->data[_t25];
            {
                gd::GdVal _t26 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
                gd::GdArr* _t27 = (_t26.kind == gd::GdVal::Kind::Arr) ? _t26.arr : nullptr;
                uint32_t _len__t28 = _t27 ? _t27->len : 0u;
                for (uint32_t _t28 = 0; _t28 < _len__t28; ++_t28) {
                    gd::GdVal lv_item = _t27->data[_t28];
                    { gd::GdVal _t29 = gd::native_array_index(gd_ctx, this->f_currentAffectedItems, lv_color); gd::GdVal _t30 = lv_item; gd::native_array_set_index(gd_ctx, _t29, _t30, gd::GdVal::from_bool(true)); }
                    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemAdded_435, _ca, 2); })();
                }
            }
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAddToInventory_419, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_registerWithInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_inventory, this->f_occupiedCells, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addToInventory_120, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedItemsForCombat_119, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_chanceRng, SYM_GEN_reset_1025, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_damageRangeRng, SYM_GEN_reset_1025, nullptr, 0);
    {
        gd::GdVal _t31 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0));
        gd::GdArr* _t32 = (_t31.kind == gd::GdVal::Kind::Arr) ? _t31.arr : nullptr;
        uint32_t _len__t33 = _t32 ? _t32->len : 0u;
        for (uint32_t _t33 = 0; _t33 < _len__t33; ++_t33) {
            gd::GdVal lv_gem = _t32->data[_t33];
            (void)gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_prepare_122, nullptr, 0);
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPrepare_123, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t34 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0));
        gd::GdArr* _t35 = (_t34.kind == gd::GdVal::Kind::Arr) ? _t34.arr : nullptr;
        uint32_t _len__t36 = _t35 ? _t35->len : 0u;
        for (uint32_t _t36 = 0; _t36 < _len__t36; ++_t36) {
            gd::GdVal lv_gem = _t35->data[_t36];
            (void)gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_preCombatStart_124, nullptr, 0);
        }
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_95, nullptr, 0))) {
        this->f_iterationCooldown = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_107, nullptr, 0));
        this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_98, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPreCombatStart_125, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasStartofBattle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t37 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0));
        gd::GdArr* _t38 = (_t37.kind == gd::GdVal::Kind::Arr) ? _t37.arr : nullptr;
        uint32_t _len__t39 = _t38 ? _t38->len : 0u;
        for (uint32_t _t39 = 0; _t39 < _len__t39; ++_t39) {
            gd::GdVal lv_gem = _t38->data[_t39];
            (void)gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_combatStart_127, nullptr, 0);
        }
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasStartofBattle_126, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_postCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t40 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0));
        gd::GdArr* _t41 = (_t40.kind == gd::GdVal::Kind::Arr) ? _t40.arr : nullptr;
        uint32_t _len__t42 = _t41 ? _t41->len : 0u;
        for (uint32_t _t42 = 0; _t42 < _len__t42; ++_t42) {
            gd::GdVal lv_gem = _t41->data[_t42];
            (void)gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_postCombatStart_128, nullptr, 0);
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPostCombatStart_129, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onPostCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_repeatCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPreCombatStart_125, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPostCombatStart_129, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCooldownActive_97, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disconnectCombat_502, nullptr, 0);
    {
        gd::GdVal _t43 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0));
        gd::GdArr* _t44 = (_t43.kind == gd::GdVal::Kind::Arr) ? _t43.arr : nullptr;
        uint32_t _len__t45 = _t44 ? _t44->len : 0u;
        for (uint32_t _t45 = 0; _t45 < _len__t45; ++_t45) {
            gd::GdVal lv_gem = _t44->data[_t45];
            (void)gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_combatEnd_131, nullptr, 0);
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onCombatEnd_132, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_resetCombatState(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1679));
    this->f_speedScale = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMinDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    {
        gd::GdVal _t46 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffPowers);
        gd::GdArr* _t47 = (_t46.kind == gd::GdVal::Kind::Arr) ? _t46.arr : nullptr;
        uint32_t _len__t48 = _t47 ? _t47->len : 0u;
        for (uint32_t _t48 = 0; _t48 < _len__t48; ++_t48) {
            gd::GdVal lv_buff = _t47->data[_t48];
            { gd::GdVal _t49 = this->f_buffPowers; gd::GdVal _t50 = lv_buff; gd::native_array_set_index(gd_ctx, _t49, _t50, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t51 = this->f_buffAmplificationChances; gd::GdVal _t52 = lv_buff; gd::native_array_set_index(gd_ctx, _t51, _t52, gd::GdVal::from_float(0.0)); }
        }
    }
    this->f_critChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critSeverity = gd::gd_coerce_float(Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_BASE_CRIT_SEVERITY_0));
    this->f_bonusChancePercent_mult = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusAccuracy = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleActivationChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleAttackEffectChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)gd::native_inline_call(gd_ctx, this->f_paramMult, gd::SYM_clear, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_paramAdd, gd::SYM_clear, nullptr, 0);
    this->f_numCharges = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, this->f_statDisplayOverrides, gd::SYM_fill, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, this->f_itemMetrics, gd::SYM_fill, _ca, 1); })();
    this->f_consumed = gd::GdVal::from_bool(false);
    this->f_lastActivationTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_activationsThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_triggersThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_lastTriggerTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_triggerTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_iterationCooldown = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    gd::native_active_cooldown_store(this->rt_ctx_,this->f__cooldown_active,gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick(const gd::GdVal* args, int argc) {
    if (!([&] { const auto& active = this->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::gd_truth(active); }())) return gd::GdVal::null();
    auto& context = *static_cast<Gd__gd_core__CoreContext*>(this->f_ctx.obj);
    const auto blocked = this->f__cooldown_blocked_epoch.as_int();
    if (blocked >= 0 && blocked == context.f_timer_pass_epoch.as_int()) return gd::GdVal::null();

    const auto receiver = gd::native_inline_self_type(this->rt_ctx_,this,&META_Gd__gd_core_items__Gems__Gem)
        ? static_cast<Gd__gd_core_items__Gems__Gem*>(this)->fn_character(nullptr, 0)
        : this->f_character_;
    const auto* character = receiver.kind == gd::GdVal::Kind::Obj
        ? static_cast<const Gd__gd_core__CoreCharacter*>(receiver.obj) : nullptr;
    if (character && character->f_stunnedDuration.as_float() > 0.0) return gd::GdVal::null();

    const auto* display = this->f_statDisplayOverrides.arr;
    const auto override = display && display->len > 3 ? display->data[3] : gd::GdVal::null();
    double speed = 1.0;
    const bool uses_override = !override.is_null() && gd::gd_truth(override);
    if (uses_override) {
        speed = override.as_float();
    } else if (gd::gd_truth(this->f_placed) && !this->f_character_.is_null()) {
        if (character) {
            const auto* buffs = character->f_buffs.dict;
            const auto stacks = [&](int64_t type) {
                const auto slot = static_cast<uint32_t>(type - 100);
                const auto* entries = buffs->entries;
                if (slot < buffs->len && entries[slot].key.i == type)
                    return static_cast<const Gd__gd_core__CoreBuff*>(entries[slot].val.obj)->f_current.as_int();
                const auto stack = buffs->get(gd::GdVal::from_int(type));
                return stack.kind == gd::GdVal::Kind::Obj && stack.obj
                    ? static_cast<const Gd__gd_core__CoreBuff*>(stack.obj)->f_current.as_int() : int64_t{0};
            };
            const auto bonus = this->f_speedScale.as_float() + static_cast<double>(stacks(107) - stacks(110)) * 0.02;
            const auto modified = bonus >= 0.0 ? 1.0 + bonus : 1.0 / (1.0 - bonus);
            speed = modified < 0.1 ? 0.1 : (modified > 10.0 ? 10.0 : modified);
        } else {
            speed = this->fn_getSpeed(nullptr, 0).as_float();
        }
    }

    const auto delta = argc > 0 ? args[0].as_float() : 0.0;
    const auto left = uses_override && !override.is_num() ? 0.0 : this->f_triggerTime.as_float() - delta * speed;
    this->f_triggerTime = gd::GdVal::from_float(left);
    auto& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(context.f_show_cooldown_progress)) {
        const gd::GdVal progress[] = {gd::GdVal::from_obj(this), gd::GdVal::from_float(1.0 - left / this->f_iterationCooldown.as_float())};
        gd::native_inline_call(gd_ctx, context.f_hooks, SYM_GEN_showCooldown_794, progress, 2);
    }
    if (this->f_triggerTime.as_float() <= 0.0) gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_newItemTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_timerName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_method = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_isMulti = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_isMulti = gd::gd_coerce_bool(lv_isMulti);
    {
        gd::GdVal _t53 = gd::gd_iter_seq(gd_ctx.arena, this->f_timers);
        gd::GdArr* _t54 = (_t53.kind == gd::GdVal::Kind::Arr) ? _t53.arr : nullptr;
        uint32_t _len__t55 = _t54 ? _t54->len : 0u;
        for (uint32_t _t55 = 0; _t55 < _len__t55; ++_t55) {
            gd::GdVal lv_existing = _t54->data[_t55];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_existing, SYM_GEN_name_7), lv_timerName)))) {
                (void)gd::native_inline_call(gd_ctx, lv_existing, SYM_GEN_stop_1780, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {lv_existing}; return gd::native_inline_call(gd_ctx, this->f_timers, gd::SYM_erase, _ca, 1); })();
                break;
            }
        }
    }
    gd::GdVal lv_t = ([&]() { gd::GdVal _ca[] = {this->f_ctx, gd::GdVal::from_obj(this), lv_timerName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreTimer), gd::SYM_new, _ca, 3); })();
    gd::set_prop(gd_ctx, lv_t, SYM_GEN_multi_1768, lv_isMulti);
    gd::set_prop(gd_ctx, lv_t, SYM_GEN_one_shot_1767, gd::GdVal::from_bool(true));
    gd::set_prop(gd_ctx, lv_t, SYM_GEN_callback_method_1769, lv_method);
    (void)([&]() { gd::GdVal _ca[] = {lv_t}; return gd::native_inline_call(gd_ctx, this->f_timers, gd::SYM_push_back, _ca, 1); })();
    return lv_t;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_timerName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t56 = gd::gd_iter_seq(gd_ctx.arena, this->f_timers);
        gd::GdArr* _t57 = (_t56.kind == gd::GdVal::Kind::Arr) ? _t56.arr : nullptr;
        uint32_t _len__t58 = _t57 ? _t57->len : 0u;
        for (uint32_t _t58 = 0; _t58 < _len__t58; ++_t58) {
            gd::GdVal lv_t = _t57->data[_t58];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_t, SYM_GEN_name_7), lv_timerName)))) {
                return lv_t;
            }
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__tickTimers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    {
        gd::GdVal _t59 = gd::gd_iter_seq(gd_ctx.arena, this->f_timers);
        gd::GdArr* _t60 = (_t59.kind == gd::GdVal::Kind::Arr) ? _t59.arr : nullptr;
        uint32_t _len__t61 = _t60 ? _t60->len : 0u;
        for (uint32_t _t61 = 0; _t61 < _len__t61; ++_t61) {
            gd::GdVal lv_t = _t60->data[_t61];
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, lv_t, SYM_GEN_tick_1516, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_tickTimersPass(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__tickTimers_137, _ca, 1); })();
    {
        gd::GdVal _t62 = gd::gd_iter_seq(gd_ctx.arena, this->f_gems);
        gd::GdArr* _t63 = (_t62.kind == gd::GdVal::Kind::Arr) ? _t62.arr : nullptr;
        uint32_t _len__t64 = _t63 ? _t63->len : 0u;
        for (uint32_t _t64 = 0; _t64 < _len__t64; ++_t64) {
            gd::GdVal lv_gem = _t63->data[_t64];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_gem, gd::GdVal::null())))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN__tickTimers_137, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rebuildTimerSeen(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t65 = gd::gd_iter_seq(gd_ctx.arena, this->f_timers);
        gd::GdArr* _t66 = (_t65.kind == gd::GdVal::Kind::Arr) ? _t65.arr : nullptr;
        uint32_t _len__t67 = _t66 ? _t66->len : 0u;
        for (uint32_t _t67 = 0; _t67 < _len__t67; ++_t67) {
            gd::GdVal lv_t = _t66->data[_t67];
            (void)gd::native_inline_call(gd_ctx, lv_t, SYM_GEN_rebuildSeen_1786, nullptr, 0);
        }
    }
    {
        gd::GdVal _t68 = gd::gd_iter_seq(gd_ctx.arena, this->f_gems);
        gd::GdArr* _t69 = (_t68.kind == gd::GdVal::Kind::Arr) ? _t68.arr : nullptr;
        uint32_t _len__t70 = _t69 ? _t69->len : 0u;
        for (uint32_t _t70 = 0; _t70 < _len__t70; ++_t70) {
            gd::GdVal lv_gem = _t69->data[_t70];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_gem, gd::GdVal::null())))) {
                (void)gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_rebuildTimerSeen_139, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerAni_1696))) {
        gd::GdVal lv_flicker_delay = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerMinDist_1697), gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerMaxDist_1698)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
        if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_training_start_1452)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::gd_coerce_float(lv_flicker_delay)}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_addTrainingFlicker_1503, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[12]), gd::gd_coerce_float(lv_flicker_delay)}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_callDelayed_1479, _ca, 3); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[14])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), ([&]() { gd::GdVal _ca[] = {lv_flicker_delay}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[15]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_rng_1406), gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_connectorReadyRoll_1701))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    }
    if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gemRoll_1702))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(10LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    }
    this->f_hasPreDealDamageEarlyEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasPreDealDamageLateEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasDealtDamageEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeReceivedEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeLeftEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initSockets_388, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[14])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[0]), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[15]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_rng_1406), gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_flickerPlayAni(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[17]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[14])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[15]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_rng_1406), gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerMinSpeed_1699), gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerMaxSpeed_1700)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_checkTriggerCount(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_limit = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_util_time = gd::gd_coerce_float(gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_replay_util_time_1455), gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_util_time, this->f_triggersThisFrame)))) {
        this->f_triggersThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
        this->f_lastTriggerTime = gd::gd_coerce_float(lv_util_time);
    }
    else {
        this->f_triggersThisFrame = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_triggersThisFrame, gd::GdVal::from_int(1LL)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_triggersThisFrame, lv_limit)))) {
            return gd::GdVal::from_bool(false);
        }
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    const gd::GdVal trace_rng = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406);
    if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, trace_rng, SYM_GEN_oracle_trace_1729)) &&
        gd::gd_truth(gd::native_inline_get_prop(gd_ctx, trace_rng, SYM_GEN__stacktrace_1731))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::gd_coerce_int(this->f_ownerType), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[19]), ([&]() { gd::GdVal _ca[] = {this->f_triggerTime}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[20])), ([&]() { gd::GdVal _ca[] = {this->f_iterationCooldown}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[21])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[22])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    } else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0);
    }
    this->f_iterationCooldown = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_107, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_triggerTime, this->f_iterationCooldown));
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_144, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_doubleActivationChance, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_doubleActivationChance}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flip_1735, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_144, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    const gd::GdVal trace_rng = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406);
    if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, trace_rng, SYM_GEN_oracle_trace_1729)) &&
        gd::gd_truth(gd::native_inline_get_prop(gd_ctx, trace_rng, SYM_GEN__stacktrace_1731))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[23]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[14])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[24]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[25])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onAfterEffectFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__consume = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_showCooldownSmooth_793, _ca, 3); })();
    if (gd::gd_truth(lv__consume)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_advanceCooldownPercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_96, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_reduction = gd::gd_mul(gd::gd_div(gd_ctx, lv_amount, gd::GdVal::from_float(100.0)), this->f_iterationCooldown);
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_triggerTime, lv_reduction));
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_triggerTime, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_143, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_96, nullptr, 0))))) {
            return gd::GdVal::null();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_advanceCooldownSeconds(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_96, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_triggerTime, gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0))));
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_triggerTime, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_143, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_96, nullptr, 0))))) {
            return gd::GdVal::null();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(6LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playDropSound_149, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_activate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_playCombatAni = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_consume = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_animationOverride = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkActivationLimit_151, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1305))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBag_83, nullptr, 0))))) {
            lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Activation_1380, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[26]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(4LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_230, _ca, 1); })();
        }
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_95, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL), gd::GdVal::null(), gd::GdVal::from_bool(false), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 5); })();
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_animationOverride, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_animationOverride, lv_consume}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playActivationAnimation_778, _ca, 3); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationSound_148, nullptr, 0);
    if (gd::gd_truth(lv_playCombatAni)) {
        gd::GdVal lv_anim_hit = gd::GdVal::from_bool(true);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_damageRes, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
            lv_anim_hit = gd::GdVal::from_bool(false);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1695)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[28]), ([&]() { gd::GdVal _ca[] = {lv_anim_hit}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    if (gd::gd_truth((gd::gd_truth(lv_playCombatAni) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1695))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.2)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_damageRes, gd::GdVal::null())))) {
        gd::GdVal lv_ch = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_ch, gd::GdVal::null())))) {
            (void)gd::native_inline_call(gd_ctx, lv_ch, SYM_GEN_playActivateAnimation_1142, nullptr, 0);
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playActivationSound_148, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_checkActivationLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), this->f_lastActivationTime)))) {
        this->f_activationsThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
        this->f_lastActivationTime = gd::gd_coerce_float(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411));
    }
    else {
        this->f_activationsThisFrame = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_activationsThisFrame, gd::GdVal::from_int(1LL)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_activationsThisFrame, gd::GdVal::from_int(3LL))))) {
            return gd::GdVal::from_bool(false);
        }
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseMinDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseMaxDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_maxDam_1676);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseAverageDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_152, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMaxDamage_153, nullptr, 0)), gd::GdVal::from_float(2.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTypedDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_typedDmgFactor = gd::GdVal::from_float(1.0);
    {
        gd::GdVal _t71 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, lv_damSource, SYM_GEN_types_1544));
        gd::GdArr* _t72 = (_t71.kind == gd::GdVal::Kind::Arr) ? _t71.arr : nullptr;
        uint32_t _len__t73 = _t72 ? _t72->len : 0u;
        for (uint32_t _t73 = 0; _t73 < _len__t73; ++_t73) {
            gd::GdVal lv_type = _t72->data[_t73];
            lv_typedDmgFactor = gd::gd_add(gd_ctx, lv_typedDmgFactor, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_typedDamageFactors_1080), lv_type));
        }
    }
    return lv_typedDmgFactor;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMinDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damSource = (_argc > 0) ? _args[0] : (this->f_damageSource);
    gd::GdVal lv_override = gd::native_array_index(gd_ctx, this->f_statDisplayOverrides, gd::GdVal::from_int(0LL));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    gd::GdVal lv_minDam = gd::gd_ceil(gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675), this->f_bonusMinDam));
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_73, nullptr, 0))) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
            lv_minDam = gd::gd_add(gd_ctx, lv_minDam, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBuffDamageMod_1258, nullptr, 0));
        }
        lv_minDam = gd::gd_mul(lv_minDam, ([&]() { gd::GdVal _ca[] = {lv_damSource}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTypedDamageFactor_155, _ca, 1); })());
    }
    lv_minDam = gd::gd_round(gd::gd_mul(lv_minDam, this->f_bonusDamageFactor));
    lv_minDam = gd::gd_max(lv_minDam, gd::GdVal::from_int(0LL));
    return lv_minDam;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMaxDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damSource = (_argc > 0) ? _args[0] : (this->f_damageSource);
    gd::GdVal lv_override = gd::native_array_index(gd_ctx, this->f_statDisplayOverrides, gd::GdVal::from_int(1LL));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    gd::GdVal lv_maxDam = gd::gd_ceil(gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_maxDam_1676), this->f_bonusMaxDam));
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_73, nullptr, 0))) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
            lv_maxDam = gd::gd_add(gd_ctx, lv_maxDam, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBuffDamageMod_1258, nullptr, 0));
        }
        lv_maxDam = gd::gd_mul(lv_maxDam, ([&]() { gd::GdVal _ca[] = {lv_damSource}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTypedDamageFactor_155, _ca, 1); })());
    }
    lv_maxDam = gd::gd_round(gd::gd_mul(lv_maxDam, this->f_bonusDamageFactor));
    lv_maxDam = gd::gd_max(lv_maxDam, gd::GdVal::from_int(0LL));
    return lv_maxDam;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAverageDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_156, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_157, nullptr, 0)), gd::GdVal::from_float(2.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_randDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_156, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_157, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getModifiedEffectDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseDamage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_modifiedDamage = lv_baseDamage;
    lv_modifiedDamage = gd::gd_mul(lv_modifiedDamage, gd::gd_add(gd_ctx, gd::GdVal::from_float(1.0), gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_typedDamageFactors_1080), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2656))));
    lv_modifiedDamage = gd::gd_mul(lv_modifiedDamage, this->f_bonusDamageFactor);
    return lv_modifiedDamage;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addBonusDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_removable = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_removable = gd::gd_coerce_bool(lv_removable);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_damage, gd::GdVal::from_int(0LL))))) {
        this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusMinDam, lv_damage));
        this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusMaxDam, lv_damage));
        if (gd::gd_truth(lv_removable)) {
            this->f_removableDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_removableDam, lv_damage));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
        if (gd::gd_truth(lv_removable)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(16LL), lv_damage}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_379, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeVaryingDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_damage, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addMinDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusMinDam, lv_damage));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addMaxDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusMaxDam, lv_damage));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRemovableDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_removableDam;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeBonusDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMinDam, this->f_removableDam));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMaxDam, this->f_removableDam));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setBonusDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_factor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusDamageFactor = gd::gd_coerce_float(lv_factor);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_chance_1681);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseChance2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_chance2_1682);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_applyBonusChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toChance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_index = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_index, gd::GdVal::from_int(1LL))))) {
        return gd::gd_mul(gd::gd_add(gd_ctx, lv_toChance, this->f_bonusChancePercent_additive1), gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_int(100LL), this->f_bonusChancePercent_mult), gd::GdVal::from_float(100.0)));
    }
    else {
        return gd::gd_mul(gd::gd_add(gd_ctx, lv_toChance, this->f_bonusChancePercent_additive2), gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_int(100LL), this->f_bonusChancePercent_mult), gd::GdVal::from_float(100.0)));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::native_array_index(gd_ctx, this->f_statDisplayOverrides, gd::GdVal::from_int(7LL));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    return gd::gd_clamp(([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_168, nullptr, 0), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_170, _ca, 2); })(), gd::GdVal::from_int(0LL), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getChance2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::native_array_index(gd_ctx, this->f_statDisplayOverrides, gd::GdVal::from_int(8LL));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    return gd::gd_clamp(([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance2_169, nullptr, 0), gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_170, _ca, 2); })(), gd::GdVal::from_int(0LL), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rollChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_chance, gd::GdVal::null())))) {
        lv_chance = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_168, nullptr, 0);
    }
    gd::GdVal lv__target = ([&]() { gd::GdVal _ca[] = {lv_chance, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_170, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[0])))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673), gd::GdVal::from_str(&battle_string_literals[29]))))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    gd::GdVal lv__rc = ([&]() { gd::GdVal _ca[] = {lv__target}; return gd::native_inline_call(gd_ctx, this->f_chanceRng, SYM_GEN_rollPercent_1760, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[0])))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673), gd::GdVal::from_str(&battle_string_literals[29]))))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[30]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[14])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[31]), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_chance, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_170, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[32]), ([&]() { gd::GdVal _ca[] = {lv__rc}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    return lv__rc;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rollChance2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_chance2_1682), gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_170, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, this->f_chanceRng, SYM_GEN_rollPercent_1760, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addBonusChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusChancePercent_mult = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusChancePercent_mult, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(7LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(8LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addBonusChance_additive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount2 = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusChancePercent_additive1, lv_amount1));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_amount2, gd::GdVal::null())))) {
        this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusChancePercent_additive2, lv_amount1));
    }
    else {
        this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusChancePercent_additive2, lv_amount2));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(7LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_amount2, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(8LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusAccuracy = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusAccuracy, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_clamp(this->f_critChancePercent, gd::GdVal::from_int(0LL), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critChancePercent, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critChancePercent = gd::gd_coerce_float(gd::gd_sub(this->f_critChancePercent, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critChancePercent, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_critTokens;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critTokens = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_critTokens, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useCritToken(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_critTokens = gd::gd_coerce_int(gd::gd_sub(this->f_critTokens, gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addCritSeverity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critSeverity = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critSeverity, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCritSeverity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_critSeverity;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rollDoubleAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {this->f_doubleAttackEffectChance}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flip_1735, _ca, 1); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_index}; return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP_m(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_baseVal = ([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return ([&]() { gd::GdVal _ca[] = {lv_paramName, lv_baseVal}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getParamModified_190, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getParamModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_baseVal = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_baseParam = gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_paramBases_1712), lv_paramName);
    return gd::gd_mul(gd::gd_add(gd_ctx, lv_baseVal, ([&]() { gd::GdVal _ca[] = {lv_baseParam, gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, this->f_paramAdd, gd::SYM_get, _ca, 2); })()), ([&]() { gd::GdVal _ca[] = {lv_baseParam, gd::GdVal::from_float(1.0)}; return gd::native_inline_call(gd_ctx, this->f_paramMult, gd::SYM_get, _ca, 2); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_modifyParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    { gd::GdVal _t74 = this->f_paramMult; gd::GdVal _t75 = lv_paramName; gd::native_array_set_index(gd_ctx, _t74, _t75, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_paramName, gd::GdVal::from_float(1.0)}; return gd::native_inline_call(gd_ctx, this->f_paramMult, gd::SYM_get, _ca, 2); })(), lv_amount)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_modifyParam_add(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    { gd::GdVal _t76 = this->f_paramAdd; gd::GdVal _t77 = lv_paramName; gd::native_array_set_index(gd_ctx, _t76, _t77, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_paramName, gd::GdVal::from_float(0.0)}; return gd::native_inline_call(gd_ctx, this->f_paramAdd, gd::SYM_get, _ca, 2); })(), lv_amount)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_accuracy_1545);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_acc = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseAccuracy_193, nullptr, 0);
    lv_acc = gd::gd_add(gd_ctx, lv_acc, this->f_bonusAccuracy);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_73, nullptr, 0))) {
        lv_acc = gd::gd_add(gd_ctx, lv_acc, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBuffAccuracyMod_1259, nullptr, 0));
    }
    return lv_acc;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAmplificationChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_array_index(gd_ctx, this->f_buffAmplificationChances, lv_buffType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeAmplificiationChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_chance = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t78 = this->f_buffAmplificationChances; gd::GdVal _t79 = lv_buffType; gd::native_array_set_index(gd_ctx, _t78, _t79, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t78, _t79), lv_chance)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeAmplificiationChancePercent_allBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t80 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t81 = (_t80.kind == gd::GdVal::Kind::Arr) ? _t80.arr : nullptr;
        uint32_t _len__t82 = _t81 ? _t81->len : 0u;
        for (uint32_t _t82 = 0; _t82 < _len__t82; ++_t82) {
            gd::GdVal lv_buff = _t81->data[_t82];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_chance}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeAmplificiationChancePercent_196, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeAmplificiationChancePercent_allDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t83 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t84 = (_t83.kind == gd::GdVal::Kind::Arr) ? _t83.arr : nullptr;
        uint32_t _len__t85 = _t84 ? _t84->len : 0u;
        for (uint32_t _t85 = 0; _t85 < _len__t85; ++_t85) {
            gd::GdVal lv_buff = _t84->data[_t85];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_chance}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeAmplificiationChancePercent_196, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeNullifyChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_chance = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t86 = this->f_buffAmplificationChances; gd::GdVal _t87 = lv_buffType; gd::native_array_set_index(gd_ctx, _t86, _t87, gd::gd_sub(gd::native_array_index(gd_ctx, _t86, _t87), lv_chance)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveReflectStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffReflectStacks_1186, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_type, gd::gd_round(gd::gd_mul(lv_amount, gd::native_array_index(gd_ctx, this->f_buffPowers, lv_type))), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_gainStacks_1030, _ca, 4); })();
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveStacksTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_type, gd::gd_round(gd::gd_mul(lv_amount, gd::native_array_index(gd_ctx, this->f_buffPowers, lv_type))), lv_duration, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_gainStacksTemporary_1218, _ca, 5); })();
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_canTriggerEffects = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_amount, gd::GdVal::null())))) {
        lv_amount = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(100LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
            if (gd::gd_truth(lv_canTriggerEffects)) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[33]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0), lv_event}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
            }
            return lv_event;
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_block_1678);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseBlock_206, _ca, 3); })();
    if (gd::gd_truth(lv_event)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countDamage_225, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseBlock_206, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stealStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_removeEvent = ([&]() { gd::GdVal _ca[] = {lv_type, lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 4); })();
    gd::GdVal lv_giveEvent = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_type, lv_amount, lv_removeEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return lv_giveEvent;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(104LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(103LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_int(108LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_selfInflictPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(108LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_int(109LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(102LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(101LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(105LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(106LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(107LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(110LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_dealDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_damageSource, SYM_GEN_updateItem_1553, _ca, 1); })();
    gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {this->f_damageSource, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_dealDamage_220, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[34]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_dealEffectDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv__damageSource = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__damageSource, gd::GdVal::null())))) {
        lv__damageSource = this->f_damageSource;
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_damage}; return gd::native_inline_call(gd_ctx, lv__damageSource, SYM_GEN_updateEffect_1554, _ca, 2); })();
    gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv__damageSource, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_takeDamage_1148, _ca, 2); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_preDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[35]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_preDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[36]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_dealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[37]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_countDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_amount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_230, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf_getNumNonStackItemMetrics(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    if (gd_ctx.native_resolved_dispatch) { if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(2); return gd::GdVal::from_int(14LL); }
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(8LL), gd::gd_mul(gd::gd_sub(gd::GdVal::from_int(9LL), gd::GdVal::from_int(8LL)), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf_getNumItemMetrics(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    if (gd_ctx.native_resolved_dispatch) { if (gd_ctx.native_resolved_collect) gd::native_static_setup_hit(2); return gd::GdVal::from_int(80LL); }
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(8LL), gd::gd_mul(gd::gd_sub(gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1396), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(8LL)), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf_getStackMetricIndex(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_stackChangeType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stackChangeType = gd::gd_coerce_int(lv_stackChangeType);
    gd::GdVal lv_stackType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_stackType = gd::gd_coerce_int(lv_stackType);
    gd::GdVal lv_offsetStackType = gd::gd_sub(lv_stackType, gd::GdVal::from_int(100LL));
    gd::GdVal lv_changeTypeOffset = gd::gd_mul(lv_stackChangeType, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_numStackTypes_1394, nullptr, 0));
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getNumNonStackItemMetrics_226, nullptr, 0, _out); return _out; })(), lv_changeTypeOffset), lv_offsetStackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf_getMultiMetricIndex(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_stackChangeType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stackChangeType = gd::gd_coerce_int(lv_stackChangeType);
    gd::GdVal lv_metric = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_metric = gd::gd_coerce_int(lv_metric);
    gd::GdVal lv_offsetMetric = gd::gd_sub(lv_metric, gd::GdVal::from_int(8LL));
    gd::GdVal lv_numMultiMetrics = gd::gd_mul(lv_offsetMetric, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0));
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_int(8LL), lv_numMultiMetrics), lv_stackChangeType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_metricsIndex = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_withNextEvent = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    { gd::GdVal _t88 = this->f_itemMetrics; gd::GdVal _t89 = lv_metricsIndex; gd::native_array_set_index(gd_ctx, _t88, _t89, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t88, _t89), lv_amount)); }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_metricsIndex, lv_playerId, lv_withNextEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_snapshotItemMetric_1383, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_metric = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_array_index(gd_ctx, this->f_itemMetrics, lv_metric);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stackChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stackType = gd::gd_coerce_int(lv_stackType);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_onPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_onPlayer = gd::gd_coerce_bool(lv_onPlayer);
    gd::GdVal lv_used = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    lv_used = gd::gd_coerce_bool(lv_used);
    gd::GdVal lv_changeType = gd::GdVal::from_int(0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        lv_changeType = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    }
    else {
        if (gd::gd_truth(lv_used)) {
            lv_changeType = gd::gd_coerce_int(gd::GdVal::from_int(4LL));
        }
        else {
            lv_changeType = gd::gd_coerce_int(gd::GdVal::from_int(2LL));
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_onPlayer)))) {
        lv_changeType = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_changeType, gd::GdVal::from_int(1LL)));
    }
    gd::GdVal lv_index = ([&]() { gd::GdVal _ca[] = {lv_changeType, lv_stackType}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getStackMetricIndex_228, _ca, 2, _out); return _out; })();
    gd::GdVal lv_playerId = (gd::gd_truth(lv_onPlayer) ? (gd::GdVal::from_int(0LL)) : (gd::GdVal::from_int(1LL)));
    (void)([&]() { gd::GdVal _ca[] = {lv_index, gd::gd_abs(lv_amount), lv_playerId, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_230, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_staminaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    gd::GdVal lv_changeType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_changeType = gd::gd_coerce_int(lv_changeType);
    gd::GdVal lv_withNextEvent = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_index = ([&]() { gd::GdVal _ca[] = {lv_changeType, gd::GdVal::from_int(8LL)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getMultiMetricIndex_229, _ca, 2, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {lv_index, lv_amount, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046), lv_withNextEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_230, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getName_234, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getIndex_235, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRarity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_rarity_1686);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getShopChance_237, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMainType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_types_1544), gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumStaticTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getTypes_240, nullptr, 0), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, this->f_dynamicTypes, gd::SYM_keys, nullptr, 0), gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_types_1544));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasDynamicType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_fromItem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_type, this->f_dynamicTypes))) {
        if (gd::gd_truth(gd::gd_in(gd::native_inline_call(gd_ctx, lv_fromItem, gd::SYM_get_instance_id, nullptr, 0), gd::native_array_index(gd_ctx, this->f_dynamicTypes, lv_type)))) {
            return gd::GdVal::from_bool(true);
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addDynamicType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_byItem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_type, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_types_1544)))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_dynamicTypes, lv_type, gd::native_inline_call(gd_ctx, lv_byItem, gd::SYM_get_instance_id, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAppend_1792, _ca, 3); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_dynamicTypes, lv_type), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL))))) {
            if (gd::gd_truth(this->f_placed)) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_onItemTypeChanged_458, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeDynamicType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_byItem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_type, lv_byItem}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasDynamicType_241, _ca, 2); })())) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_dynamicTypes, lv_type, gd::native_inline_call(gd_ctx, lv_byItem, gd::SYM_get_instance_id, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictErase_1793, _ca, 3); })();
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_type, this->f_dynamicTypes))))) {
            if (gd::gd_truth(this->f_placed)) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_onItemTypeChanged_458, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_clearDynamicTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_dynamicTypes, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isA(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__descriptor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::native_scalar_eq(this->f_descriptor, lv__descriptor));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isNeutral(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_isNeutral_246, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isTreasure(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_randomUniquePool_1689);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isClassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_classIndex = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_classIndex, gd::GdVal::null())))) {
        return (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_isClassItem_248, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_classIndex}; return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_isAvailableFor_1719, _ca, 1); })())) : gd::GdVal::from_bool(false));
    }
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_isClassItem_248, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isSubclassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_isSubclassItem_249, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isOwnable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(1LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(2LL))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isOwnedByOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(3LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isGateItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isShowCaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::null()));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[38]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_color}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1389, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[39])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[39]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_color}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1389, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_73, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::null())))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getEffectiveOwnerType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_ownerType;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBusy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBoundAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t90 = lv_stat;
        if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(1LL))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMaxDamage_153, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_157, nullptr, 0);
            }
            else {
                return gd::GdVal::from_int(0LL);
            }
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(0LL))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_152, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_156, nullptr, 0);
            }
            else {
                return gd::GdVal::from_int(0LL);
            }
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(5LL))) {
            return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAccuracy_194, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(6LL))) {
            return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCritChancePercent_178, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(3LL))) {
            return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(9LL))) {
            return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldownEncoded_106, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(2LL))) {
            return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_112, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(7LL))) {
            return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(8LL))) {
            return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t90, gd::GdVal::from_int(4LL))) {
            return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_102, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP_check(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_params_1570), lv_index);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP1(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP3(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP4(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP5(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(4LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP6(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(5LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP7(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP8(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(7LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP9(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(8LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP10(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_262, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addSpeed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_speedScale = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_speedScale, lv_amount));
    const bool native_dead_speed_trace=[&] {
        if(!gd_ctx.native_event_kernel || !gd::native_resolved_cached_generated(gd_ctx,this))return false;
        // Nested argument evaluation need not read the descriptor first.
        // Reject unknown getters before speculative field reads; fallback keeps
        // the original expression and its actual callback evaluation order.
        const auto& descriptor=this->f_descriptor;
        if(descriptor.kind!=gd::GdVal::Kind::Obj || !descriptor.obj ||
           &typeid(*descriptor.obj)!=&typeid(Gd__gd_core__CoreItemData))return false;
        if(static_cast<const Gd__gd_core__CoreItemData*>(descriptor.obj)->f_identifier.kind!=gd::GdVal::Kind::Str)return false;
        // Only generated methods are covered by the frozen no-override proof.
        // The original coordinate method may call user getters for object cells.
        const auto& cells=this->f_occupiedCells;
        if(cells.kind!=gd::GdVal::Kind::Arr || !cells.arr)return false;
        for(uint32_t i=0;i<cells.arr->len;++i) {
            const auto& cell=cells.arr->data[i];
            if(cell.kind!=gd::GdVal::Kind::Vec2 || !std::isfinite(cell.v2.x) || !std::isfinite(cell.v2.y))return false;
        }
        // Object formatting can allocate observable instance IDs or call meta().
        switch(lv_amount.kind) {
            case gd::GdVal::Kind::Null:case gd::GdVal::Kind::Bool:
            case gd::GdVal::Kind::Int:case gd::GdVal::Kind::Float:case gd::GdVal::Kind::Str:break;
            default:return false;
        }
        if(this->f_ownerType.kind!=gd::GdVal::Kind::Int || this->f_speedScale.kind!=gd::GdVal::Kind::Float)return false;
        const auto& context_value=this->f_ctx;
        if(context_value.kind!=gd::GdVal::Kind::Obj || !context_value.obj ||
           &typeid(*context_value.obj)!=&typeid(Gd__gd_core__CoreContext))return false;
        const auto& rng_value=static_cast<const Gd__gd_core__CoreContext*>(context_value.obj)->f_rng;
        if(rng_value.kind!=gd::GdVal::Kind::Obj || !rng_value.obj ||
           &typeid(*rng_value.obj)!=&typeid(Gd__gd_core__CoreRng))return false;
        const auto* rng=static_cast<const Gd__gd_core__CoreRng*>(rng_value.obj);
        return !gd::gd_truth(rng->f_oracle_trace) || !gd::gd_truth(rng->f__stacktrace);
    }();
    if(!native_dead_speed_trace) {
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[41])), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_443, nullptr, 0)))), gd::GdVal::from_str(&battle_string_literals[42])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), ([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[43]), ([&]() { gd::GdVal _ca[] = {this->f_speedScale}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceSpeed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_speedScale = gd::gd_coerce_float(gd::gd_sub(this->f_speedScale, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(9LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getDPS(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::gd_mul(gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_156, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_157, nullptr, 0)), gd::GdVal::from_float(0.5)), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_104, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isDPSModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseDPS = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseAverageDamage_154, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_102, nullptr, 0));
    gd::GdVal lv_modifiedDPS = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAverageDamage_158, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_104, nullptr, 0));
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_modifiedDPS, lv_baseDPS)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getDamageRange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_156, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_157, nullptr, 0))))) {
        return gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_156, nullptr, 0)));
    }
    else {
        return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_156, nullptr, 0))), gd::GdVal::from_str(&battle_string_literals[44])), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_157, nullptr, 0))));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isCooldownModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseCd = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldown_100, nullptr, 0);
    gd::GdVal lv_curCd = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_104, nullptr, 0);
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_baseCd, lv_curCd)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isAccuracyModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAccuracy_194, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseAccuracy_193, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isChance1Modified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_168, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isChance2Modified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance2_169, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isDamageModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusDam = gd::gd_sub(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAverageDamage_158, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseAverageDamage_154, nullptr, 0));
    return ([&]() { gd::GdVal _ca[] = {lv_bonusDam}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseStaminaPerSecond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaCost_111, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_102, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStaminaPerSecond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_112, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_104, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isStaminaPerSecondModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseSPS = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaPerSecond_283, nullptr, 0);
    gd::GdVal lv_modifiedSPS = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaPerSecond_284, nullptr, 0);
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_baseSPS, lv_modifiedSPS)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_114, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect(const gd::GdVal* _args, int _argc) {
    if (this->f__behavior.is_null()) return gd::GdVal::from_bool(false);
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1389, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    if (this->f__behavior.is_null()) return gd::GdVal::from_bool(false);
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[46])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1389, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect_tertiary(const gd::GdVal* _args, int _argc) {
    if (this->f__behavior.is_null()) return gd::GdVal::from_bool(false);
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[47])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[47]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1389, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    if (this->f__behavior.is_null()) return gd::GdVal::from_bool(false);
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1389, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect_color(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(0LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_286, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(1LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_secondary_287, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(2LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_tertiary_288, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_lightning_289, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canHealOrLifesteal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[49])}; return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1578, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1578, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canModifyChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_168, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canUseStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaCost_111, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(this->f_hasPreDealDamageEarlyEffect) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_hasPreDealDamageLateEffect)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_hasDealtDamageEffect)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_gainsBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gainedStacks_1714), gd::GdVal::from_int(254LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_usesBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_usedStacks_1716), gd::GdVal::from_int(254LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictsDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gainedStacks_1714), gd::GdVal::from_int(1792LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reactsToCharges(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_hasOnChargeReceivedEffect) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_hasOnChargeLeftEffect)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_fillUpStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_fillUpStamina_300, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRelativeOpponentHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRelativeHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveBuffPower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_power = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t91 = this->f_buffPowers; gd::GdVal _t92 = lv_buffType; gd::native_array_set_index(gd_ctx, _t91, _t92, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t91, _t92), lv_power)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeHealAmp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[49]), lv_amount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_modifyParam_191, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[50]), lv_amount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_modifyParam_191, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeStaminaFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaFactor = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaFactor, gd::gd_div(gd_ctx, lv_amount, gd::GdVal::from_float(100.0))));
    this->f_staminaFactor = gd::gd_coerce_float(gd::gd_max(gd::GdVal::from_int(0LL), this->f_staminaFactor));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addBonusDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_factor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusDamageFactor, lv_factor));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceBonusDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_factor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::gd_sub(this->f_bonusDamageFactor, lv_factor));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceMinDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMinDam, lv_damage));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceMaxDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMaxDam, lv_damage));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceBonusDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_showLabel = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_showLabel = gd::gd_coerce_bool(lv_showLabel);
    gd::GdVal lv_removable = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    lv_removable = gd::gd_coerce_bool(lv_removable);
    this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMinDam, lv_damage));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMaxDam, lv_damage));
    if (gd::gd_truth(lv_removable)) {
        this->f_removableDam = gd::gd_coerce_float(gd::gd_sub(this->f_removableDam, lv_damage));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    if (gd::gd_truth(lv_showLabel)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(16LL), gd::gd_neg(lv_damage)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_379, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_purgeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_purgable = gd::gd_min(lv_damage, this->f_removableDam);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_purgable, gd::GdVal::from_int(0LL))))) {
        this->f_removableDam = gd::gd_coerce_float(gd::gd_sub(this->f_removableDam, lv_purgable));
        this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMinDam, lv_purgable));
        this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMaxDam, lv_purgable));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(16LL), gd::gd_neg(lv_purgable)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_379, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveDoubleActivationChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_doubleActivationChance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_doubleActivationChance, gd::gd_div(gd_ctx, lv__chance, gd::GdVal::from_float(100.0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveDoubleAttackEffectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_doubleAttackEffectChance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_doubleAttackEffectChance, gd::gd_div(gd_ctx, lv__chance, gd::GdVal::from_float(100.0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_gainCritTokens_1184, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveMaxStamina_315, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMaxStaminaTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_filled = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    lv_filled = gd::gd_coerce_bool(lv_filled);
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent, lv_filled}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_gainMaxStaminaTemporary_1268, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_amount, gd::GdVal::null())))) {
        lv_amount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[51])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    }
    lv_amount = ([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_applyTemporaryMaxHealthGain_1161, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL), lv_amount, gd::GdVal::null(), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_230, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeMaxHealthTemporary_1162, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(19LL), lv_amount}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_379, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_gainStamina_1164, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fatigueIncrease = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {lv_fatigueIncrease}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_addFatigueDamage_1195, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_takeFatigueDamage_1196, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_sendCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_durPerTile = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_durPerTile = gd::gd_coerce_float(lv_durPerTile);
    gd::GdVal lv_cells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_speedFactor = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_speedFactor = gd::gd_coerce_float(lv_speedFactor);
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_chargeDuration = gd::gd_mul(lv_durPerTile, gd::gd_sub(gd::native_inline_call(gd_ctx, lv_cells, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
    gd::GdVal lv_inv_cells = ([&]() { gd::GdVal _ca[] = {lv_cells}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__chargeInventoryCells_321, _ca, 1); })();
    gd::GdVal lv_charge = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, lv_charge, SYM_GEN_inventoryCells_1649, lv_inv_cells);
    gd::GdVal lv_half_cell_duration = gd::gd_div(gd_ctx, gd::gd_mul(gd::GdVal::from_float(0.5), gd::gd_div(gd_ctx, lv_chargeDuration, lv_speedFactor)), gd::gd_sub(gd::native_inline_call(gd_ctx, lv_cells, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
    gd::GdVal lv_delay = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t93 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_sub(gd::native_inline_call(gd_ctx, lv_cells, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
        gd::GdArr* _t94 = (_t93.kind == gd::GdVal::Kind::Arr) ? _t93.arr : nullptr;
        uint32_t _len__t95 = _t94 ? _t94->len : 0u;
        for (uint32_t _t95 = 0; _t95 < _len__t95; ++_t95) {
            gd::GdVal lv_i = _t94->data[_t95];
            lv_delay = gd::gd_add(gd_ctx, lv_delay, lv_half_cell_duration);
            lv_delay = gd::gd_add(gd_ctx, lv_delay, lv_half_cell_duration);
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_delay}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_callbackDelays_1650), gd::SYM_append, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_obj(this), lv_charge}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_registerMotion_1500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, gd::GdVal::from_int(1LL), lv_inv_cells}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__chargeEnterCell_323, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_cells, gd::gd_div(gd_ctx, lv_chargeDuration, lv_speedFactor), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_sendCharge_320, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(12LL)), gd::gd_neg(gd::GdVal::from_int(5LL))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.7), gd::GdVal::from_float(1.3)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__chargeInventoryCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_top_left = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_443, nullptr, 0);
    gd::GdVal lv_inv = (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_inventory, gd::GdVal::null()))) ? (this->f_inventory) : (gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_400, nullptr, 0)));
    gd::GdVal lv_out = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t96 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t97 = (_t96.kind == gd::GdVal::Kind::Arr) ? _t96.arr : nullptr;
        uint32_t _len__t98 = _t97 ? _t97->len : 0u;
        for (uint32_t _t98 = 0; _t98 < _len__t98; ++_t98) {
            gd::GdVal lv_c = _t97->data[_t98];
            gd::GdVal lv_v = gd::gd_sub(gd::gd_add(gd_ctx, lv_top_left, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_vec2((gd::native_inline_get_prop(gd_ctx, lv_c, gd::SYM_x)).as_float(), (gd::native_inline_get_prop(gd_ctx, lv_c, gd::SYM_y)).as_float()), this->f_faceDirection}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__rotVecQuarterTurns_322, _ca, 2); })()), gd::native_array_index(gd_ctx, this->f_chargeFrame, gd::gd_mod(gd_ctx, this->f_faceDirection, gd::GdVal::from_int(4LL))));
            gd::GdVal lv_hit_cells = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_v}))}; return gd::native_inline_call(gd_ctx, lv_inv, SYM_GEN_getCellsForGlobalPositions_401, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_hit_cells, gd::GdVal::from_int(0LL))}; return gd::native_inline_call(gd_ctx, lv_out, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return lv_out;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__rotVecQuarterTurns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_v = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_n = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_n = gd::gd_coerce_int(lv_n);
    lv_n = gd::gd_coerce_int(gd::gd_mod(gd_ctx, lv_n, gd::GdVal::from_int(4LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_n, gd::GdVal::from_int(0LL))))) {
        lv_n = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_n, gd::GdVal::from_int(4LL)));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_n, gd::GdVal::from_int(1LL))))) {
        return gd::GdVal::from_vec2((gd::gd_neg(gd::native_inline_get_prop(gd_ctx, lv_v, gd::SYM_y))).as_float(), (gd::native_inline_get_prop(gd_ctx, lv_v, gd::SYM_x)).as_float());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_n, gd::GdVal::from_int(2LL))))) {
        return gd::GdVal::from_vec2((gd::gd_neg(gd::native_inline_get_prop(gd_ctx, lv_v, gd::SYM_x))).as_float(), (gd::gd_neg(gd::native_inline_get_prop(gd_ctx, lv_v, gd::SYM_y))).as_float());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_n, gd::GdVal::from_int(3LL))))) {
        return gd::GdVal::from_vec2((gd::native_inline_get_prop(gd_ctx, lv_v, gd::SYM_y)).as_float(), (gd::gd_neg(gd::native_inline_get_prop(gd_ctx, lv_v, gd::SYM_x))).as_float());
    }
    return lv_v;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__chargeEnterCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cell_index = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_cell_index = gd::gd_coerce_int(lv_cell_index);
    gd::GdVal lv_inv_cells = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::set_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_cell_index, gd::native_inline_call(gd_ctx, lv_inv_cells, gd::SYM_size, nullptr, 0))))) {
        gd::set_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648, gd::GdVal::null());
    }
    else {
        gd::GdVal lv_inv = (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_inventory, gd::GdVal::null()))) ? (this->f_inventory) : (gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_400, nullptr, 0)));
        gd::set_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648, ([&]() { gd::GdVal _ca[] = {gd::native_array_index(gd_ctx, lv_inv_cells, lv_cell_index)}; return gd::native_inline_call(gd_ctx, lv_inv, SYM_GEN_getItemInCell_1607, _ca, 1); })());
    }
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[52]), lv_charge, lv_cell_index}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_call, _ca, 3); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647), gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_charge}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647), SYM_GEN_chargeLeft_325, _ca, 1); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_charge}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), SYM_GEN_chargeReceived_324, _ca, 1); })();
            if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), SYM_GEN_hasOnChargeReceivedEffect_65))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(4.0), gd::GdVal::from_float(4.02)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_chargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_numCharges = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numCharges, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(this->f_hasOnChargeReceivedEffect)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_charge}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_chargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_numCharges = gd::gd_coerce_int(gd::gd_sub(this->f_numCharges, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(this->f_hasOnChargeLeftEffect)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_charge}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeChargedItemStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_flatVal = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_valPerTile = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_previousVal = gd::gd_add(gd_ctx, lv_flatVal, gd::gd_mul(gd::gd_sub(lv_cellIndex, gd::GdVal::from_int(2LL)), lv_valPerTile));
    gd::GdVal lv_newVal = gd::gd_add(gd_ctx, lv_previousVal, lv_valPerTile);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[53]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[41])), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_443, nullptr, 0)))), gd::gd_coerce_int(lv_cellIndex), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[54]), (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647), gd::GdVal::null()))) ? (gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647), SYM_GEN_descriptor_2), SYM_GEN_identifier_1673)))) : (gd::GdVal::from_str(&battle_string_literals[55])))), gd::GdVal::from_str(&battle_string_literals[56])), (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), gd::GdVal::null()))) ? (gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), SYM_GEN_descriptor_2), SYM_GEN_identifier_1673)))) : (gd::GdVal::from_str(&battle_string_literals[55])))), gd::GdVal::from_str(&battle_string_literals[57])), ([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_previousVal)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[58])), ([&]() { gd::GdVal _ca[] = {lv_newVal}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647), gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647), gd::gd_neg(lv_previousVal)}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), lv_valPerTile}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647), gd::gd_neg(lv_previousVal)}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), lv_newVal}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648), lv_newVal}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_heal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_amount, gd::GdVal::null())))) {
        lv_amount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[49])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    }
    else {
        lv_amount = gd::gd_coerce_int(lv_amount);
    }
    gd::GdVal lv_healed = ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_heal_327, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_healthToBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_health = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_health = gd::gd_coerce_float(lv_health);
    gd::GdVal lv_block = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_clampedHealth = gd::gd_min(lv_health, gd::gd_sub(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentHealth_1154, nullptr, 0), gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_clampedHealth, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_clampedHealth, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseHealth_1157, _ca, 3); })();
        lv_block = gd::gd_ceil(gd::gd_mul(gd::gd_div(gd_ctx, lv_clampedHealth, lv_health), lv_block));
        (void)([&]() { gd::GdVal _ca[] = {lv_block, gd::GdVal::from_bool(true), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stealLife(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_lifestealFactor = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(1.0));
    lv_lifestealFactor = gd::gd_coerce_float(lv_lifestealFactor);
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_damage}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_stealLifeDamageSource_1431), SYM_GEN_updateEffect_1554, _ca, 2); })();
    gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_stealLifeDamageSource_1431), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_takeDamage_1148, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_lifestealFactor), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_duration, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_stun_330, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_checkMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useMana_332, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_tryUseMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_curMana = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curMana, lv_amount)))) {
        return gd::GdVal::null();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseMana_1247, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMana_capped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maximum = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    lv_amount = gd::gd_round(gd::gd_mul(lv_amount, gd::native_array_index(gd_ctx, this->f_buffPowers, gd::GdVal::from_int(105LL))));
    gd::GdVal lv_curMana = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_maximum, lv_curMana)))) {
        gd::GdVal lv_missingMana = gd::gd_sub(lv_maximum, lv_curMana);
        gd::GdVal lv_manaGiven = gd::gd_min(lv_amount, lv_missingMana);
        (void)([&]() { gd::GdVal _ca[] = {lv_manaGiven, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_gainMana_1246, _ca, 3); })();
        return gd::gd_sub(lv_amount, lv_manaGiven);
    }
    else {
        return lv_amount;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseSpikes_338, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseSpikes_338, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseVampirism_341, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(103LL), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseVampirism_341, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleansePoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_curPoison = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getPoison_1229, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_curPoison, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_int(0LL);
    }
    lv_amount = gd::gd_coerce_int(gd::gd_min(lv_curPoison, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_losePoison_1232, _ca, 3); })();
    return lv_amount;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_selfInflictBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(109LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleanseBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_curBlind = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBlind_1240, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_curBlind, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_int(0LL);
    }
    lv_amount = gd::gd_coerce_int(gd::gd_min(lv_curBlind, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseBlind_1243, _ca, 3); })();
    return lv_amount;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseRegeneration_1236, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(102LL), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_tryUseLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), lv_amount)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 2); })();
        return gd::GdVal::from_bool(true);
    }
    else {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseLucky_348, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseLucky_348, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(101LL), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_int(110LL), lv_amount, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleanseCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_curCold = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCold_1254, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_curCold, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_int(0LL);
    }
    lv_amount = gd::gd_coerce_int(gd::gd_min(lv_curCold, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseCold_1257, _ca, 3); })();
    return lv_amount;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseHeat_353, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(107LL), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseEmpower_355, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleanseRandomDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numDebuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_cleansedDebuffs = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0), lv_numDebuffs, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_358, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t99 = gd::gd_iter_seq(gd_ctx.arena, lv_cleansedDebuffs);
        gd::GdArr* _t100 = (_t99.kind == gd::GdVal::Kind::Arr) ? _t99.arr : nullptr;
        uint32_t _len__t101 = _t100 ? _t100->len : 0u;
        for (uint32_t _t101 = 0; _t101 < _len__t101; ++_t101) {
            gd::GdVal lv_debuff = _t100->data[_t101];
            (void)([&]() { gd::GdVal _ca[] = {lv_debuff, gd::native_array_index(gd_ctx, lv_cleansedDebuffs, lv_debuff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 4); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictRandomDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numDebuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_availableDebuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableDebuffs, gd::GdVal::null())))) {
        lv_availableDebuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0);
    }
    gd::GdVal lv_pickedDebuffs = ([&]() { gd::GdVal _ca[] = {lv_availableDebuffs, lv_numDebuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacksToGive_359, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t102 = gd::gd_iter_seq(gd_ctx.arena, lv_pickedDebuffs);
        gd::GdArr* _t103 = (_t102.kind == gd::GdVal::Kind::Arr) ? _t102.arr : nullptr;
        uint32_t _len__t104 = _t103 ? _t103->len : 0u;
        for (uint32_t _t104 = 0; _t104 < _len__t104; ++_t104) {
            gd::GdVal lv_debuff = _t103->data[_t104];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_debuff, gd::native_array_index(gd_ctx, lv_pickedDebuffs, lv_debuff), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_pickRandomStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackTypes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_numStacks = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_target = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_priorityStack = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_stacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t105 = gd::gd_iter_seq(gd_ctx.arena, lv_stackTypes);
        gd::GdArr* _t106 = (_t105.kind == gd::GdVal::Kind::Arr) ? _t105.arr : nullptr;
        uint32_t _len__t107 = _t106 ? _t106->len : 0u;
        for (uint32_t _t107 = 0; _t107 < _len__t107; ++_t107) {
            gd::GdVal lv_stackType = _t106->data[_t107];
            gd::GdVal lv_numTargetStacks = ([&]() { gd::GdVal _ca[] = {lv_stackType}; return gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_getStacks_1023, _ca, 1); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numTargetStacks, gd::GdVal::from_int(0LL))))) {
                { gd::GdVal _t108 = lv_stacks; gd::GdVal _t109 = lv_stackType; gd::native_array_set_index(gd_ctx, _t108, _t109, lv_numTargetStacks); }
            }
        }
    }
    gd::GdVal lv_pickedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_priorityStack, gd::GdVal::null())))) {
        gd::GdVal lv_pickedPriorityStacks = gd::gd_min(lv_numStacks, ([&]() { gd::GdVal _ca[] = {lv_priorityStack, gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, lv_stacks, gd::SYM_get, _ca, 2); })());
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_pickedPriorityStacks, gd::GdVal::from_int(0LL))))) {
            { gd::GdVal _t110 = lv_pickedStacks; gd::GdVal _t111 = lv_priorityStack; gd::native_array_set_index(gd_ctx, _t110, _t111, lv_pickedPriorityStacks); }
            lv_numStacks = gd::gd_sub(lv_numStacks, lv_pickedPriorityStacks);
            (void)([&]() { gd::GdVal _ca[] = {lv_stacks, lv_priorityStack, lv_pickedPriorityStacks}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictSub_1790, _ca, 3); })();
        }
    }
    {
        gd::GdVal _t112 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_numStacks}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t113 = (_t112.kind == gd::GdVal::Kind::Arr) ? _t112.arr : nullptr;
        uint32_t _len__t114 = _t113 ? _t113->len : 0u;
        for (uint32_t _t114 = 0; _t114 < _len__t114; ++_t114) {
            gd::GdVal lv_i = _t113->data[_t114];
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_stacks, gd::SYM_empty, nullptr, 0))))) {
                gd::GdVal lv_stackType = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_stacks, gd::SYM_keys, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_pickedStacks, lv_stackType, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1789, _ca, 3); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_stacks, lv_stackType, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictSub_1790, _ca, 3); })();
            }
        }
    }
    return lv_pickedStacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_pickRandomStacksToGive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackTypes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_numStacks = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_pickedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t115 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_numStacks}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t116 = (_t115.kind == gd::GdVal::Kind::Arr) ? _t115.arr : nullptr;
        uint32_t _len__t117 = _t116 ? _t116->len : 0u;
        for (uint32_t _t117 = 0; _t117 < _len__t117; ++_t117) {
            gd::GdVal lv_i = _t116->data[_t117];
            gd::GdVal lv_stackType = ([&]() { gd::GdVal _ca[] = {lv_stackTypes}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_pickedStacks, lv_stackType, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1789, _ca, 3); })();
        }
    }
    return lv_pickedStacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getLeastStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numStacks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_target = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_availableStacks = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_priorStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t118 = gd::gd_iter_seq(gd_ctx.arena, lv_availableStacks);
        gd::GdArr* _t119 = (_t118.kind == gd::GdVal::Kind::Arr) ? _t118.arr : nullptr;
        uint32_t _len__t120 = _t119 ? _t119->len : 0u;
        for (uint32_t _t120 = 0; _t120 < _len__t120; ++_t120) {
            gd::GdVal lv_stackType = _t119->data[_t120];
            { gd::GdVal _t121 = lv_priorStacks; gd::GdVal _t122 = lv_stackType; gd::native_array_set_index(gd_ctx, _t121, _t122, ([&]() { gd::GdVal _ca[] = {lv_stackType}; return gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_getStacks_1023, _ca, 1); })()); }
        }
    }
    gd::GdVal lv_pickedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numStacks, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_leastStacksCount = gd::gd_coerce_int(gd::GdVal::from_int(10000LL));
        gd::GdVal lv_leastStacks = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t123 = gd::gd_iter_seq(gd_ctx.arena, lv_priorStacks);
            gd::GdArr* _t124 = (_t123.kind == gd::GdVal::Kind::Arr) ? _t123.arr : nullptr;
            uint32_t _len__t125 = _t124 ? _t124->len : 0u;
            for (uint32_t _t125 = 0; _t125 < _len__t125; ++_t125) {
                gd::GdVal lv_stackType = _t124->data[_t125];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_array_index(gd_ctx, lv_priorStacks, lv_stackType), lv_leastStacksCount)))) {
                    lv_leastStacksCount = gd::gd_coerce_int(gd::native_array_index(gd_ctx, lv_priorStacks, lv_stackType));
                    (void)gd::native_inline_call(gd_ctx, lv_leastStacks, gd::SYM_clear, nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {lv_stackType}; return gd::native_inline_call(gd_ctx, lv_leastStacks, gd::SYM_push_back, _ca, 1); })();
                }
                else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_priorStacks, lv_stackType), lv_leastStacksCount)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_stackType}; return gd::native_inline_call(gd_ctx, lv_leastStacks, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
        gd::GdVal lv_stackToGive = ([&]() { gd::GdVal _ca[] = {lv_leastStacks}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_pickedStacks, lv_stackToGive, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1789, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_priorStacks, lv_stackToGive, gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1789, _ca, 3); })();
        lv_numStacks = gd::gd_sub(lv_numStacks, gd::GdVal::from_int(1LL));
    }
    return lv_pickedStacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMostStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_availableStacks = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_buffs = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t126 = gd::gd_iter_seq(gd_ctx.arena, lv_availableStacks);
        gd::GdArr* _t127 = (_t126.kind == gd::GdVal::Kind::Arr) ? _t126.arr : nullptr;
        uint32_t _len__t128 = _t127 ? _t127->len : 0u;
        for (uint32_t _t128 = 0; _t128 < _len__t128; ++_t128) {
            gd::GdVal lv_buff = _t127->data[_t128];
            { gd::GdVal _t129 = lv_buffs; gd::GdVal _t130 = lv_buff; gd::native_array_set_index(gd_ctx, _t129, _t130, ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_getStacks_1023, _ca, 1); })()); }
        }
    }
    gd::GdVal lv_maxBuffs = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::GdVal lv_maxStacks = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t131 = gd::gd_iter_seq(gd_ctx.arena, lv_buffs);
        gd::GdArr* _t132 = (_t131.kind == gd::GdVal::Kind::Arr) ? _t131.arr : nullptr;
        uint32_t _len__t133 = _t132 ? _t132->len : 0u;
        for (uint32_t _t133 = 0; _t133 < _len__t133; ++_t133) {
            gd::GdVal lv_buff = _t132->data[_t133];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_buffs, lv_buff), lv_maxStacks)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::native_inline_call(gd_ctx, lv_maxBuffs, gd::SYM_push_back, _ca, 1); })();
            }
            else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_array_index(gd_ctx, lv_buffs, lv_buff), lv_maxStacks)))) {
                (void)gd::native_inline_call(gd_ctx, lv_maxBuffs, gd::SYM_clear, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::native_inline_call(gd_ctx, lv_maxBuffs, gd::SYM_push_back, _ca, 1); })();
                lv_maxStacks = gd::native_array_index(gd_ctx, lv_buffs, lv_buff);
            }
        }
    }
    return lv_maxBuffs;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStackFraction(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_fraction = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_fraction = gd::gd_coerce_float(lv_fraction);
    gd::GdVal lv_limit = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_availableStacks = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_sum = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    gd::GdVal lv_stacksUnlimited = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t134 = gd::gd_iter_seq(gd_ctx.arena, lv_availableStacks);
        gd::GdArr* _t135 = (_t134.kind == gd::GdVal::Kind::Arr) ? _t134.arr : nullptr;
        uint32_t _len__t136 = _t135 ? _t135->len : 0u;
        for (uint32_t _t136 = 0; _t136 < _len__t136; ++_t136) {
            gd::GdVal lv_buff = _t135->data[_t136];
            gd::GdVal lv_prior = ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_getStacks_1023, _ca, 1); })();
            gd::GdVal lv_withBonus = gd::gd_mul(lv_prior, lv_fraction);
            { gd::GdVal _t137 = lv_stacksUnlimited; gd::GdVal _t138 = lv_buff; gd::native_array_set_index(gd_ctx, _t137, _t138, lv_withBonus); }
            lv_sum = gd::gd_coerce_float(gd::gd_add(gd_ctx, lv_sum, lv_withBonus));
        }
    }
    gd::GdVal lv_sumRounded = gd::gd_round(lv_sum);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_sumRounded, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_totalToGive = gd::gd_coerce_float(gd::gd_min(lv_limit, lv_sumRounded));
    gd::GdVal lv_limitFactor = gd::gd_div(gd_ctx, lv_totalToGive, lv_sumRounded);
    gd::GdVal lv_buffsToGive = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    gd::GdVal lv_overflow = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    gd::GdVal lv_totalGiven = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t139 = gd::gd_iter_seq(gd_ctx.arena, lv_stacksUnlimited);
        gd::GdArr* _t140 = (_t139.kind == gd::GdVal::Kind::Arr) ? _t139.arr : nullptr;
        uint32_t _len__t141 = _t140 ? _t140->len : 0u;
        for (uint32_t _t141 = 0; _t141 < _len__t141; ++_t141) {
            gd::GdVal lv_buff = _t140->data[_t141];
            gd::GdVal lv_limited = gd::gd_mul(gd::native_array_index(gd_ctx, lv_stacksUnlimited, lv_buff), lv_limitFactor);
            gd::GdVal lv_guaranteed = gd::gd_coerce_int(lv_limited);
            { gd::GdVal _t142 = lv_buffsToGive; gd::GdVal _t143 = lv_buff; gd::native_array_set_index(gd_ctx, _t142, _t143, lv_guaranteed); }
            { gd::GdVal _t144 = lv_overflow; gd::GdVal _t145 = lv_buff; gd::native_array_set_index(gd_ctx, _t144, _t145, gd::gd_sub(lv_limited, lv_guaranteed)); }
            lv_totalGiven = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_totalGiven, lv_guaranteed));
        }
    }
    gd::GdVal lv_overflowBuffs = gd::gd_coerce_int(gd::gd_sub(lv_totalToGive, lv_totalGiven));
    gd::GdVal lv_sortedOverflow = gd::native_inline_call(gd_ctx, lv_overflow, gd::SYM_keys, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_sortedOverflow, gd::GdVal::from_str(&battle_string_literals[59])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_shuffleEngine_1747, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_overflow}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_DictSorter_1808), gd::SYM_new, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[60])}; return gd::native_inline_call(gd_ctx, lv_sortedOverflow, gd::SYM_sort_custom, _ca, 2); })();
    {
        gd::GdVal _t146 = gd::gd_iter_seq(gd_ctx.arena, lv_sortedOverflow);
        gd::GdArr* _t147 = (_t146.kind == gd::GdVal::Kind::Arr) ? _t146.arr : nullptr;
        uint32_t _len__t148 = _t147 ? _t147->len : 0u;
        for (uint32_t _t148 = 0; _t148 < _len__t148; ++_t148) {
            gd::GdVal lv_buff = _t147->data[_t148];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_overflowBuffs, gd::GdVal::from_int(0LL))))) {
                break;
            }
            { gd::GdVal _t149 = lv_buffsToGive; gd::GdVal _t150 = lv_buff; gd::native_array_set_index(gd_ctx, _t149, _t150, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t149, _t150), gd::GdVal::from_int(1LL))); }
            lv_overflowBuffs = gd::gd_coerce_int(gd::gd_sub(lv_overflowBuffs, gd::GdVal::from_int(1LL)));
        }
    }
    return lv_buffsToGive;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_multiplyBuffsLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonus = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_bonus = gd::gd_coerce_float(lv_bonus);
    gd::GdVal lv_limit = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_availableBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    gd::GdVal lv_buffsToGive = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_bonus, lv_limit, lv_availableBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStackFraction_362, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_buffsToGive, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t151 = gd::gd_iter_seq(gd_ctx.arena, lv_buffsToGive);
        gd::GdArr* _t152 = (_t151.kind == gd::GdVal::Kind::Arr) ? _t151.arr : nullptr;
        uint32_t _len__t153 = _t152 ? _t152->len : 0u;
        for (uint32_t _t153 = 0; _t153 < _len__t153; ++_t153) {
            gd::GdVal lv_buff = _t152->data[_t153];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buff, gd::native_array_index(gd_ctx, lv_buffsToGive, lv_buff)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 3); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeBuffsFraction(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fraction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_fraction = gd::gd_coerce_float(lv_fraction);
    gd::GdVal lv_limit = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    gd::GdVal lv_buffsToRemove = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_fraction, lv_limit, lv_availableBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStackFraction_362, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_buffsToRemove, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t154 = gd::gd_iter_seq(gd_ctx.arena, lv_buffsToRemove);
        gd::GdArr* _t155 = (_t154.kind == gd::GdVal::Kind::Arr) ? _t154.arr : nullptr;
        uint32_t _len__t156 = _t155 ? _t155->len : 0u;
        for (uint32_t _t156 = 0; _t156 < _len__t156; ++_t156) {
            gd::GdVal lv_buff = _t155->data[_t156];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::native_array_index(gd_ctx, lv_buffsToRemove, lv_buff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 4); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stealBuffsFraction(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fraction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_fraction = gd::gd_coerce_float(lv_fraction);
    gd::GdVal lv_limit = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    gd::GdVal lv_buffsToSteal = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_fraction, lv_limit, lv_availableBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStackFraction_362, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_buffsToSteal, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t157 = gd::gd_iter_seq(gd_ctx.arena, lv_buffsToSteal);
        gd::GdArr* _t158 = (_t157.kind == gd::GdVal::Kind::Arr) ? _t157.arr : nullptr;
        uint32_t _len__t159 = _t158 ? _t158->len : 0u;
        for (uint32_t _t159 = 0; _t159 < _len__t159; ++_t159) {
            gd::GdVal lv_buff = _t158->data[_t159];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::native_array_index(gd_ctx, lv_buffsToSteal, lv_buff), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealStack_208, _ca, 3); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveLeastBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_target = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_target, gd::GdVal::null())))) {
        lv_target = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    gd::GdVal lv_pickedStacks = ([&]() { gd::GdVal _ca[] = {lv_numBuffs, lv_target, lv_availableBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getLeastStacks_360, _ca, 3); })();
    {
        gd::GdVal _t160 = gd::gd_iter_seq(gd_ctx.arena, lv_pickedStacks);
        gd::GdArr* _t161 = (_t160.kind == gd::GdVal::Kind::Arr) ? _t160.arr : nullptr;
        uint32_t _len__t162 = _t161 ? _t161->len : 0u;
        for (uint32_t _t162 = 0; _t162 < _len__t162; ++_t162) {
            gd::GdVal lv_buffType = _t161->data[_t162];
            (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_buffType, gd::native_array_index(gd_ctx, lv_pickedStacks, lv_buffType), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMostBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    gd::GdVal lv_maxBuffs = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_availableBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_361, _ca, 2); })();
    gd::GdVal lv_buffToGive = ([&]() { gd::GdVal _ca[] = {lv_maxBuffs}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buffToGive, lv_numBuffs, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeMostBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_use = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_use = gd::gd_coerce_bool(lv_use);
    gd::GdVal lv_availableBuffs = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    gd::GdVal lv_target = gd::GdVal::null();
    gd::GdVal lv_buffs = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    if (gd::gd_truth(lv_use)) {
        lv_target = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0);
    }
    else {
        lv_target = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0);
    }
    gd::GdVal lv_maxBuffs = ([&]() { gd::GdVal _ca[] = {lv_target, lv_availableBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_361, _ca, 2); })();
    gd::GdVal lv_buffToRemove = ([&]() { gd::GdVal _ca[] = {lv_maxBuffs}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    gd::GdVal lv_toRemove = gd::gd_min(lv_numBuffs, ([&]() { gd::GdVal _ca[] = {lv_buffToRemove}; return gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_getStacks_1023, _ca, 1); })());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_toRemove, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(lv_use)) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_buffToRemove, lv_toRemove, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 4); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_buffToRemove, lv_toRemove, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 4); })();
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_numBuffs = gd::gd_coerce_int(lv_numBuffs);
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_target = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_target, gd::GdVal::null())))) {
        lv_target = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0);
    }
    gd::GdVal lv_pickedBuffs = ([&]() { gd::GdVal _ca[] = {lv_availableBuffs, lv_numBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacksToGive_359, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t163 = gd::gd_iter_seq(gd_ctx.arena, lv_pickedBuffs);
        gd::GdArr* _t164 = (_t163.kind == gd::GdVal::Kind::Arr) ? _t163.arr : nullptr;
        uint32_t _len__t165 = _t164 ? _t164->len : 0u;
        for (uint32_t _t165 = 0; _t165 < _len__t165; ++_t165) {
            gd::GdVal lv_buff = _t164->data[_t165];
            (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_buff, gd::native_array_index(gd_ctx, lv_pickedBuffs, lv_buff), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveAllBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    {
        gd::GdVal _t166 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t167 = (_t166.kind == gd::GdVal::Kind::Arr) ? _t166.arr : nullptr;
        uint32_t _len__t168 = _t167 ? _t167->len : 0u;
        for (uint32_t _t168 = 0; _t168 < _len__t168; ++_t168) {
            gd::GdVal lv_buff = _t167->data[_t168];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buff, lv_numBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    gd::GdVal lv_pickedBuffs = ([&]() { gd::GdVal _ca[] = {lv_availableBuffs, lv_numBuffs, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_358, _ca, 3); })();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_pickedBuffs, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_events = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t169 = gd::gd_iter_seq(gd_ctx.arena, lv_pickedBuffs);
        gd::GdArr* _t170 = (_t169.kind == gd::GdVal::Kind::Arr) ? _t169.arr : nullptr;
        uint32_t _len__t171 = _t170 ? _t170->len : 0u;
        for (uint32_t _t171 = 0; _t171 < _len__t171; ++_t171) {
            gd::GdVal lv_buff = _t170->data[_t171];
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_buff, gd::native_array_index(gd_ctx, lv_pickedBuffs, lv_buff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_useStacks_1219, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, lv_events, gd::SYM_push_back, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return lv_events;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_removedStacks = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0), lv_numBuffs, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_358, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t172 = gd::gd_iter_seq(gd_ctx.arena, lv_removedStacks);
        gd::GdArr* _t173 = (_t172.kind == gd::GdVal::Kind::Arr) ? _t172.arr : nullptr;
        uint32_t _len__t174 = _t173 ? _t173->len : 0u;
        for (uint32_t _t174 = 0; _t174 < _len__t174; ++_t174) {
            gd::GdVal lv_buff = _t173->data[_t174];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::native_array_index(gd_ctx, lv_removedStacks, lv_buff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 4); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stealRandomBuff(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_possibleBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_priorityBuff = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_possibleBuffs, gd::GdVal::null())))) {
        lv_possibleBuffs = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    }
    gd::GdVal lv_removedStacks = ([&]() { gd::GdVal _ca[] = {lv_possibleBuffs, lv_numBuffs, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_priorityBuff}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_358, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
    {
        gd::GdVal _t175 = gd::gd_iter_seq(gd_ctx.arena, lv_removedStacks);
        gd::GdArr* _t176 = (_t175.kind == gd::GdVal::Kind::Arr) ? _t175.arr : nullptr;
        uint32_t _len__t177 = _t176 ? _t176->len : 0u;
        for (uint32_t _t177 = 0; _t177 < _len__t177; ++_t177) {
            gd::GdVal lv_buff = _t176->data[_t177];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::native_array_index(gd_ctx, lv_removedStacks, lv_buff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseStacks_1032, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buff, gd::native_array_index(gd_ctx, lv_removedStacks, lv_buff), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectToCharacterBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t178 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t179 = (_t178.kind == gd::GdVal::Kind::Arr) ? _t178.arr : nullptr;
        uint32_t _len__t180 = _t179 ? _t179->len : 0u;
        for (uint32_t _t180 = 0; _t180 < _len__t180; ++_t180) {
            gd::GdVal lv_buff = _t179->data[_t180];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_buffs_1048), lv_buff), SYM_GEN_signalName_1013), lv_methodName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectToCharacterDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t181 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t182 = (_t181.kind == gd::GdVal::Kind::Arr) ? _t181.arr : nullptr;
        uint32_t _len__t183 = _t182 ? _t182->len : 0u;
        for (uint32_t _t183 = 0; _t183 < _len__t183; ++_t183) {
            gd::GdVal lv_debuff = _t182->data[_t183];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_buffs_1048), lv_debuff), SYM_GEN_signalName_1013), lv_methodName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectToOpponentDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t184 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0));
        gd::GdArr* _t185 = (_t184.kind == gd::GdVal::Kind::Arr) ? _t184.arr : nullptr;
        uint32_t _len__t186 = _t185 ? _t185->len : 0u;
        for (uint32_t _t186 = 0; _t186 < _len__t186; ++_t186) {
            gd::GdVal lv_debuff = _t185->data[_t186];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_buffs_1048), lv_debuff), SYM_GEN_signalName_1013), lv_methodName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectToOpponentBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t187 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t188 = (_t187.kind == gd::GdVal::Kind::Arr) ? _t187.arr : nullptr;
        uint32_t _len__t189 = _t188 ? _t188->len : 0u;
        for (uint32_t _t189 = 0; _t189 < _len__t189; ++_t189) {
            gd::GdVal lv_buff = _t188->data[_t189];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::native_inline_get_prop(gd_ctx, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_buffs_1048), lv_buff), SYM_GEN_signalName_1013), lv_methodName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNextFreeLabelPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if(gd::native_lazy_diagnostic_required(gd_ctx,0,gd::native_skip_label_diagnostic(gd_ctx,*this))) {
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[61]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::gd_coerce_int(this->f_ownerType), ([&]() { gd::GdVal _ca[] = {(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046))) : gd::GdVal::from_bool(false))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    {
        const gd::GdVal integer_source_t190 = gd::native_inline_call(gd_ctx, this->f_buffLabelPositionTimestamps, gd::SYM_size, nullptr, 0);
        const bool integer_range_t190 = integer_source_t190.kind == gd::GdVal::Kind::Int &&
            integer_source_t190.i <= 4294967295LL;
        gd::GdVal _t190 = integer_range_t190 ? gd::GdVal::null() :
            gd::gd_iter_seq(gd_ctx.arena, integer_source_t190);
        gd::GdArr* _t191 = (_t190.kind == gd::GdVal::Kind::Arr) ? _t190.arr : nullptr;
        uint32_t _len__t192 = integer_range_t190 ?
            (integer_source_t190.i > 0 ? static_cast<uint32_t>(integer_source_t190.i) : 0u) :
            (_t191 ? _t191->len : 0u);
        for (uint32_t _t192 = 0; _t192 < _len__t192; ++_t192) {
            gd::GdVal lv_i = integer_range_t190 ? gd::GdVal::from_int(static_cast<int64_t>(_t192)) : _t191->data[_t192];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), gd::native_array_index(gd_ctx, this->f_buffLabelPositionTimestamps, lv_i))))) {
                { gd::GdVal _t193 = this->f_buffLabelPositionTimestamps; gd::GdVal _t194 = lv_i; gd::native_array_set_index(gd_ctx, _t193, _t194, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), gd::GdVal::from_float(0.5))); }
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
                return gd::GdVal::null();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}

gd::GdVal Gd__gd_core__CoreItem::fn_spawnLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_type, gd::GdVal::from_obj(this), lv_amount}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnLabelOnItem_1643, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_spawnLabel_other(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_type, gd::GdVal::from_obj(this), lv_amount}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnLabelOnItem_1643, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_consume(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_playCombatAni = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_playCombatAni, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 3); })();
    this->f_consumed = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setState(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_withNextEvent = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_newState, lv_withNextEvent, lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemState_1385, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_newState}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onTemporaryStacksTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_empowerEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_gems, gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_gems, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_initSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t195 = gd::gd_iter_seq(gd_ctx.arena, this->f_gems);
        gd::GdArr* _t196 = (_t195.kind == gd::GdVal::Kind::Arr) ? _t195.arr : nullptr;
        uint32_t _len__t197 = _t196 ? _t196->len : 0u;
        for (uint32_t _t197 = 0; _t197 < _len__t197; ++_t197) {
            gd::GdVal lv_gem = _t196->data[_t197];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_gem, gd::GdVal::null())))) {
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGemsOfItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_out = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t198 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t199 = (_t198.kind == gd::GdVal::Kind::Arr) ? _t198.arr : nullptr;
        uint32_t _len__t200 = _t199 ? _t199->len : 0u;
        for (uint32_t _t200 = 0; _t200 < _len__t200; ++_t200) {
            gd::GdVal lv_item = _t199->data[_t200];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getGemsNoNull_497, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_out, gd::SYM_append_array, _ca, 1); })();
        }
    }
    return lv_out;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getPrice_392, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseSellPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getSellPrice_394, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getSellPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getSellPrice_394, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getSalePrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getSalePrice_395, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setGem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_socketId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_socketId = gd::gd_coerce_int(lv_socketId);
    gd::GdVal lv_gem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_socketId, gd::native_inline_call(gd_ctx, this->f_gems, gd::SYM_size, nullptr, 0))))) {
        (void)gd::GdVal::null();
    }
    else {
        gd::set_prop(gd_ctx, lv_gem, SYM_GEN_ownerType_49, gd::GdVal::from_int(7LL));
        { gd::GdVal _t201 = this->f_gems; gd::GdVal _t202 = lv_socketId; gd::native_array_set_index(gd_ctx, _t201, _t202, lv_gem); }
        gd::set_prop(gd_ctx, lv_gem, SYM_GEN_socket_962, gd::GdVal::from_obj(this));
        (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_gem, SYM_GEN_occupiedCells_52), gd::SYM_clear, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_pushGemsToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_pushItemsInsideToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_returnToSocket(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_movebackDur = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getOwnOrPlayerInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        return this->f_inventory;
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), gd::GdVal::null())))) {
        return gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), SYM_GEN_inventory_5);
    }
    return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_emptyGrid_1487, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCellsForGlobalPositions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_points = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return lv_points;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGlobalPointsForCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return lv_cells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGlobalPointsForCells_noRotate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return lv_cells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCollisionCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_collisionCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getExtensionCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_extensionCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCollisionPoints(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_collisionCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getExtensionPoints(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_extensionCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCells_tilemap(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return ([&]() { gd::GdVal _ca[] = {lv_color, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, this->f_affectedTileCells, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsAfterRotate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : (gd::GdVal::from_int(0LL));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(0LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_rotatedCells}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsAfterRotate_primary_410, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_color, gd::GdVal::from_int(1LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_rotatedCells}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsAfterRotate_secondary_411, _ca, 1); })();
    }
    else {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[62]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv__rotatedCells}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
    }
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsAfterRotate_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv__rotatedCells}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })();
    }
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCells_noRotate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return ([&]() { gd::GdVal _ca[] = {this->f_collisionCells, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsAfterRotate_409, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedPoints(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_tilemap_408, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_noRotate_412, _ca, 1); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedPoints_413, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_400, nullptr, 0), SYM_GEN_getCellsForGlobalPositions_401, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsInInventory_cached(const gd::GdVal* args, int argc) {
    auto& ctx = *this->rt_ctx_;
    const auto color = argc > 0 ? args[0] : gd::GdVal::null();
    const auto cache = this->f_affectedCellsCache;
    if (cache.kind == gd::GdVal::Kind::Dict && cache.dict) {
        const auto index = cache.dict->find_index(color);
        if (index >= 0) return cache.dict->entries[index].val;
        return gd::GdVal::from_arr(gd::GdArr::from_init(ctx.arena, {}));
    }
    const gd::GdVal query[] = {color, gd::GdVal::from_arr(gd::GdArr::from_init(ctx.arena, {}))};
    return gd::native_inline_call(ctx, cache, gd::SYM_get, query, 2);
}
gd::GdVal Gd__gd_core__CoreItem::fn_cacheAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t203 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t204 = (_t203.kind == gd::GdVal::Kind::Arr) ? _t203.arr : nullptr;
        uint32_t _len__t205 = _t204 ? _t204->len : 0u;
        for (uint32_t _t205 = 0; _t205 < _len__t205; ++_t205) {
            gd::GdVal lv_color = _t204->data[_t205];
            { gd::GdVal _t206 = this->f_affectedCellsCache; gd::GdVal _t207 = lv_color; gd::native_array_set_index(gd_ctx, _t206, _t207, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_414, _ca, 1); })()); }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleanCachedAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_affectedCellsCache, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t208 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t209 = (_t208.kind == gd::GdVal::Kind::Arr) ? _t208.arr : nullptr;
        uint32_t _len__t210 = _t209 ? _t209->len : 0u;
        for (uint32_t _t210 = 0; _t210 < _len__t210; ++_t210) {
            gd::GdVal lv_color = _t209->data[_t210];
            (void)gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_currentAffectedItems, lv_color), gd::SYM_clear, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanCachedAffectedItems_417, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_cachedAffectedItems, gd::SYM_empty, nullptr, 0))))) {
        return gd::native_array_index(gd_ctx, this->f_cachedAffectedItems, lv_color);
    }
    gd::GdVal lv_items = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t211 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_423, _ca, 1); })());
        gd::GdArr* _t212 = (_t211.kind == gd::GdVal::Kind::Arr) ? _t211.arr : nullptr;
        uint32_t _len__t213 = _t212 ? _t212->len : 0u;
        for (uint32_t _t213 = 0; _t213 < _len__t213; ++_t213) {
            gd::GdVal lv_item = _t212->data[_t213];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_290, _ca, 2); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_items, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_items;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedItems_nocache(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv_items = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t214 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_422, _ca, 1); })());
        gd::GdArr* _t215 = (_t214.kind == gd::GdVal::Kind::Arr) ? _t214.arr : nullptr;
        uint32_t _len__t216 = _t215 ? _t215->len : 0u;
        for (uint32_t _t216 = 0; _t216 < _len__t216; ++_t216) {
            gd::GdVal lv_item = _t215->data[_t216];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_290, _ca, 2); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_items, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_items;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getItemsInAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_414, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_400, nullptr, 0), SYM_GEN_getItemsInCells_1608, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getItemsInAffectedCells_cached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_415, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_400, nullptr, 0), SYM_GEN_getItemsInCells_1608, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_countItemsInAffectedCells_cached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_415, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_400, nullptr, 0), SYM_GEN_countItemsInCells_1609, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isItemAffected(const gd::GdVal* args, int argc) {
    auto& ctx = *this->rt_ctx_;
    const gd::GdVal query[] = {
        argc > 0 ? args[0] : gd::GdVal::null(),
        argc > 1 ? args[1] : gd::GdVal::from_int(0),
    };
    if (gd::gd_truth(gd::native_inline_call(ctx, query[0], SYM_GEN_isBag_83, nullptr, 0))
            || !gd::gd_truth(this->fn_canAffect_color(query, 2))) {
        return gd::GdVal::from_bool(false);
    }
    gd::GdVal tiles;
    const auto cache = this->f_affectedCellsCache;
    if (cache.kind == gd::GdVal::Kind::Dict && cache.dict) {
        const auto index = cache.dict->find_index(query[1]);
        if (index < 0) return gd::GdVal::from_bool(false);
        tiles = cache.dict->entries[index].val;
    } else {
        tiles = this->fn_getAffectedCellsInInventory_cached(query + 1, 1);
    }
    if (tiles.kind == gd::GdVal::Kind::Arr && tiles.arr && tiles.arr->len == 0)
        return gd::GdVal::from_bool(false);
    const auto cells = gd::gd_iter_seq(ctx.arena, gd::native_inline_get_prop(ctx, query[0], SYM_GEN_occupiedCells_52));
    const auto* occupied = cells.kind == gd::GdVal::Kind::Arr ? cells.arr : nullptr;
    for (uint32_t i = 0, count = occupied ? occupied->len : 0; i < count; ++i) {
        if (gd::gd_truth(gd::gd_in(occupied->data[i], tiles))) return gd::GdVal::from_bool(true);
    }
    return gd::GdVal::from_bool(false);
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumEmptyAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_414, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getEmptyCellsInCells_1606, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })(), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getFirstAffectedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv__affectedItems = ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv__affectedItems, gd::SYM_empty, nullptr, 0))))) {
        return gd::native_array_index(gd_ctx, lv__affectedItems, gd::GdVal::from_int(0LL));
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumAffected_type(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t220 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t221 = (_t220.kind == gd::GdVal::Kind::Arr) ? _t220.arr : nullptr;
        uint32_t _len__t222 = _t221 ? _t221->len : 0u;
        for (uint32_t _t222 = 0; _t222 < _len__t222; ++_t222) {
            gd::GdVal lv_item = _t221->data[_t222];
            lv_num = gd::gd_add(gd_ctx, lv_num, ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getTypeMultiplicity_80, _ca, 1); })());
        }
    }
    return lv_num;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumDistinctAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv_distinctAffectedDescriptors = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t223 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t224 = (_t223.kind == gd::GdVal::Kind::Arr) ? _t223.arr : nullptr;
        uint32_t _len__t225 = _t224 ? _t224->len : 0u;
        for (uint32_t _t225 = 0; _t225 < _len__t225; ++_t225) {
            gd::GdVal lv_item = _t224->data[_t225];
            { gd::GdVal _t226 = lv_distinctAffectedDescriptors; gd::GdVal _t227 = gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2); gd::native_array_set_index(gd_ctx, _t226, _t227, gd::GdVal::from_bool(true)); }
        }
    }
    return gd::native_inline_call(gd_ctx, lv_distinctAffectedDescriptors, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    if (gd::gd_truth(gd::gd_in(lv_color, this->f_affectedCellsCache))) {
        return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_affectedCellsCache, lv_color), gd::SYM_size, nullptr, 0);
    }
    else {
        return gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_tilemap_408, _ca, 1); })(), gd::SYM_size, nullptr, 0), gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_noRotate_412, _ca, 1); })(), gd::SYM_size, nullptr, 0));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_activateExtendedAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t228 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedExtensionCells);
        gd::GdArr* _t229 = (_t228.kind == gd::GdVal::Kind::Arr) ? _t228.arr : nullptr;
        uint32_t _len__t230 = _t229 ? _t229->len : 0u;
        for (uint32_t _t230 = 0; _t230 < _len__t230; ++_t230) {
            gd::GdVal lv_cell = _t229->data[_t230];
            (void)([&]() { gd::GdVal _ca[] = {this->f_affectedTileCells, gd::GdVal::from_int(0LL), lv_cell}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAppend_1792, _ca, 3); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedCells_416, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_deactivateExtendedAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t231 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedExtensionCells);
        gd::GdArr* _t232 = (_t231.kind == gd::GdVal::Kind::Arr) ? _t231.arr : nullptr;
        uint32_t _len__t233 = _t232 ? _t232->len : 0u;
        for (uint32_t _t233 = 0; _t233 < _len__t233; ++_t233) {
            gd::GdVal lv_cell = _t232->data[_t233];
            gd::GdVal lv_arr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, this->f_affectedTileCells, gd::SYM_get, _ca, 2); })();
            if (gd::gd_truth(gd::gd_in(lv_cell, lv_arr))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, lv_arr, gd::SYM_erase, _ca, 1); })();
            }
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedCells_416, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffectDraggedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_290, _ca, 2); })())) {
        gd::GdVal lv_affectedCells = ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_415, _ca, 1); })();
        {
            gd::GdVal _t234 = gd::gd_iter_seq(gd_ctx.arena, lv_affectedCells);
            gd::GdArr* _t235 = (_t234.kind == gd::GdVal::Kind::Arr) ? _t234.arr : nullptr;
            uint32_t _len__t236 = _t235 ? _t235->len : 0u;
            for (uint32_t _t236 = 0; _t236 < _len__t236; ++_t236) {
                gd::GdVal lv_cell = _t235->data[_t236];
                if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_dragged_51))) {
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_isHovered_714, _ca, 1); })())) {
                        return gd::GdVal::from_bool(true);
                    }
                }
                else {
                    if (gd::gd_truth(gd::gd_in(lv_cell, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_52)))) {
                        return gd::GdVal::from_bool(true);
                    }
                }
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onItemAdded(const gd::GdVal* args, int argc) {
    auto& ctx = *this->rt_ctx_;
    const auto item = argc > 0 ? args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(ctx, item, SYM_GEN_isBag_83, nullptr, 0)))
        return gd::GdVal::null();
    const auto affected_query = [&](const gd::GdVal* query) {
        if (!gd::gd_truth(this->fn_canAffect_color(query, 2))) return false;
        gd::GdVal tiles;
        const auto cache = this->f_affectedCellsCache;
        if (cache.kind == gd::GdVal::Kind::Dict && cache.dict) {
            const auto index = cache.dict->find_index(query[1]);
            if (index < 0) return false;
            tiles = cache.dict->entries[index].val;
        } else {
            tiles = this->fn_getAffectedCellsInInventory_cached(query + 1, 1);
        }
        if (tiles.kind == gd::GdVal::Kind::Arr && tiles.arr && tiles.arr->len == 0) return false;
        const auto cells = gd::gd_iter_seq(ctx.arena, gd::native_inline_get_prop(ctx, item, SYM_GEN_occupiedCells_52));
        const auto* occupied = cells.kind == gd::GdVal::Kind::Arr ? cells.arr : nullptr;
        for (uint32_t i = 0, count = occupied ? occupied->len : 0; i < count; ++i) {
            if (gd::gd_truth(gd::gd_in(occupied->data[i], tiles))) return true;
        }
        return false;
    };
    constexpr int color_count = 4;
    bool affected[color_count]{};
    // Complete every query before invoking any callback. A callback may change
    // the inventory or affected sets before the next color is committed.
    for (int color = 0; color < color_count; ++color) {
        const gd::GdVal query[] = {item, gd::GdVal::from_int(color)};
        const auto current = gd::native_array_index(ctx, this->f_currentAffectedItems, query[1]);
        if (!gd::gd_truth(gd::gd_in(item, current))) {
            affected[color] = affected_query(query);
        }
    }
    for (int color = 0; color < color_count; ++color) {
        if (!affected[color]) continue;
        const gd::GdVal event[] = {item, gd::GdVal::from_int(color)};
        auto current = gd::native_array_index(ctx, this->f_currentAffectedItems, event[1]);
        gd::native_array_set_index(ctx, current, item, gd::GdVal::from_bool(true));
        gd::native_inline_call(ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemAdded_435, event, 2);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t247 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t248 = (_t247.kind == gd::GdVal::Kind::Arr) ? _t247.arr : nullptr;
        uint32_t _len__t249 = _t248 ? _t248->len : 0u;
        for (uint32_t _t249 = 0; _t249 < _len__t249; ++_t249) {
            gd::GdVal lv_color = _t248->data[_t249];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_currentAffectedItems, lv_color), gd::SYM_erase, _ca, 1); })();
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffectDraggedItem_434, _ca, 2); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_436, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumOccupiedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_collisionCells, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumBagCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_extensionCells, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumOccupiedCells_439, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumBagCells_440, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getSizeInCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_topLeft = gd::GdVal::from_vec2((gd::GdVal::from_int(100LL)).as_float(), (gd::GdVal::from_int(100LL)).as_float());
    gd::GdVal lv_bottomRight = gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(100LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(100LL))).as_float());
    gd::GdVal lv_cells = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCollisionCells_404, nullptr, 0);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_cells, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::from_vec2(0.0, 0.0);
    }
    {
        gd::GdVal _t250 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t251 = (_t250.kind == gd::GdVal::Kind::Arr) ? _t250.arr : nullptr;
        uint32_t _len__t252 = _t251 ? _t251->len : 0u;
        for (uint32_t _t252 = 0; _t252 < _len__t252; ++_t252) {
            gd::GdVal lv_cell = _t251->data[_t252];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_x), gd::native_inline_get_prop(gd_ctx, lv_topLeft, gd::SYM_x))))) {
                gd::set_prop(gd_ctx, lv_topLeft, gd::SYM_x, gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_x));
            }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::native_inline_get_prop(gd_ctx, lv_topLeft, gd::SYM_y))))) {
                gd::set_prop(gd_ctx, lv_topLeft, gd::SYM_y, gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_y));
            }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_x), gd::native_inline_get_prop(gd_ctx, lv_bottomRight, gd::SYM_x))))) {
                gd::set_prop(gd_ctx, lv_bottomRight, gd::SYM_x, gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_x));
            }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::native_inline_get_prop(gd_ctx, lv_bottomRight, gd::SYM_y))))) {
                gd::set_prop(gd_ctx, lv_bottomRight, gd::SYM_y, gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_y));
            }
        }
    }
    return gd::gd_add(gd_ctx, gd::gd_sub(lv_bottomRight, lv_topLeft), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTopLeftCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_topLeft = gd::GdVal::from_vec2((gd::GdVal::from_float(std::numeric_limits<double>::infinity())).as_float(), (gd::GdVal::from_float(std::numeric_limits<double>::infinity())).as_float());
    {
        gd::GdVal _t253 = gd::gd_iter_seq(gd_ctx.arena, this->f_occupiedCells);
        gd::GdArr* _t254 = (_t253.kind == gd::GdVal::Kind::Arr) ? _t253.arr : nullptr;
        uint32_t _len__t255 = _t254 ? _t254->len : 0u;
        for (uint32_t _t255 = 0; _t255 < _len__t255; ++_t255) {
            gd::GdVal lv_cell = _t254->data[_t255];
            gd::set_prop(gd_ctx, lv_topLeft, gd::SYM_x, gd::gd_min(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_x), gd::native_inline_get_prop(gd_ctx, lv_topLeft, gd::SYM_x)));
            gd::set_prop(gd_ctx, lv_topLeft, gd::SYM_y, gd::gd_min(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::native_inline_get_prop(gd_ctx, lv_topLeft, gd::SYM_y)));
        }
    }
    return lv_topLeft;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNormalizedCollisionCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBag_83, nullptr, 0))) {
        lv_cells = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getExtensionCells_405, nullptr, 0), gd::SYM_duplicate, nullptr, 0);
    }
    else {
        lv_cells = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCollisionCells_404, nullptr, 0), gd::SYM_duplicate, nullptr, 0);
    }
    gd::GdVal lv_minimum = gd::GdVal::from_vec2((gd::GdVal::from_int(100LL)).as_float(), (gd::GdVal::from_int(100LL)).as_float());
    {
        gd::GdVal _t256 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t257 = (_t256.kind == gd::GdVal::Kind::Arr) ? _t256.arr : nullptr;
        uint32_t _len__t258 = _t257 ? _t257->len : 0u;
        for (uint32_t _t258 = 0; _t258 < _len__t258; ++_t258) {
            gd::GdVal lv_cell = _t257->data[_t258];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::native_inline_get_prop(gd_ctx, lv_minimum, gd::SYM_y))))) {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::native_inline_get_prop(gd_ctx, lv_minimum, gd::SYM_y))))) {
                    gd::set_prop(gd_ctx, lv_minimum, gd::SYM_x, gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_x));
                }
                else {
                    gd::set_prop(gd_ctx, lv_minimum, gd::SYM_x, gd::gd_min(gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_x), gd::native_inline_get_prop(gd_ctx, lv_minimum, gd::SYM_x)));
                }
                gd::set_prop(gd_ctx, lv_minimum, gd::SYM_y, gd::native_inline_get_prop(gd_ctx, lv_cell, gd::SYM_y));
            }
        }
    }
    {
        gd::GdVal _t259 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_cells, gd::SYM_size, nullptr, 0)}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t260 = (_t259.kind == gd::GdVal::Kind::Arr) ? _t259.arr : nullptr;
        uint32_t _len__t261 = _t260 ? _t260->len : 0u;
        for (uint32_t _t261 = 0; _t261 < _len__t261; ++_t261) {
            gd::GdVal lv_i = _t260->data[_t261];
            { gd::GdVal _t262 = lv_cells; gd::GdVal _t263 = lv_i; gd::native_array_set_index(gd_ctx, _t262, _t263, gd::gd_sub(gd::native_array_index(gd_ctx, lv_cells, lv_i), lv_minimum)); }
        }
    }
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_cells, gd::GdVal::from_vec2(0.0, 0.0)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canCombine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_placed;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_prepareReplacement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_replacementPending = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_finishReplacement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_replacementPending = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_placeGeneratedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_candidateCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_moveTo(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fromPos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_newPos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 2) ? _args[2] : (gd::GdVal::from_float(0.2));
    gd::GdVal lv_transitionType = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_resetZ(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_resetZ_450, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onGateItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_insertCounter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_queue_free(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_shift(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_direction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onSold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reactToItemTypeChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[64]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1389, _ca, 1); })();
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onItemTypeChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_canAddAgain = ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reactToItemTypeChange_457, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_canAddAgain)))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_addedToAffected = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t264 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t265 = (_t264.kind == gd::GdVal::Kind::Arr) ? _t264.arr : nullptr;
        uint32_t _len__t266 = _t265 ? _t265->len : 0u;
        for (uint32_t _t266 = 0; _t266 < _len__t266; ++_t266) {
            gd::GdVal lv_color = _t265->data[_t266];
            { gd::GdVal _t267 = lv_addedToAffected; gd::GdVal _t268 = lv_color; gd::native_array_set_index(gd_ctx, _t267, _t268, gd::GdVal::from_bool(false)); }
            if (gd::gd_truth(gd::gd_in(lv_item, gd::native_array_index(gd_ctx, this->f_currentAffectedItems, lv_color)))) {
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_290, _ca, 2); })())))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, this->f_currentAffectedItems, lv_color), gd::SYM_erase, _ca, 1); })();
                    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_436, _ca, 2); })();
                }
            }
            else if (gd::gd_truth(gd::gd_in(lv_item, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })()))) {
                { gd::GdVal _t269 = gd::native_array_index(gd_ctx, this->f_currentAffectedItems, lv_color); gd::GdVal _t270 = lv_item; gd::native_array_set_index(gd_ctx, _t269, _t270, gd::GdVal::from_bool(true)); }
                (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemAdded_435, _ca, 2); })();
                { gd::GdVal _t271 = lv_addedToAffected; gd::GdVal _t272 = lv_color; gd::native_array_set_index(gd_ctx, _t271, _t272, gd::GdVal::from_bool(true)); }
            }
        }
    }
    if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_placedByPlayer_50))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_addedToAffected}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playAffectedPlacedAnimation_663, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gatedItems_1691);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_countAllPlacedOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_count = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_251, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_75), gd::GdVal::null())))) {
            return gd::GdVal::from_int(0LL);
        }
        {
            gd::GdVal _t273 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_75), SYM_GEN_inventory_5), SYM_GEN_getItemsAndGems_1604, nullptr, 0));
            gd::GdArr* _t274 = (_t273.kind == gd::GdVal::Kind::Arr) ? _t273.arr : nullptr;
            uint32_t _len__t275 = _t274 ? _t274->len : 0u;
            for (uint32_t _t275 = 0; _t275 < _len__t275; ++_t275) {
                gd::GdVal lv_item = _t274->data[_t275];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), lv_descr)))) : gd::GdVal::from_bool(false)))) {
                    lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
                }
            }
        }
        return lv_count;
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), gd::GdVal::null())))) {
        {
            gd::GdVal _t276 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), SYM_GEN_inventory_5), SYM_GEN_getItemsAndGems_1604, nullptr, 0));
            gd::GdArr* _t277 = (_t276.kind == gd::GdVal::Kind::Arr) ? _t276.arr : nullptr;
            uint32_t _len__t278 = _t277 ? _t277->len : 0u;
            for (uint32_t _t278 = 0; _t278 < _len__t278; ++_t278) {
                gd::GdVal lv_item = _t277->data[_t278];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), lv_descr))))))) {
                    continue;
                }
                if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_49), gd::GdVal::from_int(7LL))))) {
                    lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
                }
                else if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_placed_6)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_49), gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false)))) {
                    lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
                }
            }
        }
    }
    return lv_count;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTouchedBagsCounted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBag_83, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed))))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_touchedBags = ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getBagsInCells_1610, _ca, 1); })();
    gd::GdVal lv_bagCounter = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t279 = gd::gd_iter_seq(gd_ctx.arena, lv_touchedBags);
        gd::GdArr* _t280 = (_t279.kind == gd::GdVal::Kind::Arr) ? _t279.arr : nullptr;
        uint32_t _len__t281 = _t280 ? _t280->len : 0u;
        for (uint32_t _t281 = 0; _t281 < _len__t281; ++_t281) {
            gd::GdVal lv_bag = _t280->data[_t281];
            gd::GdVal lv_found = gd::GdVal::from_bool(false);
            {
                gd::GdVal _t282 = gd::gd_iter_seq(gd_ctx.arena, lv_bagCounter);
                gd::GdArr* _t283 = (_t282.kind == gd::GdVal::Kind::Arr) ? _t282.arr : nullptr;
                uint32_t _len__t284 = _t283 ? _t283->len : 0u;
                for (uint32_t _t284 = 0; _t284 < _len__t284; ++_t284) {
                    gd::GdVal lv_countedBag = _t283->data[_t284];
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_countedBag, SYM_GEN_descriptor_2), gd::native_inline_get_prop(gd_ctx, lv_bag, SYM_GEN_descriptor_2))))) {
                        { gd::GdVal _t285 = lv_bagCounter; gd::GdVal _t286 = lv_countedBag; gd::native_array_set_index(gd_ctx, _t285, _t286, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t285, _t286), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_bag, SYM_GEN_getBagMultiplicity_932, _ca, 1); })())); }
                        lv_found = gd::GdVal::from_bool(true);
                        break;
                    }
                }
            }
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_found)))) {
                { gd::GdVal _t287 = lv_bagCounter; gd::GdVal _t288 = lv_bag; gd::native_array_set_index(gd_ctx, _t287, _t288, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_bag, SYM_GEN_getBagMultiplicity_932, _ca, 1); })()); }
            }
        }
    }
    return lv_bagCounter;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getHeightRange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2((gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_443, nullptr, 0), gd::SYM_y)).as_float(), (gd::gd_sub(gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_443, nullptr, 0), gd::SYM_y), gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSizeInCells_442, nullptr, 0), gd::SYM_y)), gd::GdVal::from_int(1LL))).as_float());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_ready_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_503, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[65])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_504, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotationFromFaceDirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_mul(gd::gd_mul(lv__faceDirection, gd::GdVal::from_float(3.14159265358979323846)), gd::GdVal::from_float(0.5));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getFaceDirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, gd::gd_coerce_int(gd::gd_add(gd_ctx, gd::gd_div(gd_ctx, gd::gd_mul(gd::GdVal::from_int(2LL), this->f_rotation), gd::GdVal::from_float(3.14159265358979323846)), gd::gd_mul(gd::GdVal::from_float(2.25), gd::GdVal::from_float(3.14159265358979323846)))), gd::GdVal::from_int(5LL)), gd::GdVal::from_int(4LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGlobalFaceDirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFaceDirection_465, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setFaceDirectionInstant(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_faceDirection = gd::gd_coerce_int(lv__faceDirection);
    this->f_rotation = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rotationFromFaceDirection_464, _ca, 1); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setRotation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_rotation = gd::gd_coerce_float(lv__rotation);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeAllItemsCritRate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t289 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t290 = (_t289.kind == gd::GdVal::Kind::Arr) ? _t289.arr : nullptr;
        uint32_t _len__t291 = _t290 ? _t290->len : 0u;
        for (uint32_t _t291 = 0; _t291 < _len__t291; ++_t291) {
            gd::GdVal lv_item = _t290->data[_t291];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_miniActivate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), (gd::gd_truth(this->f_consumed) ? (gd::GdVal::from_str(&battle_string_literals[66])) : (gd::GdVal::from_str(&battle_string_literals[67]))), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playActivationAnimation_778, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_previewCellCollision(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_previewCellCollision_471, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_previewCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_previewCells_472, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_previewCanAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_previewCanAffect_473, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateRight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_faceDirection = gd::gd_coerce_int(gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, this->f_faceDirection, gd::GdVal::from_int(1LL)), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_size, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_467, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onItemRotated_1630, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_faceDirection = gd::gd_coerce_int(gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, gd::gd_sub(this->f_faceDirection, gd::GdVal::from_int(1LL)), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_size, nullptr, 0)), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_size, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_467, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onItemRotated_1630, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateTo(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetRotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.15));
    this->f_faceDirection = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGlobalFaceDirection_466, nullptr, 0));
    this->f_rotation = gd::gd_coerce_float(lv_targetRotation);
    this->f_faceDirection = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGlobalFaceDirection_466, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onItemRotated_1630, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateToDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetRotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.15));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[68]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_targetRotation, lv_duration}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setFaceDirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_mul(lv__faceDirection, gd::GdVal::from_float(3.14159265358979323846)), gd::GdVal::from_float(0.5))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rotateTo_476, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_correctInsideItemFacedirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_number = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_str(&battle_string_literals[0]);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGemData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setGemData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gemData = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reconstructCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_encodedCd = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_timeSinceEntry = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_findBondsWithAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateProgress(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_progress = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    {
        gd::GdVal _t292 = this->f_faceDirection;
        if (gd::native_scalar_eq(_t292, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            lv_progress = gd::gd_coerce_float(gd::gd_sub(gd::GdVal::from_float(1.0), lv_progress));
        }
        else if (gd::native_scalar_eq(_t292, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            lv_progress = gd::gd_coerce_float(gd::gd_sub(gd::GdVal::from_float(1.0), lv_progress));
        }
        else if (gd::native_scalar_eq(_t292, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            lv_progress = gd::gd_coerce_float(gd::gd_neg(lv_progress));
        }
        else if (gd::native_scalar_eq(_t292, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            lv_progress = gd::gd_coerce_float(gd::gd_neg(lv_progress));
        }
    }
    return lv_progress;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cacheCollisionCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBaseItemForShopItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_activateFromEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[69]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_playActivationAnimation_778, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNeighborItemsAndGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_neighbors = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getAdjacentItems_1613, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_neighbors, gd::SYM_append_array, _ca, 1); })();
    {
        gd::GdVal _t293 = gd::gd_iter_seq(gd_ctx.arena, lv_neighbors);
        gd::GdArr* _t294 = (_t293.kind == gd::GdVal::Kind::Arr) ? _t293.arr : nullptr;
        uint32_t _len__t295 = _t294 ? _t294->len : 0u;
        for (uint32_t _t295 = 0; _t295 < _len__t295; ++_t295) {
            gd::GdVal lv_neighbor = _t294->data[_t295];
            gd::GdVal lv_neighborGems = gd::native_inline_call(gd_ctx, lv_neighbor, SYM_GEN_getGemsNoNull_497, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_neighborGems}; return gd::native_inline_call(gd_ctx, lv_neighbors, gd::SYM_append_array, _ca, 1); })();
        }
    }
    return lv_neighbors;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTouchedBags(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBag_83, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed))))))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getBagsInCells_1610, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBusyNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_busyNeighbors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t296 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNeighborItemsAndGems_489, nullptr, 0));
        gd::GdArr* _t297 = (_t296.kind == gd::GdVal::Kind::Arr) ? _t296.arr : nullptr;
        uint32_t _len__t298 = _t297 ? _t297->len : 0u;
        for (uint32_t _t298 = 0; _t298 < _len__t298; ++_t298) {
            gd::GdVal lv_neighbor = _t297->data[_t298];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_neighbor, SYM_GEN_isBusy_259, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::native_inline_call(gd_ctx, lv_busyNeighbors, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    {
        gd::GdVal _t299 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTouchedBags_490, nullptr, 0));
        gd::GdArr* _t300 = (_t299.kind == gd::GdVal::Kind::Arr) ? _t299.arr : nullptr;
        uint32_t _len__t301 = _t300 ? _t300->len : 0u;
        for (uint32_t _t301 = 0; _t301 < _len__t301; ++_t301) {
            gd::GdVal lv_bag = _t300->data[_t301];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_bag, SYM_GEN_isBusy_259, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_bag}; return gd::native_inline_call(gd_ctx, lv_busyNeighbors, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_busyNeighbors;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCraftableNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craftableNeighbors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t302 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNeighborItemsAndGems_489, nullptr, 0));
        gd::GdArr* _t303 = (_t302.kind == gd::GdVal::Kind::Arr) ? _t302.arr : nullptr;
        uint32_t _len__t304 = _t303 ? _t303->len : 0u;
        for (uint32_t _t304 = 0; _t304 < _len__t304; ++_t304) {
            gd::GdVal lv_neighbor = _t303->data[_t304];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_neighbor, SYM_GEN_isAvailableForCrafting_493, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::native_inline_call(gd_ctx, lv_craftableNeighbors, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    {
        gd::GdVal _t305 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTouchedBags_490, nullptr, 0));
        gd::GdArr* _t306 = (_t305.kind == gd::GdVal::Kind::Arr) ? _t305.arr : nullptr;
        uint32_t _len__t307 = _t306 ? _t306->len : 0u;
        for (uint32_t _t307 = 0; _t307 < _len__t307; ++_t307) {
            gd::GdVal lv_bag = _t306->data[_t307];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_bag, SYM_GEN_isAvailableForCrafting_493, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_bag}; return gd::native_inline_call(gd_ctx, lv_craftableNeighbors, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_craftableNeighbors;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isAvailableForCrafting(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedGoldValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t308 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_nocache_421, nullptr, 0));
        gd::GdArr* _t309 = (_t308.kind == gd::GdVal::Kind::Arr) ? _t308.arr : nullptr;
        uint32_t _len__t310 = _t309 ? _t309->len : 0u;
        for (uint32_t _t310 = 0; _t310 < _len__t310; ++_t310) {
            gd::GdVal lv_item = _t309->data[_t310];
            lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getPrice_392, nullptr, 0));
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_countTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ofItems = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_typesDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t311 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855));
        gd::GdArr* _t312 = (_t311.kind == gd::GdVal::Kind::Arr) ? _t311.arr : nullptr;
        uint32_t _len__t313 = _t312 ? _t312->len : 0u;
        for (uint32_t _t313 = 0; _t313 < _len__t313; ++_t313) {
            gd::GdVal lv_type = _t312->data[_t313];
            { gd::GdVal _t314 = lv_typesDict; gd::GdVal _t315 = gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), lv_type); gd::native_array_set_index(gd_ctx, _t314, _t315, gd::GdVal::from_int(0LL)); }
        }
    }
    {
        gd::GdVal _t316 = gd::gd_iter_seq(gd_ctx.arena, lv_ofItems);
        gd::GdArr* _t317 = (_t316.kind == gd::GdVal::Kind::Arr) ? _t316.arr : nullptr;
        uint32_t _len__t318 = _t317 ? _t317->len : 0u;
        for (uint32_t _t318 = 0; _t318 < _len__t318; ++_t318) {
            gd::GdVal lv_item = _t317->data[_t318];
            {
                gd::GdVal _t319 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getTypes_240, nullptr, 0));
                gd::GdArr* _t320 = (_t319.kind == gd::GdVal::Kind::Arr) ? _t319.arr : nullptr;
                uint32_t _len__t321 = _t320 ? _t320->len : 0u;
                for (uint32_t _t321 = 0; _t321 < _len__t321; ++_t321) {
                    gd::GdVal lv_type = _t320->data[_t321];
                    { gd::GdVal _t322 = lv_typesDict; gd::GdVal _t323 = lv_type; gd::native_array_set_index(gd_ctx, _t322, _t323, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t322, _t323), gd::GdVal::from_int(1LL))); }
                }
            }
        }
    }
    return lv_typesDict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasSameOrientationAsPickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGemsNoNull(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_out = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t324 = gd::gd_iter_seq(gd_ctx.arena, this->f_gems);
        gd::GdArr* _t325 = (_t324.kind == gd::GdVal::Kind::Arr) ? _t324.arr : nullptr;
        uint32_t _len__t326 = _t325 ? _t325->len : 0u;
        for (uint32_t _t326 = 0; _t326 < _len__t326; ++_t326) {
            gd::GdVal lv_gem = _t325->data[_t326];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_gem, gd::GdVal::null())))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_gem}; return gd::native_inline_call(gd_ctx, lv_out, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_out;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_gems;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_buildDamageSource(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_damageSource = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_damageSource, SYM_GEN__rng_1548, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv__type}; return gd::native_inline_call(gd_ctx, this->f_damageSource, SYM_GEN_setItem_1550, _ca, 2); })();
    return this->f_damageSource;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectForCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, gd::GdVal::from_obj(this), lv_methodName}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_connectEvent_1595, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectForCombat_signal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    gd::GdVal lv_newConnection = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, gd::GdVal::from_obj(this), lv_methodName, lv_binds}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection), gd::SYM_new, _ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_newConnection}; return gd::native_inline_call(gd_ctx, this->f_combatConnections, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_disconnectCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t327 = gd::gd_iter_seq(gd_ctx.arena, this->f_combatConnections);
        gd::GdArr* _t328 = (_t327.kind == gd::GdVal::Kind::Arr) ? _t327.arr : nullptr;
        uint32_t _len__t329 = _t328 ? _t328->len : 0u;
        for (uint32_t _t329 = 0; _t329 < _len__t329; ++_t329) {
            gd::GdVal lv_connection = _t328->data[_t329];
            (void)gd::native_inline_call(gd_ctx, lv_connection, SYM_GEN_destroy_1657, nullptr, 0);
        }
    }
    (void)gd::native_inline_call(gd_ctx, this->f_combatConnections, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__hasBehaviorMethod(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if(gd_ctx.native_resolved_dispatch && this->f__behavior.kind==gd::GdVal::Kind::Null){
        gd::GdVal result;
        if(gd::native_try_behavior_chain(gd_ctx,this,lv_methodName,gd::GdVal::null(),true,result))return result;
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f__behavior, gd::GdVal::null())))) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_methodName}; return gd::native_inline_call(gd_ctx, this->f__behavior, SYM_GEN_hasBehavior_2688, _ca, 2); })();
    }
    return (gd::gd_truth(gd::gd_in(lv_methodName, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_SELF_BEHAVIOR_METHODS_61))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_methodName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__behavior_call(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_args = (_argc > 1) ? _args[1] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    if(gd_ctx.native_resolved_dispatch && this->f__behavior.kind==gd::GdVal::Kind::Null){
        gd::GdVal result;
        if(gd::native_try_behavior_chain(gd_ctx,this,lv_methodName,lv_args,false,result))return result;
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f__behavior, gd::GdVal::null())))) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_methodName, lv_args}; return gd::native_inline_call(gd_ctx, this->f__behavior, SYM_GEN_callBehavior_2689, _ca, 3); })();
    }
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_methodName, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_SELF_BEHAVIOR_METHODS_61))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_methodName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        return ([&]() { gd::GdVal _ca[] = {lv_methodName, lv_args}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_callv, _ca, 2); })();
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf__f32eng(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    (void)gd_ctx;
    const auto value = gd::gd_coerce_float(_argc > 0 ? _args[0] : gd::GdVal::null());
    return gd::GdVal::from_float(static_cast<double>(static_cast<float>(value.as_float())));
}
gd::GdVal Gd__gd_core__CoreItem::fn__tickChargePath(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_delta = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    gd::set_prop(gd_ctx, lv_charge, SYM_GEN_elapsed_1651, ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_elapsed_1651), lv_delta)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })());
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_nextCell_1652), gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_inventoryCells_1649), gd::SYM_size, nullptr, 0))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_elapsed_1651), gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_callbackDelays_1650), gd::gd_sub(gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_nextCell_1652), gd::GdVal::from_int(2LL))))))) {
            return gd::GdVal::null();
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_charge, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_nextCell_1652), gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_inventoryCells_1649)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__chargeEnterCell_323, _ca, 3); })();
        gd::set_prop(gd_ctx, lv_charge, SYM_GEN_nextCell_1652, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_charge, SYM_GEN_nextCell_1652), gd::GdVal::from_int(1LL)));
    }
    gd::set_prop(gd_ctx, lv_charge, SYM_GEN_active_1653, gd::GdVal::from_bool(false));
    gd::set_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1647, gd::GdVal::null());
    gd::set_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1648, gd::GdVal::null());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreItem(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreItem>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,37u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreItem = {CLS_Gd__gd_core__CoreItem, "CoreItem", "res://gd_core/CoreItem.gd", nullptr, false, _alloc_Gd__gd_core__CoreItem, &Gd__gd_core__CoreItem::get_static_prop_fn, &Gd__gd_core__CoreItem::call_static_fn};

void Gd__gd_core__BloodGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Goobert::init_fields(gd_ctx);
    this->f_dam = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__BloodGoobert::meta() const { return &META_Gd__gd_core__BloodGoobert; }
gd::GdVal Gd__gd_core__BloodGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__BloodGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__BloodGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__BloodGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BloodGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__BloodGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BloodGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BloodGoobert::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BloodGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getVampirism_1226, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BloodGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BloodGoobert(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__BloodGoobert>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,8u); return object; }
const gd::GdClassMeta META_Gd__gd_core__BloodGoobert = {CLS_Gd__gd_core__BloodGoobert, "BloodGoobert", "res://gd_core/BloodGoobert.gd", &META_Gd__gd_core__Goobert, false, _alloc_Gd__gd_core__BloodGoobert, &Gd__gd_core__BloodGoobert::get_static_prop_fn, &Gd__gd_core__BloodGoobert::call_static_fn};

void Gd__gd_core__CoreBuff::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_type = gd::GdVal::from_int(0);
    this->f_isBuff = gd::GdVal::from_bool(false);
    this->f_character = gd::GdVal::null();
    this->f_current = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_permanentStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_resistChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_resistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_reflectChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_signalName = gd::GdVal::from_cstr(gd_ctx.arena, "");
    this->f_temporaryStacks = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_nextTemporaryTimeout = gd::GdVal::from_int(0);
    this->f_MAX_STACKS = gd::GdVal::from_int(0);
    this->f__timer_left = gd::gd_neg(gd::GdVal::from_float(1.0));
    this->f__timer_active = gd::GdVal::from_bool(false);
    this->f__timer_wait = gd::GdVal::from_float(1.0);
    this->f__timer_first_pass = gd::GdVal::from_int(0LL);
    this->f__timer_member_epoch = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_ctx = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreBuff::meta() const { return &META_Gd__gd_core__CoreBuff; }
gd::GdVal Gd__gd_core__CoreBuff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_TemporaryStacks_1040: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreBuff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_TemporaryStacks_1040: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreBuff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_type_1005: out = this->f_type; return true;
        case SYM_GEN_isBuff_1006: out = this->f_isBuff; return true;
        case SYM_GEN_character_74: out = this->f_character; return true;
        case SYM_GEN_current_1007: out = this->f_current; return true;
        case SYM_GEN_permanentStacks_1008: out = this->f_permanentStacks; return true;
        case SYM_GEN_resistChancePercent_1009: out = this->f_resistChancePercent; return true;
        case SYM_GEN_resistStacks_1010: out = this->f_resistStacks; return true;
        case SYM_GEN_reflectChancePercent_1011: out = this->f_reflectChancePercent; return true;
        case SYM_GEN_cleanseProtectionChancePercent_1012: out = this->f_cleanseProtectionChancePercent; return true;
        case SYM_GEN_signalName_1013: out = this->f_signalName; return true;
        case SYM_GEN_temporaryStacks_1014: out = this->f_temporaryStacks; return true;
        case SYM_GEN_nextTemporaryTimeout_1015: out = this->f_nextTemporaryTimeout; return true;
        case SYM_GEN_MAX_STACKS_1016: out = this->f_MAX_STACKS; return true;
        case SYM_GEN__timer_left_1017: out = this->f__timer_left; return true;
        case SYM_GEN__timer_active_1018: out = this->f__timer_active; return true;
        case SYM_GEN__timer_wait_1019: out = this->f__timer_wait; return true;
        case SYM_GEN__timer_first_pass_1020: out = this->f__timer_first_pass; return true;
        case SYM_GEN__timer_member_epoch_1021: out = this->f__timer_member_epoch; return true;
        case SYM_GEN_ctx_3: out = this->f_ctx; return true;
        case SYM_GEN_TemporaryStacks_1040: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_type_1005: this->f_type = gd::gd_coerce_int(val); return true;
        case SYM_GEN_isBuff_1006: this->f_isBuff = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_character_74: this->f_character = val; return true;
        case SYM_GEN_current_1007: this->f_current = gd::gd_coerce_int(val); return true;
        case SYM_GEN_permanentStacks_1008: this->f_permanentStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_resistChancePercent_1009: this->f_resistChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_resistStacks_1010: this->f_resistStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_reflectChancePercent_1011: this->f_reflectChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_cleanseProtectionChancePercent_1012: this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_signalName_1013: this->f_signalName = val; return true;
        case SYM_GEN_temporaryStacks_1014: this->f_temporaryStacks = val; return true;
        case SYM_GEN_nextTemporaryTimeout_1015: this->f_nextTemporaryTimeout = gd::gd_coerce_int(val); return true;
        case SYM_GEN_MAX_STACKS_1016: this->f_MAX_STACKS = gd::gd_coerce_int(val); return true;
        case SYM_GEN__timer_left_1017: this->f__timer_left = val; return true;
        case SYM_GEN__timer_active_1018: this->f__timer_active = val; return true;
        case SYM_GEN__timer_wait_1019: this->f__timer_wait = val; return true;
        case SYM_GEN__timer_first_pass_1020: this->f__timer_first_pass = val; return true;
        case SYM_GEN__timer_member_epoch_1021: this->f__timer_member_epoch = val; return true;
        case SYM_GEN_ctx_3: this->f_ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_init_1022: return true;
        case SYM_GEN_getStacks_1023: return true;
        case SYM_GEN_setStacks_1024: return true;
        case SYM_GEN_reset_1025: return true;
        case SYM_GEN_changeResistChance_1026: return true;
        case SYM_GEN_changeResistStacks_1027: return true;
        case SYM_GEN_changeCleanseProtectionChance_1028: return true;
        case SYM_GEN_changeReflectChance_1029: return true;
        case SYM_GEN_gainStacks_1030: return true;
        case SYM_GEN_gainTemporary_1031: return true;
        case SYM_GEN_loseStacks_1032: return true;
        case SYM_GEN_changeCurrentLogShowLabel_1033: return true;
        case SYM_GEN__blnd_snap_1034: return true;
        case SYM_GEN_onTimeout_1035: return true;
        case SYM_GEN_combatEnd_131: return true;
        case SYM_GEN__startTimer_1036: return true;
        case SYM_GEN__stopTimer_1037: return true;
        case SYM_GEN_isTimerActive_1038: return true;
        case SYM_GEN__tick_1039: return true;
        case SYM_GEN_rebuildTimerSeen_139: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_init_1022: out = fn_init(args, argc); return true;
        case SYM_GEN_getStacks_1023: out = fn_getStacks(args, argc); return true;
        case SYM_GEN_setStacks_1024: out = fn_setStacks(args, argc); return true;
        case SYM_GEN_reset_1025: out = fn_reset(args, argc); return true;
        case SYM_GEN_changeResistChance_1026: out = fn_changeResistChance(args, argc); return true;
        case SYM_GEN_changeResistStacks_1027: out = fn_changeResistStacks(args, argc); return true;
        case SYM_GEN_changeCleanseProtectionChance_1028: out = fn_changeCleanseProtectionChance(args, argc); return true;
        case SYM_GEN_changeReflectChance_1029: out = fn_changeReflectChance(args, argc); return true;
        case SYM_GEN_gainStacks_1030: out = fn_gainStacks(args, argc); return true;
        case SYM_GEN_gainTemporary_1031: out = fn_gainTemporary(args, argc); return true;
        case SYM_GEN_loseStacks_1032: out = fn_loseStacks(args, argc); return true;
        case SYM_GEN_changeCurrentLogShowLabel_1033: out = fn_changeCurrentLogShowLabel(args, argc); return true;
        case SYM_GEN__blnd_snap_1034: out = fn__blnd_snap(args, argc); return true;
        case SYM_GEN_onTimeout_1035: out = fn_onTimeout(args, argc); return true;
        case SYM_GEN_combatEnd_131: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN__startTimer_1036: out = fn__startTimer(args, argc); return true;
        case SYM_GEN__f32eng_505: out = sf__f32eng(gd_ctx, args, argc); return true;
        case SYM_GEN__stopTimer_1037: out = fn__stopTimer(args, argc); return true;
        case SYM_GEN_isTimerActive_1038: out = fn_isTimerActive(args, argc); return true;
        case SYM_GEN__tick_1039: out = fn__tick(args, argc); return true;
        case SYM_GEN_rebuildTimerSeen_139: out = fn_rebuildTimerSeen(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__f32eng_505: out = sf__f32eng(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreBuff::fn_init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__character = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__signalName = (_argc > 2) ? _args[2] : (gd::GdVal::from_str(&battle_string_literals[0]));
    this->f_type = gd::gd_coerce_int(lv__type);
    this->f_isBuff = gd::gd_coerce_bool(([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_isBuff_1006, _ca, 1); })());
    this->f_character = lv__character;
    this->f_signalName = lv__signalName;
    this->f_ctx = gd::native_inline_get_prop(gd_ctx, lv__character, SYM_GEN_ctx_3);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_type, gd::GdVal::from_int(100LL))))) {
        this->f_MAX_STACKS = gd::gd_coerce_int(gd::GdVal::from_int(100000LL));
    }
    else {
        this->f_MAX_STACKS = gd::gd_coerce_int(gd::GdVal::from_int(10000LL));
    }
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_getStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_current;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_setStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_current = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_current = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_reset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return this->fn_setStacks(_ca, 1); })();
    this->f_resistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_resistChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_reflectChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1024, _ca, 1); })();
    this->f_resistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_resistChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_reflectChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeResistChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_resistChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_resistChancePercent, lv_chance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeResistStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_resistStacks = gd::gd_coerce_int(gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_add(gd_ctx, this->f_resistStacks, lv_amount)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeCleanseProtectionChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_cleanseProtectionChancePercent, lv_chance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeReflectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_reflectChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_reflectChancePercent, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_gainStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::gd_neg(gd::GdVal::from_int(1LL)), lv_item, lv_triggerEvent, lv_reflect}; return this->fn_gainTemporary(_ca, 5); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::gd_neg(gd::GdVal::from_int(1LL)), lv_item, lv_triggerEvent, lv_reflect}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainTemporary_1031, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_gainTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
        ++gd_ctx.native_event_counts[2];
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_resisted = gd::GdVal::from_int(0LL);
        gd::GdVal lv_totalResistChance = this->f_resistChancePercent;
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_reflect)))) : gd::GdVal::from_bool(false)))) {
            lv_totalResistChance = gd::gd_sub(lv_totalResistChance, ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getAmplificationChancePercent_195, _ca, 1); })());
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_totalResistChance, gd::GdVal::from_int(0LL))))) {
            {
                gd::NativePrivateIntegerView _t330(gd_ctx, lv_amount);
                uint32_t _len__t332 = _t330.length;
                for (uint32_t _t332 = 0; _t332 < _len__t332; ++_t332) {
                    gd::GdVal lv_i = _t330.at(_t332);
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_totalResistChance}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_flipPercent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                        lv_resisted = gd::gd_add(gd_ctx, lv_resisted, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_totalResistChance, gd::GdVal::from_int(0LL))))) {
            {
                gd::NativePrivateIntegerView _t333(gd_ctx, lv_amount);
                uint32_t _len__t335 = _t333.length;
                for (uint32_t _t335 = 0; _t335 < _len__t335; ++_t335) {
                    gd::GdVal lv_i = _t333.at(_t335);
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_totalResistChance)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_flipPercent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                        lv_amount = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_amount, gd::GdVal::from_int(1LL)));
                    }
                }
            }
        }
        gd::GdVal lv_left = gd::gd_sub(lv_amount, lv_resisted);
        gd::GdVal lv_reflected = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isBuff)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_reflect)))) {
                {
                    gd::NativePrivateIntegerView _t336(gd_ctx, lv_amount);
                    uint32_t _len__t338 = _t336.length;
                    for (uint32_t _t338 = 0; _t338 < _len__t338; ++_t338) {
                        gd::GdVal lv_i = _t336.at(_t338);
                        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_reflectChancePercent}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_flipPercent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                            lv_reflected = gd::gd_add(gd_ctx, lv_reflected, gd::GdVal::from_int(1LL));
                        }
                    }
                }
                lv_left = gd::gd_sub(lv_left, lv_reflected);
                gd::GdVal lv_reflectedByStacks = gd::GdVal::from_int(0LL);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_left, gd::GdVal::from_int(0LL))))) {
                    lv_reflectedByStacks = gd::gd_min(lv_left, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_debuffReflectStacks>(gd_ctx, this->f_character, SYM_GEN_debuffReflectStacks_1073));
                }
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflectedByStacks, gd::GdVal::from_int(0LL))))) {
                    lv_reflected = gd::gd_add(gd_ctx, lv_reflected, lv_reflectedByStacks);
                    lv_left = gd::gd_sub(lv_left, lv_reflectedByStacks);
                    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_reflectedByStacks)}; return native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_changeDebuffReflectStacks>(gd_ctx, this->f_character, SYM_GEN_changeDebuffReflectStacks_1186, _ca, 1); })();
                }
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflected, gd::GdVal::from_int(0LL))))) {
                    lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_reflected));
                    gd::GdVal lv_target = native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_opponent>(gd_ctx, this->f_character, SYM_GEN_opponent_75);
                    (void)gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
                    (void)gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_reflected}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnReflectLabel_1632, _ca, 2); })();
                }
            }
            gd::GdVal lv_ownStacksUsed = gd::gd_min(lv_left, this->f_resistStacks);
            lv_resisted = gd::gd_add(gd_ctx, lv_resisted, lv_ownStacksUsed);
            lv_left = gd::gd_sub(lv_left, lv_ownStacksUsed);
            this->f_resistStacks = gd::gd_coerce_int(gd::gd_sub(this->f_resistStacks, lv_ownStacksUsed));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_left, gd::GdVal::from_int(0LL))))) {
                gd::GdVal lv_characterStacksUsed = gd::gd_min(lv_left, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_debuffResistStacks>(gd_ctx, this->f_character, SYM_GEN_debuffResistStacks_1072));
                lv_resisted = gd::gd_add(gd_ctx, lv_resisted, lv_characterStacksUsed);
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_characterStacksUsed)}; return native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_changeDebuffResistStacks>(gd_ctx, this->f_character, SYM_GEN_changeDebuffResistStacks_1185, _ca, 1); })();
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_resisted, gd::GdVal::from_int(0LL))))) {
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_resisted));
            (void)native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_randBuffLabelPos>(gd_ctx, this->f_character, SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
            (void)native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_randBuffLabelDir>(gd_ctx, this->f_character, SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_resisted}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnResistedLabel_1633, _ca, 2); })();
            gd::GdVal lv_resistedEvent = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_resisted, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_reflect}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_createEvent_StackResistOrNullify>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StackResistOrNullify_1365, _ca, 6); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_resistedEvent}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_logEvent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
            lv_amount = gd::gd_coerce_int(gd::gd_coerce_int(gd::gd_min(lv_amount, gd::gd_sub(this->f_MAX_STACKS, this->f_current))));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_amount, gd::GdVal::from_int(0LL))))) {
                return gd::GdVal::null();
            }
            this->f_current = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_current, lv_amount));
            (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_duration, gd::GdVal::from_int(0LL))))) {
                this->f_permanentStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_permanentStacks, lv_amount));
            }
            else {
                gd::GdVal lv_timeout = gd::gd_add(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_time>(gd_ctx, this->f_ctx, SYM_GEN_time_1411), lv_duration);
                gd::GdVal lv_tempStacks = ([&]() { gd::GdVal _ca[] = {lv_amount, lv_timeout, lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks), gd::SYM_new, _ca, 3); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_tempStacks}; return gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_push_back, _ca, 1); })();
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return this->fn__startTimer(_ca, 1); })();
                    this->f_nextTemporaryTimeout = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
                }
                else {
                    gd::GdVal lv_timerLeft = ([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_float(0.0), this->f__timer_left)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreBuff::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_duration, lv_timerLeft)))) {
                        (void)this->fn__stopTimer(nullptr, 0);
                        (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return this->fn__startTimer(_ca, 1); })();
                        this->f_nextTemporaryTimeout = gd::gd_coerce_int(gd::gd_sub(gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
                    }
                }
                if(gd::native_lazy_diagnostic_required(gd_ctx,1,gd::native_skip_buff_diagnostic(gd_ctx,*this,{lv_duration}))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72]), ([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return this->fn__blnd_snap(_ca, 2); })();
                }
            }
            if (gd::gd_truth(lv_item)) {
                gd::GdVal lv_isPlayer = gd::GdVal::from_bool(gd::native_scalar_eq(this->f_character, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_player>(gd_ctx, this->f_ctx, SYM_GEN_player_1302)));
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isBuff)))) {
                    lv_isPlayer = gd::GdVal::from_bool(!gd::gd_truth(lv_isPlayer));
                }
                (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_amount, lv_isPlayer}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_stackChanged_232, _ca, 3); })();
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_duration, gd::GdVal::from_int(0LL))))) {
                    lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, gd::GdVal::from_bool(false), lv_reflect}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_createEvent_Stack>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Stack_1362, _ca, 7); })();
                }
                else {
                    lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, lv_duration, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_reflect}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_createEvent_StackTemporary>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StackTemporary_1363, _ca, 7); })();
                }
                gd::GdVal lv_appliedToOpponent = gd::GdVal::from_bool(gd::native_scalar_ne(this->f_character, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0)));
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73]), gd::GdVal::from_str(&battle_string_literals[74]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_diag>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
                (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, lv_appliedToOpponent}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnBuffLabel_item_1635, _ca, 4); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_signalName, lv_event}; const gd::GdVal _payload[] = {native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_getAmount>(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0), lv_event}; return gd_native_emit_literal_event(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), _ca, _payload, static_cast<int>(std::size(_payload))); })();
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflected, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_reflected, lv_duration, lv_item, lv_triggerEvent, gd::GdVal::from_bool(true)}; return native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_gainStacksTemporary>(gd_ctx, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_opponent>(gd_ctx, this->f_character, SYM_GEN_opponent_75), SYM_GEN_gainStacksTemporary_1218, _ca, 6); })();
        }
    }
    return lv_event;
    return gd::GdVal::null();
    }
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_resisted = gd::GdVal::from_int(0LL);
        gd::GdVal lv_totalResistChance = this->f_resistChancePercent;
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_reflect)))) : gd::GdVal::from_bool(false)))) {
            lv_totalResistChance = gd::gd_sub(lv_totalResistChance, ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getAmplificationChancePercent_195, _ca, 1); })());
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_totalResistChance, gd::GdVal::from_int(0LL))))) {
            {
                gd::NativePrivateIntegerView _t330(gd_ctx, lv_amount);
                uint32_t _len__t332 = _t330.length;
                for (uint32_t _t332 = 0; _t332 < _len__t332; ++_t332) {
                    gd::GdVal lv_i = _t330.at(_t332);
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_totalResistChance}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                        lv_resisted = gd::gd_add(gd_ctx, lv_resisted, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_totalResistChance, gd::GdVal::from_int(0LL))))) {
            {
                gd::NativePrivateIntegerView _t333(gd_ctx, lv_amount);
                uint32_t _len__t335 = _t333.length;
                for (uint32_t _t335 = 0; _t335 < _len__t335; ++_t335) {
                    gd::GdVal lv_i = _t333.at(_t335);
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_totalResistChance)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                        lv_amount = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_amount, gd::GdVal::from_int(1LL)));
                    }
                }
            }
        }
        gd::GdVal lv_left = gd::gd_sub(lv_amount, lv_resisted);
        gd::GdVal lv_reflected = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isBuff)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_reflect)))) {
                {
                    gd::NativePrivateIntegerView _t336(gd_ctx, lv_amount);
                    uint32_t _len__t338 = _t336.length;
                    for (uint32_t _t338 = 0; _t338 < _len__t338; ++_t338) {
                        gd::GdVal lv_i = _t336.at(_t338);
                        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_reflectChancePercent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                            lv_reflected = gd::gd_add(gd_ctx, lv_reflected, gd::GdVal::from_int(1LL));
                        }
                    }
                }
                lv_left = gd::gd_sub(lv_left, lv_reflected);
                gd::GdVal lv_reflectedByStacks = gd::GdVal::from_int(0LL);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_left, gd::GdVal::from_int(0LL))))) {
                    lv_reflectedByStacks = gd::gd_min(lv_left, gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_debuffReflectStacks_1073));
                }
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflectedByStacks, gd::GdVal::from_int(0LL))))) {
                    lv_reflected = gd::gd_add(gd_ctx, lv_reflected, lv_reflectedByStacks);
                    lv_left = gd::gd_sub(lv_left, lv_reflectedByStacks);
                    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_reflectedByStacks)}; return gd::native_inline_call(gd_ctx, this->f_character, SYM_GEN_changeDebuffReflectStacks_1186, _ca, 1); })();
                }
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflected, gd::GdVal::from_int(0LL))))) {
                    lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_reflected));
                    gd::GdVal lv_target = gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_opponent_75);
                    (void)gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
                    (void)gd::native_inline_call(gd_ctx, lv_target, SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_reflected}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnReflectLabel_1632, _ca, 2); })();
                }
            }
            gd::GdVal lv_ownStacksUsed = gd::gd_min(lv_left, this->f_resistStacks);
            lv_resisted = gd::gd_add(gd_ctx, lv_resisted, lv_ownStacksUsed);
            lv_left = gd::gd_sub(lv_left, lv_ownStacksUsed);
            this->f_resistStacks = gd::gd_coerce_int(gd::gd_sub(this->f_resistStacks, lv_ownStacksUsed));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_left, gd::GdVal::from_int(0LL))))) {
                gd::GdVal lv_characterStacksUsed = gd::gd_min(lv_left, gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_debuffResistStacks_1072));
                lv_resisted = gd::gd_add(gd_ctx, lv_resisted, lv_characterStacksUsed);
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_characterStacksUsed)}; return gd::native_inline_call(gd_ctx, this->f_character, SYM_GEN_changeDebuffResistStacks_1185, _ca, 1); })();
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_resisted, gd::GdVal::from_int(0LL))))) {
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_resisted));
            (void)gd::native_inline_call(gd_ctx, this->f_character, SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
            (void)gd::native_inline_call(gd_ctx, this->f_character, SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_resisted}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnResistedLabel_1633, _ca, 2); })();
            gd::GdVal lv_resistedEvent = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_resisted, gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_reflect}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StackResistOrNullify_1365, _ca, 6); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_resistedEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
            lv_amount = gd::gd_coerce_int(gd::gd_coerce_int(gd::gd_min(lv_amount, gd::gd_sub(this->f_MAX_STACKS, this->f_current))));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_amount, gd::GdVal::from_int(0LL))))) {
                return gd::GdVal::null();
            }
            this->f_current = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_current, lv_amount));
            (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_duration, gd::GdVal::from_int(0LL))))) {
                this->f_permanentStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_permanentStacks, lv_amount));
            }
            else {
                gd::GdVal lv_timeout = gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411), lv_duration);
                gd::GdVal lv_tempStacks = ([&]() { gd::GdVal _ca[] = {lv_amount, lv_timeout, lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks), gd::SYM_new, _ca, 3); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_tempStacks}; return gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_push_back, _ca, 1); })();
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__startTimer_1036, _ca, 1); })();
                    this->f_nextTemporaryTimeout = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
                }
                else {
                    gd::GdVal lv_timerLeft = ([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_float(0.0), this->f__timer_left)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreBuff::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_duration, lv_timerLeft)))) {
                        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__stopTimer_1037, nullptr, 0);
                        (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__startTimer_1036, _ca, 1); })();
                        this->f_nextTemporaryTimeout = gd::gd_coerce_int(gd::gd_sub(gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
                    }
                }
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72]), ([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1034, _ca, 2); })();
            }
            if (gd::gd_truth(lv_item)) {
                gd::GdVal lv_isPlayer = gd::GdVal::from_bool(gd::native_scalar_eq(this->f_character, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302)));
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isBuff)))) {
                    lv_isPlayer = gd::GdVal::from_bool(!gd::gd_truth(lv_isPlayer));
                }
                (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_amount, lv_isPlayer}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_stackChanged_232, _ca, 3); })();
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_duration, gd::GdVal::from_int(0LL))))) {
                    lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, gd::GdVal::from_bool(false), lv_reflect}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Stack_1362, _ca, 7); })();
                }
                else {
                    lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, lv_duration, gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_reflect}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StackTemporary_1363, _ca, 7); })();
                }
                gd::GdVal lv_appliedToOpponent = gd::GdVal::from_bool(gd::native_scalar_ne(this->f_character, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0)));
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73]), gd::GdVal::from_str(&battle_string_literals[74]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
                (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, lv_appliedToOpponent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnBuffLabel_item_1635, _ca, 4); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_signalName, lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0), lv_event}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflected, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_reflected, lv_duration, lv_item, lv_triggerEvent, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_opponent_75), SYM_GEN_gainStacksTemporary_1218, _ca, 6); })();
        }
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_loseStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_used = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    lv_amount = gd::gd_coerce_int(gd::gd_min(this->f_current, lv_amount));
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_used)))) {
        gd::GdVal lv_protected = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_cleanseProtectionChancePercent, gd::GdVal::from_int(0LL))))) {
            {
                gd::NativePrivateIntegerView _t339(gd_ctx, lv_amount);
                uint32_t _len__t341 = _t339.length;
                for (uint32_t _t341 = 0; _t341 < _len__t341; ++_t341) {
                    gd::GdVal lv_i = _t339.at(_t341);
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_cleanseProtectionChancePercent}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_flipPercent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                        lv_protected = gd::gd_add(gd_ctx, lv_protected, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_cleanseProtectionChancePercent, gd::GdVal::from_int(0LL))))) {
            {
                gd::NativePrivateIntegerView _t342(gd_ctx, lv_amount);
                uint32_t _len__t344 = _t342.length;
                for (uint32_t _t344 = 0; _t344 < _len__t344; ++_t344) {
                    gd::GdVal lv_i = _t342.at(_t344);
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_cleanseProtectionChancePercent)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_flipPercent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                        lv_protected = gd::gd_sub(lv_protected, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protected));
        lv_amount = gd::gd_coerce_int(gd::gd_clamp(lv_amount, gd::GdVal::from_int(0LL), this->f_current));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_resistStacks, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            gd::GdVal lv_protectedByStacks = gd::gd_min(lv_amount, this->f_resistStacks);
            lv_protected = gd::gd_add(gd_ctx, lv_protected, lv_protectedByStacks);
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protectedByStacks));
            this->f_resistStacks = gd::gd_coerce_int(gd::gd_sub(this->f_resistStacks, lv_protectedByStacks));
        }
        if (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f_isBuff) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_type, gd::GdVal::from_int(100LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_buffProtectStacks>(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            gd::GdVal lv_protectedByStacks = gd::gd_min(lv_amount, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_buffProtectStacks>(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074));
            lv_protected = gd::gd_add(gd_ctx, lv_protected, lv_protectedByStacks);
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protectedByStacks));
            native_event_set<Gd__gd_core__CoreCharacter>(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074, gd::gd_sub(native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_buffProtectStacks>(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074), lv_protectedByStacks));
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_protected, gd::GdVal::from_int(0LL))))) {
            (void)native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_randBuffLabelPos>(gd_ctx, this->f_character, SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
            (void)native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_randBuffLabelDir>(gd_ctx, this->f_character, SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_protected}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnProtectedLabel_1634, _ca, 2); })();
            gd::GdVal lv_protectedEvent = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_protected, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_createEvent_StackProtect>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StackProtect_1366, _ca, 5); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_protectedEvent}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_logEvent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_permanentStacks, lv_amount)))) {
        this->f_permanentStacks = gd::gd_coerce_int(gd::gd_sub(this->f_permanentStacks, lv_amount));
    }
    else {
        gd::GdVal lv_tempToCleanse = gd::gd_sub(lv_amount, this->f_permanentStacks);
        this->f_permanentStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_tempToCleanse, gd::GdVal::from_int(0LL))))) {
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))) {
                break;
            }
            gd::GdVal lv_farthestTimeout = gd::GdVal::from_int(0LL);
            gd::GdVal lv_farthestIndex = gd::gd_neg(gd::GdVal::from_int(1LL));
            {
                gd::NativePrivateIntegerView _t345(gd_ctx, gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0));
                uint32_t _len__t347 = _t345.length;
                for (uint32_t _t347 = 0; _t347 < _len__t347; ++_t347) {
                    gd::GdVal lv_i = _t345.at(_t347);
                    gd::GdVal lv_stacks = gd::native_array_index(gd_ctx, this->f_temporaryStacks, lv_i);
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042), lv_farthestTimeout)))) {
                        lv_farthestTimeout = gd::native_inline_get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042);
                        lv_farthestIndex = lv_i;
                    }
                }
            }
            gd::GdVal lv_farthest = gd::native_array_index(gd_ctx, this->f_temporaryStacks, lv_farthestIndex);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041), lv_tempToCleanse)))) {
                gd::set_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041, gd::gd_sub(gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041), lv_tempToCleanse));
                if(gd::native_lazy_diagnostic_required(gd_ctx,2,gd::native_skip_buff_farthest_diagnostic(gd_ctx,*this,lv_farthestIndex,lv_farthest))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[76])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return this->fn__blnd_snap(_ca, 2); })();
                }
                lv_tempToCleanse = gd::GdVal::from_int(0LL);
            }
            else {
                lv_tempToCleanse = gd::gd_sub(lv_tempToCleanse, gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041));
                (void)([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_remove, _ca, 1); })();
                if(gd::native_lazy_diagnostic_required(gd_ctx,3,gd::native_skip_buff_diagnostic(gd_ctx,*this,{lv_farthestIndex}))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77]), ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return this->fn__blnd_snap(_ca, 2); })();
                }
                if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))) {
                    (void)this->fn__stopTimer(nullptr, 0);
                }
            }
        }
    }
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), lv_amount, lv_item, lv_triggerEvent, lv_used}; return this->fn_changeCurrentLogShowLabel(_ca, 5); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_used = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    lv_amount = gd::gd_coerce_int(gd::gd_min(this->f_current, lv_amount));
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_used)))) {
        gd::GdVal lv_protected = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_cleanseProtectionChancePercent, gd::GdVal::from_int(0LL))))) {
            {
                gd::NativePrivateIntegerView _t339(gd_ctx, lv_amount);
                uint32_t _len__t341 = _t339.length;
                for (uint32_t _t341 = 0; _t341 < _len__t341; ++_t341) {
                    gd::GdVal lv_i = _t339.at(_t341);
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_cleanseProtectionChancePercent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                        lv_protected = gd::gd_add(gd_ctx, lv_protected, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_cleanseProtectionChancePercent, gd::GdVal::from_int(0LL))))) {
            {
                gd::NativePrivateIntegerView _t342(gd_ctx, lv_amount);
                uint32_t _len__t344 = _t342.length;
                for (uint32_t _t344 = 0; _t344 < _len__t344; ++_t344) {
                    gd::GdVal lv_i = _t342.at(_t344);
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_cleanseProtectionChancePercent)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
                        lv_protected = gd::gd_sub(lv_protected, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protected));
        lv_amount = gd::gd_coerce_int(gd::gd_clamp(lv_amount, gd::GdVal::from_int(0LL), this->f_current));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_resistStacks, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            gd::GdVal lv_protectedByStacks = gd::gd_min(lv_amount, this->f_resistStacks);
            lv_protected = gd::gd_add(gd_ctx, lv_protected, lv_protectedByStacks);
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protectedByStacks));
            this->f_resistStacks = gd::gd_coerce_int(gd::gd_sub(this->f_resistStacks, lv_protectedByStacks));
        }
        if (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f_isBuff) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_type, gd::GdVal::from_int(100LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            gd::GdVal lv_protectedByStacks = gd::gd_min(lv_amount, gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074));
            lv_protected = gd::gd_add(gd_ctx, lv_protected, lv_protectedByStacks);
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protectedByStacks));
            gd::set_prop(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074, gd::gd_sub(gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074), lv_protectedByStacks));
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_protected, gd::GdVal::from_int(0LL))))) {
            (void)gd::native_inline_call(gd_ctx, this->f_character, SYM_GEN_randBuffLabelPos_1143, nullptr, 0);
            (void)gd::native_inline_call(gd_ctx, this->f_character, SYM_GEN_randBuffLabelDir_1144, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_protected}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnProtectedLabel_1634, _ca, 2); })();
            gd::GdVal lv_protectedEvent = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_protected, gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StackProtect_1366, _ca, 5); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_protectedEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_permanentStacks, lv_amount)))) {
        this->f_permanentStacks = gd::gd_coerce_int(gd::gd_sub(this->f_permanentStacks, lv_amount));
    }
    else {
        gd::GdVal lv_tempToCleanse = gd::gd_sub(lv_amount, this->f_permanentStacks);
        this->f_permanentStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_tempToCleanse, gd::GdVal::from_int(0LL))))) {
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))) {
                break;
            }
            gd::GdVal lv_farthestTimeout = gd::GdVal::from_int(0LL);
            gd::GdVal lv_farthestIndex = gd::gd_neg(gd::GdVal::from_int(1LL));
            {
                gd::NativePrivateIntegerView _t345(gd_ctx, gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0));
                uint32_t _len__t347 = _t345.length;
                for (uint32_t _t347 = 0; _t347 < _len__t347; ++_t347) {
                    gd::GdVal lv_i = _t345.at(_t347);
                    gd::GdVal lv_stacks = gd::native_array_index(gd_ctx, this->f_temporaryStacks, lv_i);
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042), lv_farthestTimeout)))) {
                        lv_farthestTimeout = gd::native_inline_get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042);
                        lv_farthestIndex = lv_i;
                    }
                }
            }
            gd::GdVal lv_farthest = gd::native_array_index(gd_ctx, this->f_temporaryStacks, lv_farthestIndex);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041), lv_tempToCleanse)))) {
                gd::set_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041, gd::gd_sub(gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041), lv_tempToCleanse));
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[75]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::GdVal::from_str(&battle_string_literals[76])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1034, _ca, 2); })();
                lv_tempToCleanse = gd::GdVal::from_int(0LL);
            }
            else {
                lv_tempToCleanse = gd::gd_sub(lv_tempToCleanse, gd::native_inline_get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041));
                (void)([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_remove, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77]), ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1034, _ca, 2); })();
                if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))) {
                    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__stopTimer_1037, nullptr, 0);
                }
            }
        }
    }
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), lv_amount, lv_item, lv_triggerEvent, lv_used}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCurrentLogShowLabel_1033, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeCurrentLogShowLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_isTimeout = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_isTimeout = gd::gd_coerce_bool(lv_isTimeout);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_used = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    lv_used = gd::gd_coerce_bool(lv_used);
    gd::GdVal lv_change = gd::gd_min(this->f_current, lv_amount);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_change, gd::GdVal::from_int(0LL))))) {
        this->f_current = gd::gd_coerce_int(gd::gd_sub(this->f_current, lv_change));
        (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
        if (gd::gd_truth(lv_item)) {
            gd::GdVal lv_isPlayer = gd::GdVal::from_bool(gd::native_scalar_eq(this->f_character, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_player>(gd_ctx, this->f_ctx, SYM_GEN_player_1302)));
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_used)))) {
                if (gd::gd_truth(this->f_isBuff)) {
                    lv_isPlayer = gd::GdVal::from_bool(!gd::gd_truth(lv_isPlayer));
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, gd::gd_neg(lv_change), lv_isPlayer, lv_used}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_stackChanged_232, _ca, 4); })();
            gd::GdVal lv_event = gd::GdVal::null();
            if (gd::gd_truth(lv_isTimeout)) {
                lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_createEvent_StackTimeout>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StackTimeout_1364, _ca, 5); })();
            }
            else {
                lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_used}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_createEvent_Stack>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Stack_1362, _ca, 6); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_signalName, lv_event}; const gd::GdVal _payload[] = {native_event_call<Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::fn_getAmount>(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0), lv_event}; return gd_native_emit_literal_event(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), _ca, _payload, static_cast<int>(std::size(_payload))); })();
            gd::GdVal lv_appliedToOpponent = gd::GdVal::from_bool(gd::native_scalar_ne(this->f_character, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0)));
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), lv_appliedToOpponent}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnBuffLabel_item_1635, _ca, 4); })();
            return lv_event;
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
    }
    gd::GdVal lv_isTimeout = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_isTimeout = gd::gd_coerce_bool(lv_isTimeout);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_used = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    lv_used = gd::gd_coerce_bool(lv_used);
    gd::GdVal lv_change = gd::gd_min(this->f_current, lv_amount);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_change, gd::GdVal::from_int(0LL))))) {
        this->f_current = gd::gd_coerce_int(gd::gd_sub(this->f_current, lv_change));
        (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_activateBuffCounter_1623, _ca, 2); })();
        if (gd::gd_truth(lv_item)) {
            gd::GdVal lv_isPlayer = gd::GdVal::from_bool(gd::native_scalar_eq(this->f_character, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302)));
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_used)))) {
                if (gd::gd_truth(this->f_isBuff)) {
                    lv_isPlayer = gd::GdVal::from_bool(!gd::gd_truth(lv_isPlayer));
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, gd::gd_neg(lv_change), lv_isPlayer, lv_used}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_stackChanged_232, _ca, 4); })();
            gd::GdVal lv_event = gd::GdVal::null();
            if (gd::gd_truth(lv_isTimeout)) {
                lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_StackTimeout_1364, _ca, 5); })();
            }
            else {
                lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_used}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Stack_1362, _ca, 6); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_signalName, lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getAmount_1576, nullptr, 0), lv_event}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
            gd::GdVal lv_appliedToOpponent = gd::GdVal::from_bool(gd::native_scalar_ne(this->f_character, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_character_74, nullptr, 0)));
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_378, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), lv_appliedToOpponent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnBuffLabel_item_1635, _ca, 4); })();
            return lv_event;
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn__blnd_snap(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_op = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_pre = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f__stacktrace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__b = gd::GdVal::from_str(&battle_string_literals[0]);
        {
            gd::GdVal _t348 = gd::gd_iter_seq(gd_ctx.arena, this->f_temporaryStacks);
            gd::GdArr* _t349 = (_t348.kind == gd::GdVal::Kind::Arr) ? _t348.arr : nullptr;
            uint32_t _len__t350 = _t349 ? _t349->len : 0u;
            for (uint32_t _t350 = 0; _t350 < _len__t350; ++_t350) {
                gd::GdVal lv_ts = _t349->data[_t350];
                lv__b = gd::gd_add(gd_ctx, lv__b, gd::gd_mod(gd_ctx, gd::GdVal::from_str(&battle_string_literals[78]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_ts, SYM_GEN_amount_1041)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(5LL)}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_ts, SYM_GEN_timeout_1042)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::SYM_substr, _ca, 2); })()}))));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[79]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[80]), ([&]() { gd::GdVal _ca[] = {native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, this->f_character, SYM_GEN_playerId_1046)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[81])), ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[82])), lv_op), gd::GdVal::from_str(&battle_string_literals[82])), lv_pre), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[83]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[84])), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[85])), ([&]() { gd::GdVal _ca[] = {this->f__timer_active}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[86])), ([&]() { gd::GdVal _ca[] = {this->f__timer_left}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[87])), ([&]() { gd::GdVal _ca[] = {native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_frame_counter>(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1413)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), lv__b}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_diag>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    return gd::GdVal::null();
    }
    gd::GdVal lv_op = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_pre = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__b = gd::GdVal::from_str(&battle_string_literals[0]);
        {
            gd::GdVal _t348 = gd::gd_iter_seq(gd_ctx.arena, this->f_temporaryStacks);
            gd::GdArr* _t349 = (_t348.kind == gd::GdVal::Kind::Arr) ? _t348.arr : nullptr;
            uint32_t _len__t350 = _t349 ? _t349->len : 0u;
            for (uint32_t _t350 = 0; _t350 < _len__t350; ++_t350) {
                gd::GdVal lv_ts = _t349->data[_t350];
                lv__b = gd::gd_add(gd_ctx, lv__b, gd::gd_mod(gd_ctx, gd::GdVal::from_str(&battle_string_literals[78]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_ts, SYM_GEN_amount_1041)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(5LL)}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_ts, SYM_GEN_timeout_1042)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::SYM_substr, _ca, 2); })()}))));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[79]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[80]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[81])), ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[82])), lv_op), gd::GdVal::from_str(&battle_string_literals[82])), lv_pre), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[83]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[84])), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[85])), ([&]() { gd::GdVal _ca[] = {this->f__timer_active}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[86])), ([&]() { gd::GdVal _ca[] = {this->f__timer_left}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[87])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1413)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), lv__b}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_onTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    if(gd::native_lazy_diagnostic_required(gd_ctx,4,gd::native_skip_buff_diagnostic(gd_ctx,*this,{this->f_nextTemporaryTimeout}))) {
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88]), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return this->fn__blnd_snap(_ca, 2); })();
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_nextTemporaryTimeout, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_nextTemporaryTimeout, gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_timedOutStacks = gd::native_array_index(gd_ctx, this->f_temporaryStacks, this->f_nextTemporaryTimeout);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::native_inline_get_prop(gd_ctx, lv_timedOutStacks, SYM_GEN_amount_1041), gd::native_inline_get_prop(gd_ctx, lv_timedOutStacks, SYM_GEN_item_1043)}; return this->fn_changeCurrentLogShowLabel(_ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_remove, _ca, 1); })();
        if(gd::native_lazy_diagnostic_required(gd_ctx,5,gd::native_skip_buff_diagnostic(gd_ctx,*this,{this->f_nextTemporaryTimeout}))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89]), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return this->fn__blnd_snap(_ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_native_frame_rng>(gd_ctx, this->f_ctx, SYM_GEN_native_frame_rng_1450))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))))) {
        gd::GdVal lv_earliestTimeout = gd::GdVal::from_float(std::numeric_limits<double>::infinity());
        gd::GdVal lv_earliestIndex = gd::gd_neg(gd::GdVal::from_int(1LL));
        {
            gd::NativePrivateIntegerView _t351(gd_ctx, gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0));
            uint32_t _len__t353 = _t351.length;
            for (uint32_t _t353 = 0; _t353 < _len__t353; ++_t353) {
                gd::GdVal lv_i = _t351.at(_t353);
                gd::GdVal lv_stacks = gd::native_array_index(gd_ctx, this->f_temporaryStacks, lv_i);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042), lv_earliestTimeout)))) {
                    lv_earliestTimeout = gd::native_inline_get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042);
                    lv_earliestIndex = lv_i;
                }
            }
        }
        this->f_nextTemporaryTimeout = gd::gd_coerce_int(lv_earliestIndex);
        gd::GdVal lv_delay = gd::gd_sub(lv_earliestTimeout, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_time>(gd_ctx, this->f_ctx, SYM_GEN_time_1411));
        if(gd::native_lazy_diagnostic_required(gd_ctx,6,gd::native_skip_buff_timeout_diagnostic(gd_ctx,*this,lv_delay,lv_earliestTimeout))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[90]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[91]), ([&]() { gd::GdVal _ca[] = {lv_delay}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[92])), ([&]() { gd::GdVal _ca[] = {lv_earliestTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[93])), ([&]() { gd::GdVal _ca[] = {native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_time>(gd_ctx, this->f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return this->fn__blnd_snap(_ca, 2); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_delay, gd::GdVal::from_float(0.01))))) {
            (void)this->fn_onTimeout(nullptr, 0);
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_delay}; return this->fn__startTimer(_ca, 1); })();
        }
    }
    return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88]), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1034, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_nextTemporaryTimeout, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_nextTemporaryTimeout, gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_timedOutStacks = gd::native_array_index(gd_ctx, this->f_temporaryStacks, this->f_nextTemporaryTimeout);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::native_inline_get_prop(gd_ctx, lv_timedOutStacks, SYM_GEN_amount_1041), gd::native_inline_get_prop(gd_ctx, lv_timedOutStacks, SYM_GEN_item_1043)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCurrentLogShowLabel_1033, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_remove, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89]), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1034, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_native_frame_rng_1450))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))))) {
        gd::GdVal lv_earliestTimeout = gd::GdVal::from_float(std::numeric_limits<double>::infinity());
        gd::GdVal lv_earliestIndex = gd::gd_neg(gd::GdVal::from_int(1LL));
        {
            gd::NativePrivateIntegerView _t351(gd_ctx, gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0));
            uint32_t _len__t353 = _t351.length;
            for (uint32_t _t353 = 0; _t353 < _len__t353; ++_t353) {
                gd::GdVal lv_i = _t351.at(_t353);
                gd::GdVal lv_stacks = gd::native_array_index(gd_ctx, this->f_temporaryStacks, lv_i);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042), lv_earliestTimeout)))) {
                    lv_earliestTimeout = gd::native_inline_get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042);
                    lv_earliestIndex = lv_i;
                }
            }
        }
        this->f_nextTemporaryTimeout = gd::gd_coerce_int(lv_earliestIndex);
        gd::GdVal lv_delay = gd::gd_sub(lv_earliestTimeout, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[90]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[91]), ([&]() { gd::GdVal _ca[] = {lv_delay}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[92])), ([&]() { gd::GdVal _ca[] = {lv_earliestTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[93])), ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1411)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1034, _ca, 2); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_delay, gd::GdVal::from_float(0.01))))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTimeout_1035, nullptr, 0);
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_delay}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__startTimer_1036, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    (void)this->fn__stopTimer(nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__stopTimer_1037, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_temporaryStacks, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn__startTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_duration, gd::GdVal::from_float(0.0))))) {
        this->f__timer_wait = ([&]() { gd::GdVal _ca[] = {lv_duration}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreBuff::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    }
    this->f__timer_left = this->f__timer_wait;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active)))) {
        this->f__timer_first_pass = gd::gd_add(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_timer_pass_epoch>(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445), gd::GdVal::from_int(1LL));
        if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_in_physics_timer_pass>(gd_ctx, this->f_ctx, SYM_GEN_in_physics_timer_pass_1446)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f__timer_member_epoch, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_timer_pass_epoch>(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445))))) : gd::GdVal::from_bool(false)))) {
            this->f__timer_first_pass = native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_timer_pass_epoch>(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445);
        }
    }
    this->f__timer_active = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
    }
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_duration, gd::GdVal::from_float(0.0))))) {
        this->f__timer_wait = ([&]() { gd::GdVal _ca[] = {lv_duration}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreBuff::call_static_fn(gd_ctx, SYM_GEN__f32eng_505, _ca, 1, _out); return _out; })();
    }
    this->f__timer_left = this->f__timer_wait;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active)))) {
        this->f__timer_first_pass = gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445), gd::GdVal::from_int(1LL));
        if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_in_physics_timer_pass_1446)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f__timer_member_epoch, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445))))) : gd::GdVal::from_bool(false)))) {
            this->f__timer_first_pass = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445);
        }
    }
    this->f__timer_active = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::sf__f32eng(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    (void)gd_ctx;
    const auto value = gd::gd_coerce_float(_argc > 0 ? _args[0] : gd::GdVal::null());
    return gd::GdVal::from_float(static_cast<double>(static_cast<float>(value.as_float())));
}
gd::GdVal Gd__gd_core__CoreBuff::fn__stopTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    this->f__timer_member_epoch = gd::gd_neg(gd::GdVal::from_int(1LL));
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_in_physics_timer_pass>(gd_ctx, this->f_ctx, SYM_GEN_in_physics_timer_pass_1446)) ? gd::GdVal::from_bool(gd::gd_truth(this->f__timer_active)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f__timer_first_pass, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_timer_pass_epoch>(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445))))) : gd::GdVal::from_bool(false)))) {
        this->f__timer_member_epoch = native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_timer_pass_epoch>(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445);
    }
    this->f__timer_active = gd::GdVal::from_bool(false);
    this->f__timer_left = gd::gd_neg(gd::GdVal::from_float(1.0));
    return gd::GdVal::null();
    }
    this->f__timer_member_epoch = gd::gd_neg(gd::GdVal::from_int(1LL));
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_in_physics_timer_pass_1446)) ? gd::GdVal::from_bool(gd::gd_truth(this->f__timer_active)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f__timer_first_pass, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445))))) : gd::GdVal::from_bool(false)))) {
        this->f__timer_member_epoch = gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445);
    }
    this->f__timer_active = gd::GdVal::from_bool(false);
    this->f__timer_left = gd::gd_neg(gd::GdVal::from_float(1.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_isTimerActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f__timer_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn__tick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_timer_pass_epoch>(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445), this->f__timer_first_pass))))))) {
        return gd::GdVal::null();
    }
    this->f__timer_left = gd::gd_sub(this->f__timer_left, lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__timer_left, gd::GdVal::from_float(0.0))))) {
        this->f__timer_active = gd::GdVal::from_bool(false);
        this->f__timer_left = gd::gd_neg(gd::GdVal::from_float(1.0));
        (void)this->fn_onTimeout(nullptr, 0);
    }
    return gd::GdVal::null();
    }
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_timer_pass_epoch_1445), this->f__timer_first_pass))))))) {
        return gd::GdVal::null();
    }
    this->f__timer_left = gd::gd_sub(this->f__timer_left, lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f__timer_left, gd::GdVal::from_float(0.0))))) {
        this->f__timer_active = gd::GdVal::from_bool(false);
        this->f__timer_left = gd::gd_neg(gd::GdVal::from_float(1.0));
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTimeout_1035, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_rebuildTimerSeen(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreBuff(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreBuff>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,22u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreBuff = {CLS_Gd__gd_core__CoreBuff, "CoreBuff", "res://gd_core/CoreBuff.gd", nullptr, false, _alloc_Gd__gd_core__CoreBuff, &Gd__gd_core__CoreBuff::get_static_prop_fn, &Gd__gd_core__CoreBuff::call_static_fn};

void Gd__gd_core__CoreItem__INNER__CoreSignalConnection::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_emitter = gd::GdVal::null();
    this->f_signalName = gd::GdVal::null();
    this->f_receiver = gd::GdVal::null();
    this->f_methodName = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreItem__INNER__CoreSignalConnection::meta() const { return &META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection; }
gd::GdVal Gd__gd_core__CoreItem__INNER__CoreSignalConnection::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_emitter_1654: out = this->f_emitter; return true;
        case SYM_GEN_signalName_1013: out = this->f_signalName; return true;
        case SYM_GEN_receiver_1655: out = this->f_receiver; return true;
        case SYM_GEN_methodName_1656: out = this->f_methodName; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_emitter_1654: this->f_emitter = val; return true;
        case SYM_GEN_signalName_1013: this->f_signalName = val; return true;
        case SYM_GEN_receiver_1655: this->f_receiver = val; return true;
        case SYM_GEN_methodName_1656: this->f_methodName = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_destroy_1657: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_destroy_1657: out = fn_destroy(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem__INNER__CoreSignalConnection::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreItem__INNER__CoreSignalConnection::fn__init(const gd::GdVal* _args, int _argc) {
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_emitter, this->f_signalName, this->f_receiver, this->f_methodName}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_receiver, SYM_GEN_ctx_3), SYM_GEN_bus_1408), SYM_GEN_connectEvent_1595, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem__INNER__CoreSignalConnection::fn_destroy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreItem__INNER__CoreSignalConnection(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreItem__INNER__CoreSignalConnection>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,41u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection = {CLS_Gd__gd_core__CoreItem__INNER__CoreSignalConnection, "CoreSignalConnection", "", nullptr, false, _alloc_Gd__gd_core__CoreItem__INNER__CoreSignalConnection, &Gd__gd_core__CoreItem__INNER__CoreSignalConnection::get_static_prop_fn, &Gd__gd_core__CoreItem__INNER__CoreSignalConnection::call_static_fn};

void Gd__gd_core__DancingDragon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__DancingDragon::meta() const { return &META_Gd__gd_core__DancingDragon; }
gd::GdVal Gd__gd_core__DancingDragon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__DancingDragon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__DancingDragon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__DancingDragon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DancingDragon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__DancingDragon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__DancingDragon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__DancingDragon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(23LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[94]), gd::GdVal::from_str(&battle_string_literals[95])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[96]), gd::GdVal::from_str(&battle_string_literals[97])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numAffected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_numAffected)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), lv_numAffected)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_amount)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), lv_amount)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistChances_1220, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DancingDragon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DancingDragon(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__DancingDragon>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,56u); return object; }
const gd::GdClassMeta META_Gd__gd_core__DancingDragon = {CLS_Gd__gd_core__DancingDragon, "DancingDragon", "res://gd_core/DancingDragon.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__DancingDragon, &Gd__gd_core__DancingDragon::get_static_prop_fn, &Gd__gd_core__DancingDragon::call_static_fn};

void Gd__gd_core__FannyPack::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bag::init_fields(gd_ctx);
    this->f_speedBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__FannyPack::meta() const { return &META_Gd__gd_core__FannyPack; }
gd::GdVal Gd__gd_core__FannyPack::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__FannyPack::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__FannyPack::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        default: break;
    }
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__FannyPack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__FannyPack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__FannyPack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__FannyPack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__FannyPack::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = gd::GdVal::from_bool(false);
    gd::GdVal lv_totalSpeed = this->f_speedBonus;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        lv_totalSpeed = gd::gd_add(gd_ctx, lv_totalSpeed, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)));
    }
    {
        gd::GdVal _t354 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t355 = (_t354.kind == gd::GdVal::Kind::Arr) ? _t354.arr : nullptr;
        uint32_t _len__t356 = _t355 ? _t355->len : 0u;
        for (uint32_t _t356 = 0; _t356 < _len__t356; ++_t356) {
            gd::GdVal lv_item = _t355->data[_t356];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_totalSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
                lv_active = gd::GdVal::from_bool(true);
            }
        }
    }
    if (gd::gd_truth(lv_active)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FannyPack::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_hasCooldown_95, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_isBag_83, nullptr, 0))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FannyPack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__FannyPack(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__FannyPack>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,69u); return object; }
const gd::GdClassMeta META_Gd__gd_core__FannyPack = {CLS_Gd__gd_core__FannyPack, "FannyPack", "res://gd_core/FannyPack.gd", &META_Gd__gd_core__Bag, false, _alloc_Gd__gd_core__FannyPack, &Gd__gd_core__FannyPack::get_static_prop_fn, &Gd__gd_core__FannyPack::call_static_fn};

void Gd__gd_core__HolyArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__HolyArmor::meta() const { return &META_Gd__gd_core__HolyArmor; }
gd::GdVal Gd__gd_core__HolyArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HolyArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HolyArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__HolyArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HolyArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__HolyArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HolyArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HolyArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolyArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    gd::GdVal lv_numAffected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_numAffected, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolyArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleansePoison_342, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolyArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HolyArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__HolyArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,87u); return object; }
const gd::GdClassMeta META_Gd__gd_core__HolyArmor = {CLS_Gd__gd_core__HolyArmor, "HolyArmor", "res://gd_core/HolyArmor.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__HolyArmor, &Gd__gd_core__HolyArmor::get_static_prop_fn, &Gd__gd_core__HolyArmor::call_static_fn};

void Gd__gd_core__ManaOrb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_stackTypes = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_bonusBuffs = gd::GdVal::from_int(0);
    this->f_mana = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::from_int(0);
    this->f_buffs = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__ManaOrb::meta() const { return &META_Gd__gd_core__ManaOrb; }
gd::GdVal Gd__gd_core__ManaOrb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ManaOrb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ManaOrb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: out = this->f_stackTypes; return true;
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_bonusBuffs_1927: out = this->f_bonusBuffs; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__ManaOrb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: this->f_stackTypes = val; return true;
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_bonusBuffs_1927: this->f_bonusBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ManaOrb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_addBonusRandomBuffs_1930: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__ManaOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_addBonusRandomBuffs_1930: out = fn_addBonusRandomBuffs(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ManaOrb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ManaOrb::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    {
        gd::GdVal _t357 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t358 = (_t357.kind == gd::GdVal::Kind::Arr) ? _t357.arr : nullptr;
        uint32_t _len__t359 = _t358 ? _t358->len : 0u;
        for (uint32_t _t359 = 0; _t359 < _len__t359; ++_t359) {
            gd::GdVal lv_item = _t358->data[_t359];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_str(&battle_string_literals[100])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[101]), gd::GdVal::from_str(&battle_string_literals[102])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_buffs, this->f_bonusBuffs), lv_event, this->f_stackTypes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 3); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_addBonusRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_bonusBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusBuffs, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__activated = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__activated = gd::gd_coerce_bool(lv__activated);
    this->f_activated = gd::gd_coerce_bool(lv__activated);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_manaNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    this->f_buffs = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    this->f_stackTypes = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL)}; return gd::native_inline_call(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ManaOrb(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__ManaOrb>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,103u); return object; }
const gd::GdClassMeta META_Gd__gd_core__ManaOrb = {CLS_Gd__gd_core__ManaOrb, "ManaOrb", "res://gd_core/ManaOrb.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__ManaOrb, &Gd__gd_core__ManaOrb::get_static_prop_fn, &Gd__gd_core__ManaOrb::call_static_fn};

void Gd__gd_core__PoisonGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__PoisonGoobert::meta() const { return &META_Gd__gd_core__PoisonGoobert; }
gd::GdVal Gd__gd_core__PoisonGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PoisonGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PoisonGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__PoisonGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PoisonGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__PoisonGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PoisonGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PoisonGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PoisonGoobert(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__PoisonGoobert>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,118u); return object; }
const gd::GdClassMeta META_Gd__gd_core__PoisonGoobert = {CLS_Gd__gd_core__PoisonGoobert, "PoisonGoobert", "res://gd_core/PoisonGoobert.gd", &META_Gd__gd_core__Goobert, false, _alloc_Gd__gd_core__PoisonGoobert, &Gd__gd_core__PoisonGoobert::get_static_prop_fn, &Gd__gd_core__PoisonGoobert::call_static_fn};

void Gd__gd_core__SpectralDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Dagger::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__SpectralDagger::meta() const { return &META_Gd__gd_core__SpectralDagger; }
gd::GdVal Gd__gd_core__SpectralDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__SpectralDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__SpectralDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Dagger::get_prop(prop, out);
}
bool Gd__gd_core__SpectralDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__SpectralDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Dagger::has_own_method(m);
}
bool Gd__gd_core__SpectralDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__SpectralDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__SpectralDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
        if (gd::gd_truth(lv_event)) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)));
            (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_makeSpectral_1564, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SpectralDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__SpectralDagger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__SpectralDagger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,137u); return object; }
const gd::GdClassMeta META_Gd__gd_core__SpectralDagger = {CLS_Gd__gd_core__SpectralDagger, "SpectralDagger", "res://gd_core/SpectralDagger.gd", &META_Gd__gd_core__Dagger, false, _alloc_Gd__gd_core__SpectralDagger, &Gd__gd_core__SpectralDagger::get_static_prop_fn, &Gd__gd_core__SpectralDagger::call_static_fn};

void Gd__gd_core_items__StoneSkinPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__StoneSkinPotion::meta() const { return &META_Gd__gd_core_items__StoneSkinPotion; }
gd::GdVal Gd__gd_core_items__StoneSkinPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StoneSkinPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StoneSkinPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__StoneSkinPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StoneSkinPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBlockChanged_1986: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__StoneSkinPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBlockChanged_1986: out = fn_onBlockChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StoneSkinPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StoneSkinPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_328, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StoneSkinPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[103]), gd::GdVal::from_str(&battle_string_literals[104])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StoneSkinPotion::fn_onBlockChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBlock_204, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StoneSkinPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StoneSkinPotion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__StoneSkinPotion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,651u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__StoneSkinPotion = {CLS_Gd__gd_core_items__StoneSkinPotion, "StoneSkinPotion", "res://gd_core_items/StoneSkinPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__StoneSkinPotion, &Gd__gd_core_items__StoneSkinPotion::get_static_prop_fn, &Gd__gd_core_items__StoneSkinPotion::call_static_fn};

void Gd__gd_core__WoodenSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__WoodenSword::meta() const { return &META_Gd__gd_core__WoodenSword; }
gd::GdVal Gd__gd_core__WoodenSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__WoodenSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__WoodenSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__WoodenSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__WoodenSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__WoodenSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__WoodenSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__WoodenSword::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__WoodenSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__WoodenSword(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__WoodenSword>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,165u); return object; }
const gd::GdClassMeta META_Gd__gd_core__WoodenSword = {CLS_Gd__gd_core__WoodenSword, "WoodenSword", "res://gd_core/WoodenSword.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__WoodenSword, &Gd__gd_core__WoodenSword::get_static_prop_fn, &Gd__gd_core__WoodenSword::call_static_fn};

void Gd__gd_core_items__Dagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Dagger::meta() const { return &META_Gd__gd_core_items__Dagger; }
gd::GdVal Gd__gd_core_items__Dagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Dagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Dagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Dagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Dagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_onStun_946: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Dagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onStun_946: out = fn_onStun(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Dagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Dagger::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[105]), gd::GdVal::from_str(&battle_string_literals[106])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Dagger::fn_onStun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attack_941, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Dagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Dagger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Dagger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,197u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Dagger = {CLS_Gd__gd_core_items__Dagger, "Dagger", "res://gd_core_items/Dagger.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Dagger, &Gd__gd_core_items__Dagger::get_static_prop_fn, &Gd__gd_core_items__Dagger::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Crown_CrownState[] = {{"Inactive", 0LL}, {"Active", 1LL}, {"Used", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Crown_CrownState = {"CrownState", _ekv_Gd__gd_core_items__Crown_CrownState, 3u};
void Gd__gd_core_items__Crown::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_crownState = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Crown::meta() const { return &META_Gd__gd_core_items__Crown; }
gd::GdVal Gd__gd_core_items__Crown::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_CrownState_1822: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Crown_CrownState);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Crown::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_CrownState_1822: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Crown_CrownState); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Crown::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_crownState_1818: out = this->f_crownState; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_CrownState_1822: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Crown_CrownState); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Crown::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_crownState_1818: this->f_crownState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Crown::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onInvuEnded_1820: return true;
        case SYM_GEN_checkTrigger_1821: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Crown::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onInvuEnded_1820: out = fn_onInvuEnded(args, argc); return true;
        case SYM_GEN_checkTrigger_1821: out = fn_checkTrigger(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Crown::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Crown::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[101]), gd::GdVal::from_str(&battle_string_literals[107])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[108]), gd::GdVal::from_str(&battle_string_literals[109])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_onInvuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTrigger_1821, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_checkTrigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_crownState, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_isVulnerable_1291, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_331, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[110])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_makeInvulnerable_1211, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseBlind_344, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__crownState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__crownState, gd::GdVal::from_int(0LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__crownState, gd::GdVal::from_int(1LL))))) {
    }
    else {
    }
    this->f_crownState = gd::gd_coerce_int(lv__crownState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Crown::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[111]), gd::GdVal::from_str(&battle_string_literals[112]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[113])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Crown(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Crown>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,193u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Crown = {CLS_Gd__gd_core_items__Crown, "Crown", "res://gd_core_items/Crown.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Crown, &Gd__gd_core_items__Crown::get_static_prop_fn, &Gd__gd_core_items__Crown::call_static_fn};

void Gd__gd_core_items__Exclusive__AmethystWhelp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmethystWhelp::meta() const { return &META_Gd__gd_core_items__Exclusive__AmethystWhelp; }
gd::GdVal Gd__gd_core_items__Exclusive__AmethystWhelp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmethystWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmethystWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmethystWhelp::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmethystWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmethystWhelp(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__AmethystWhelp>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,210u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmethystWhelp = {CLS_Gd__gd_core_items__Exclusive__AmethystWhelp, "AmethystWhelp", "res://gd_core_items/Exclusive/AmethystWhelp.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__AmethystWhelp, &Gd__gd_core_items__Exclusive__AmethystWhelp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmethystWhelp::call_static_fn};

void Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__CouragePuppy::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::meta() const { return &META_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy; }
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__CouragePuppy::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Exclusive__CouragePuppy::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Exclusive__CouragePuppy::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__CouragePuppy::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__CouragePuppy::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__CouragePuppy::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__CouragePuppy::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1565), SYM_GEN_CanTriggerItems_2696)}; return gd::native_inline_call(gd_ctx, this->f_damageSource, SYM_GEN_unsetFlag_1556, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1565), SYM_GEN_CanTriggerSpikes_2697)}; return gd::native_inline_call(gd_ctx, this->f_damageSource, SYM_GEN_unsetFlag_1556, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ArmoredCouragePuppy>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,225u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy = {CLS_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy, "ArmoredCouragePuppy", "res://gd_core_items/Exclusive/ArmoredCouragePuppy.gd", &META_Gd__gd_core_items__Exclusive__CouragePuppy, true, _alloc_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy, &Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ArmoredCouragePuppy::call_static_fn};

void Gd__gd_core_items__Exclusive__Bewitchment::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_typesDict = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
    this->f_numDebuffs = gd::GdVal::null();
    this->f_bonusPoison = gd::GdVal::null();
    this->f_bonusBlind = gd::GdVal::null();
    this->f_bonusCold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Bewitchment::meta() const { return &META_Gd__gd_core_items__Exclusive__Bewitchment; }
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Bewitchment::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_typesDict_2068: out = this->f_typesDict; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_numDebuffs_2048: out = this->f_numDebuffs; return true;
        case SYM_GEN_bonusPoison_2069: out = this->f_bonusPoison; return true;
        case SYM_GEN_bonusBlind_2070: out = this->f_bonusBlind; return true;
        case SYM_GEN_bonusCold_2071: out = this->f_bonusCold; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_typesDict_2068: this->f_typesDict = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_numDebuffs_2048: this->f_numDebuffs = val; return true;
        case SYM_GEN_bonusPoison_2069: this->f_bonusPoison = val; return true;
        case SYM_GEN_bonusBlind_2070: this->f_bonusBlind = val; return true;
        case SYM_GEN_bonusCold_2071: this->f_bonusCold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Bewitchment::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(28LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[114]), gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[115]), gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[116]), gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_495, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[117]), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(26LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[118]), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(25LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[119]), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(28LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_452, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        gd::GdVal lv_leastStacks = ([&]() { gd::GdVal _ca[] = {this->f_numDebuffs, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1391, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getLeastStacks_360, _ca, 3); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(26LL)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {lv_leastStacks, gd::GdVal::from_int(108LL), this->f_bonusPoison}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_dictAdd_1789, _ca, 3); })();
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(25LL)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {lv_leastStacks, gd::GdVal::from_int(109LL), this->f_bonusBlind}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_dictAdd_1789, _ca, 3); })();
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_array_index(gd_ctx, this->f_typesDict, gd::GdVal::from_int(28LL)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {lv_leastStacks, gd::GdVal::from_int(110LL), this->f_bonusCold}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_dictAdd_1789, _ca, 3); })();
        }
        {
            gd::GdVal _t360 = gd::gd_iter_seq(gd_ctx.arena, lv_leastStacks);
            gd::GdArr* _t361 = (_t360.kind == gd::GdVal::Kind::Arr) ? _t360.arr : nullptr;
            uint32_t _len__t362 = _t361 ? _t361->len : 0u;
            for (uint32_t _t362 = 0; _t362 < _len__t362; ++_t362) {
                gd::GdVal lv_debuffType = _t361->data[_t362];
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), lv_debuffType, gd::native_array_index(gd_ctx, lv_leastStacks, lv_debuffType), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
            }
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bewitchment::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[120])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_numDebuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[121])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[122])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusBlind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[123])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_bonusCold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[124])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Bewitchment(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Bewitchment>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,238u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bewitchment = {CLS_Gd__gd_core_items__Exclusive__Bewitchment, "Bewitchment", "res://gd_core_items/Exclusive/Bewitchment.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Bewitchment, &Gd__gd_core_items__Exclusive__Bewitchment::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Bewitchment::call_static_fn};

void Gd__gd_core_items__Exclusive__BrassKnuckles::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_extraAccuracy = gd::GdVal::null();
    this->f_battleRageSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BrassKnuckles::meta() const { return &META_Gd__gd_core_items__Exclusive__BrassKnuckles; }
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraAccuracy_2101: out = this->f_extraAccuracy; return true;
        case SYM_GEN_battleRageSpeed_2065: out = this->f_battleRageSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraAccuracy_2101: this->f_extraAccuracy = val; return true;
        case SYM_GEN_battleRageSpeed_2065: this->f_battleRageSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBattleRageStarted_2066: return true;
        case SYM_GEN_onBattleRageEnded_2067: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_2066: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_2067: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BrassKnuckles::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_179, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_extraAccuracy}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addAccuracy_177, _ca, 1); })();
        {
            gd::GdVal _t363 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t364 = (_t363.kind == gd::GdVal::Kind::Arr) ? _t363.arr : nullptr;
            uint32_t _len__t365 = _t364 ? _t364->len : 0u;
            for (uint32_t _t365 = 0; _t365 < _len__t365; ++_t365) {
                gd::GdVal lv_item = _t364->data[_t365];
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
                if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {this->f_extraAccuracy}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addAccuracy_177, _ca, 1); })();
                }
            }
        }
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[125])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[126]), gd::GdVal::from_str(&battle_string_literals[127])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[128]), gd::GdVal::from_str(&battle_string_literals[129])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageSpeed}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageSpeed}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceSpeed_274, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BrassKnuckles::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_extraAccuracy = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    this->f_battleRageSpeed = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BrassKnuckles(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__BrassKnuckles>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,252u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BrassKnuckles = {CLS_Gd__gd_core_items__Exclusive__BrassKnuckles, "BrassKnuckles", "res://gd_core_items/Exclusive/BrassKnuckles.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__BrassKnuckles, &Gd__gd_core_items__Exclusive__BrassKnuckles::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BrassKnuckles::call_static_fn};

void Gd__gd_core_items__Exclusive__Cheese::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cheese::meta() const { return &META_Gd__gd_core_items__Exclusive__Cheese; }
gd::GdVal Gd__gd_core_items__Exclusive__Cheese::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cheese::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cheese::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cheese::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cheese::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cheese::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cheese::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cheese::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cheese::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cheese(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Cheese>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,268u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cheese = {CLS_Gd__gd_core_items__Exclusive__Cheese, "Cheese", "res://gd_core_items/Exclusive/Cheese.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__Cheese, &Gd__gd_core_items__Exclusive__Cheese::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cheese::call_static_fn};

void Gd__gd_core_items__Exclusive__ChessMaster::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speed_v = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ChessMaster::meta() const { return &META_Gd__gd_core_items__Exclusive__ChessMaster; }
gd::GdVal Gd__gd_core_items__Exclusive__ChessMaster::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_firstKnightRound_2176: return gd::GdVal::from_int(1LL);
        case SYM_GEN_firstRookRound_2177: return gd::GdVal::from_int(5LL);
        case SYM_GEN_firstQueenRound_2178: return gd::GdVal::from_int(13LL);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_firstKnightRound_2176: out = gd::GdVal::from_int(1LL); return true;
        case SYM_GEN_firstRookRound_2177: out = gd::GdVal::from_int(5LL); return true;
        case SYM_GEN_firstQueenRound_2178: out = gd::GdVal::from_int(13LL); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ChessMaster::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speed_v_2179: out = this->f_speed_v; return true;
        case SYM_GEN_firstKnightRound_2176: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_firstRookRound_2177: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_firstQueenRound_2178: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speed_v_2179: this->f_speed_v = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChessMaster::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChessMaster::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chessboards = ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[130])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAllInInventoryOfType_803, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_chessboards, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_speed_v}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_chessboards, gd::GdVal::from_int(0LL)), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChessMaster::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChessMaster::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speed_v = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChessMaster(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ChessMaster>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,271u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChessMaster = {CLS_Gd__gd_core_items__Exclusive__ChessMaster, "ChessMaster", "res://gd_core_items/Exclusive/ChessMaster.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ChessMaster, &Gd__gd_core_items__Exclusive__ChessMaster::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ChessMaster::call_static_fn};

void Gd__gd_core_items__Exclusive__Daggerang::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Daggerang::meta() const { return &META_Gd__gd_core_items__Exclusive__Daggerang; }
gd::GdVal Gd__gd_core_items__Exclusive__Daggerang::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Daggerang::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Daggerang::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaReduction_2013: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Daggerang::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaReduction_2013: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Daggerang::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Daggerang::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Daggerang::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Daggerang::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Exclusive__Daggerang::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Daggerang(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Daggerang>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,302u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Daggerang = {CLS_Gd__gd_core_items__Exclusive__Daggerang, "Daggerang", "res://gd_core_items/Exclusive/Daggerang.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__Exclusive__Daggerang, &Gd__gd_core_items__Exclusive__Daggerang::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Daggerang::call_static_fn};

void Gd__gd_core_items__Exclusive__DragonscaleArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DragonscaleArmor::meta() const { return &META_Gd__gd_core_items__Exclusive__DragonscaleArmor; }
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBattleRageStarted_2066: return true;
        case SYM_GEN_onBattleRageEnded_2067: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_2066: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_2067: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[126]), gd::GdVal::from_str(&battle_string_literals[127])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[128]), gd::GdVal::from_str(&battle_string_literals[129])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DragonscaleArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__DragonscaleArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,318u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonscaleArmor = {CLS_Gd__gd_core_items__Exclusive__DragonscaleArmor, "DragonscaleArmor", "res://gd_core_items/Exclusive/DragonscaleArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DragonscaleArmor, &Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DragonscaleArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__Everburning::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numFlames = gd::GdVal::null();
    this->f_burningSwordDescr = gd::GdVal::null();
    this->f_burningBladeDescr = gd::GdVal::null();
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Everburning::meta() const { return &META_Gd__gd_core_items__Exclusive__Everburning; }
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Everburning::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Everburning::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numFlames_2248: out = this->f_numFlames; return true;
        case SYM_GEN_burningSwordDescr_2249: out = this->f_burningSwordDescr; return true;
        case SYM_GEN_burningBladeDescr_2250: out = this->f_burningBladeDescr; return true;
        case SYM_GEN_staminaReduction_2013: out = this->f_staminaReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Everburning::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numFlames_2248: this->f_numFlames = val; return true;
        case SYM_GEN_burningSwordDescr_2249: this->f_burningSwordDescr = val; return true;
        case SYM_GEN_burningBladeDescr_2250: this->f_burningBladeDescr = val; return true;
        case SYM_GEN_staminaReduction_2013: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Everburning::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Everburning::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Everburning::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numFlames = ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[132])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllInInventoryOfType_804, _ca, 1); })();
    {
        gd::GdVal _t366 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {this->f_burningSwordDescr}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAllInInventoryOfType_803, _ca, 1); })());
        gd::GdArr* _t367 = (_t366.kind == gd::GdVal::Kind::Arr) ? _t366.arr : nullptr;
        uint32_t _len__t368 = _t367 ? _t367->len : 0u;
        for (uint32_t _t368 = 0; _t368 < _len__t368; ++_t368) {
            gd::GdVal lv_item = _t367->data[_t368];
            (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
        }
    }
    {
        gd::GdVal _t369 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {this->f_burningBladeDescr}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAllInInventoryOfType_803, _ca, 1); })());
        gd::GdArr* _t370 = (_t369.kind == gd::GdVal::Kind::Arr) ? _t369.arr : nullptr;
        uint32_t _len__t371 = _t370 ? _t370->len : 0u;
        for (uint32_t _t371 = 0; _t371 < _len__t371; ++_t371) {
            gd::GdVal lv_item = _t370->data[_t371];
            (void)([&]() { gd::GdVal _ca[] = {this->f_staminaReduction}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_numFlames, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[133])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), this->f_numFlames)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[132])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_burningBladeDescr}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_burningSwordDescr}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Everburning::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_burningSwordDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[134])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_burningBladeDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[135])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_staminaReduction = gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Everburning(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Everburning>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,332u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Everburning = {CLS_Gd__gd_core_items__Exclusive__Everburning, "Everburning", "res://gd_core_items/Exclusive/Everburning.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Everburning, &Gd__gd_core_items__Exclusive__Everburning::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Everburning::call_static_fn};

void Gd__gd_core_items__Exclusive__FriendlyFire::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_maxHeatReached = gd::GdVal::from_int(0);
    this->f_manaNeeded = gd::GdVal::from_int(0);
    this->f_threshold1 = gd::GdVal::from_int(0);
    this->f_threshold2 = gd::GdVal::from_int(0);
    this->f_threshold3 = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FriendlyFire::meta() const { return &META_Gd__gd_core_items__Exclusive__FriendlyFire; }
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_maxHeatReached_2264: out = this->f_maxHeatReached; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_threshold1_2265: out = this->f_threshold1; return true;
        case SYM_GEN_threshold2_2266: out = this->f_threshold2; return true;
        case SYM_GEN_threshold3_2267: out = this->f_threshold3; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_maxHeatReached_2264: this->f_maxHeatReached = gd::gd_coerce_int(val); return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_threshold1_2265: this->f_threshold1 = gd::gd_coerce_int(val); return true;
        case SYM_GEN_threshold2_2266: this->f_threshold2 = gd::gd_coerce_int(val); return true;
        case SYM_GEN_threshold3_2267: this->f_threshold3 = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FriendlyFire::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(27LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(27LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_429, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_maxHeatReached = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[94]), gd::GdVal::from_str(&battle_string_literals[95])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_newMaxHeat = gd::gd_max(this->f_maxHeatReached, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_newMaxHeat, this->f_threshold3))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_maxHeatReached, this->f_threshold3)))) : gd::GdVal::from_bool(false)))) {
        this->f_maxHeatReached = gd::gd_coerce_int(lv_newMaxHeat);
        gd::GdVal lv_dam = gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675);
        gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv_dam, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_newMaxHeat, this->f_threshold2))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_maxHeatReached, this->f_threshold2)))) : gd::GdVal::from_bool(false)))) {
        this->f_maxHeatReached = gd::gd_coerce_int(lv_newMaxHeat);
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP7_269, nullptr, 0), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_newMaxHeat, this->f_threshold1))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_maxHeatReached, this->f_threshold1)))) : gd::GdVal::from_bool(false)))) {
        this->f_maxHeatReached = gd::gd_coerce_int(lv_newMaxHeat);
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FriendlyFire::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_threshold1 = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    this->f_threshold2 = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_268, nullptr, 0));
    this->f_threshold3 = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP8_270, nullptr, 0));
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FriendlyFire(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__FriendlyFire>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,347u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FriendlyFire = {CLS_Gd__gd_core_items__Exclusive__FriendlyFire, "FriendlyFire", "res://gd_core_items/Exclusive/FriendlyFire.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__FriendlyFire, &Gd__gd_core_items__Exclusive__FriendlyFire::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FriendlyFire::call_static_fn};

void Gd__gd_core_items__Exclusive__Hardwood::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hasCommonMeleeWeapon = gd::GdVal::from_bool(false);
    this->f_numCommons = gd::GdVal::from_int(0);
    this->f_commonDam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Hardwood::meta() const { return &META_Gd__gd_core_items__Exclusive__Hardwood; }
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Hardwood::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Hardwood::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasCommonMeleeWeapon_2294: out = this->f_hasCommonMeleeWeapon; return true;
        case SYM_GEN_numCommons_2295: out = this->f_numCommons; return true;
        case SYM_GEN_commonDam_2296: out = this->f_commonDam; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Hardwood::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasCommonMeleeWeapon_2294: this->f_hasCommonMeleeWeapon = val; return true;
        case SYM_GEN_numCommons_2295: this->f_numCommons = gd::gd_coerce_int(val); return true;
        case SYM_GEN_commonDam_2296: this->f_commonDam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Hardwood::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_isMeleeWeapon_1722: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onItemsCounted_2297: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Hardwood::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_isMeleeWeapon_1722: out = fn_isMeleeWeapon(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onItemsCounted_2297: out = fn_onItemsCounted(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Hardwood::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getRarity_236, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_isMeleeWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isMeleeWeapon_1722, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numCommons = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t372 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t373 = (_t372.kind == gd::GdVal::Kind::Arr) ? _t372.arr : nullptr;
        uint32_t _len__t374 = _t373 ? _t373->len : 0u;
        for (uint32_t _t374 = 0; _t374 < _len__t374; ++_t374) {
            gd::GdVal lv_item = _t373->data[_t374];
            this->f_numCommons = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numCommons, gd::GdVal::from_int(1LL)));
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isMeleeWeapon_1722, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_commonDam}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_306, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_numCommons, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), this->f_numCommons)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_onItemsCounted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hardwood::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_commonDam = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Hardwood(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Hardwood>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,361u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hardwood = {CLS_Gd__gd_core_items__Exclusive__Hardwood, "Hardwood", "res://gd_core_items/Exclusive/Hardwood.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Hardwood, &Gd__gd_core_items__Exclusive__Hardwood::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Hardwood::call_static_fn};

void Gd__gd_core_items__Exclusive__InnerPower::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_healAmpAcc = gd::GdVal::from_float(0.0);
    this->f_speedAcc = gd::GdVal::from_float(0.0);
    this->f_luck = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_healAmpPerLuck = gd::GdVal::null();
    this->f_speedPerEmpower = gd::GdVal::null();
    this->f_healAmpMax = gd::GdVal::null();
    this->f_speedMax = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__InnerPower::meta() const { return &META_Gd__gd_core_items__Exclusive__InnerPower; }
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__InnerPower::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__InnerPower::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healAmpAcc_2318: out = this->f_healAmpAcc; return true;
        case SYM_GEN_speedAcc_2319: out = this->f_speedAcc; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_healAmpPerLuck_2320: out = this->f_healAmpPerLuck; return true;
        case SYM_GEN_speedPerEmpower_2321: out = this->f_speedPerEmpower; return true;
        case SYM_GEN_healAmpMax_2322: out = this->f_healAmpMax; return true;
        case SYM_GEN_speedMax_2323: out = this->f_speedMax; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__InnerPower::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healAmpAcc_2318: this->f_healAmpAcc = gd::gd_coerce_float(val); return true;
        case SYM_GEN_speedAcc_2319: this->f_speedAcc = gd::gd_coerce_float(val); return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_healAmpPerLuck_2320: this->f_healAmpPerLuck = val; return true;
        case SYM_GEN_speedPerEmpower_2321: this->f_speedPerEmpower = val; return true;
        case SYM_GEN_healAmpMax_2322: this->f_healAmpMax = val; return true;
        case SYM_GEN_speedMax_2323: this->f_speedMax = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__InnerPower::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onLuckChanged_2064: return true;
        case SYM_GEN_onEmpowerChanged_2113: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__InnerPower::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckChanged_2064: out = fn_onLuckChanged(args, argc); return true;
        case SYM_GEN_onEmpowerChanged_2113: out = fn_onEmpowerChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__InnerPower::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canHealOrLifesteal_292, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_healAmpAcc = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_speedAcc = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[96]), gd::GdVal::from_str(&battle_string_literals[136])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[137]), gd::GdVal::from_str(&battle_string_literals[138])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_onLuckChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_before = gd::gd_min(this->f_healAmpAcc, this->f_healAmpMax);
    gd::GdVal lv_dif = gd::gd_mul(lv_amount, this->f_healAmpPerLuck);
    this->f_healAmpAcc = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_healAmpAcc, lv_dif));
    gd::GdVal lv_healAmpToGive = gd::gd_sub(gd::gd_min(this->f_healAmpAcc, this->f_healAmpMax), lv_before);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_healAmpToGive, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t375 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t376 = (_t375.kind == gd::GdVal::Kind::Arr) ? _t375.arr : nullptr;
            uint32_t _len__t377 = _t376 ? _t376->len : 0u;
            for (uint32_t _t377 = 0; _t377 < _len__t377; ++_t377) {
                gd::GdVal lv_item = _t376->data[_t377];
                (void)([&]() { gd::GdVal _ca[] = {lv_healAmpToGive}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeHealAmp_304, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn_onEmpowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_before = gd::gd_min(this->f_speedAcc, this->f_speedMax);
    gd::GdVal lv_dif = gd::gd_mul(lv_amount, this->f_speedPerEmpower);
    this->f_speedAcc = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_speedAcc, lv_dif));
    gd::GdVal lv_speedToGive = gd::gd_sub(gd::gd_min(this->f_speedAcc, this->f_speedMax), lv_before);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_speedToGive, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t378 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t379 = (_t378.kind == gd::GdVal::Kind::Arr) ? _t378.arr : nullptr;
            uint32_t _len__t380 = _t379 ? _t379->len : 0u;
            for (uint32_t _t380 = 0; _t380 < _len__t380; ++_t380) {
                gd::GdVal lv_item = _t379->data[_t380];
                (void)([&]() { gd::GdVal _ca[] = {lv_speedToGive}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InnerPower::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[139])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[140])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_healAmpPerLuck = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[141])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speedPerEmpower = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_healAmpMax = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[142])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speedMax = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[143])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__InnerPower(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__InnerPower>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,376u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__InnerPower = {CLS_Gd__gd_core_items__Exclusive__InnerPower, "InnerPower", "res://gd_core_items/Exclusive/InnerPower.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__InnerPower, &Gd__gd_core_items__Exclusive__InnerPower::get_static_prop_fn, &Gd__gd_core_items__Exclusive__InnerPower::call_static_fn};

void Gd__gd_core_items__Exclusive__LightningStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    this->f_manaCost = gd::GdVal::null();
    this->f_permDamBonus = gd::GdVal::null();
    this->f_chargeDamBase = gd::GdVal::null();
    this->f_chargeDamPerTile = gd::GdVal::null();
    this->f_numAttacks = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LightningStaff::meta() const { return &META_Gd__gd_core_items__Exclusive__LightningStaff; }
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_chargeCells_2055: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(3LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(4LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(4LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float())}));
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LightningStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_attackCounter_1001: out = this->f_attackCounter; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        case SYM_GEN_chargeDamBase_2347: out = this->f_chargeDamBase; return true;
        case SYM_GEN_chargeDamPerTile_2348: out = this->f_chargeDamPerTile; return true;
        case SYM_GEN_numAttacks_2349: out = this->f_numAttacks; return true;
        case SYM_GEN_chargeCells_2055: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_attackCounter_1001: this->f_attackCounter = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        case SYM_GEN_chargeDamBase_2347: this->f_chargeDamBase = val; return true;
        case SYM_GEN_chargeDamPerTile_2348: this->f_chargeDamPerTile = val; return true;
        case SYM_GEN_numAttacks_2349: this->f_numAttacks = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_canAffect_lightning_289: return true;
        case SYM_GEN_emitCharge_2058: return true;
        case SYM_GEN_onChargeEnteredCell_2059: return true;
        case SYM_GEN_chargedItemStatChange_2060: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_canAffect_lightning_289: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_emitCharge_2058: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_2059: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_2060: out = fn_chargedItemStatChange(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LightningStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
    }
    this->f_attackCounter = gd::gd_add(gd_ctx, this->f_attackCounter, gd::GdVal::from_int(1LL));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_attackCounter, this->f_numAttacks)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_2058, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[144]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        this->f_attackCounter = gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reactsToCharges_299, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[145])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), Gd__gd_core_items__Exclusive__LightningStaff::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells_2055), lv_speedFactor, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_320, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, this->f_chargeDamBase, this->f_chargeDamPerTile}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_326, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LightningStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaCost = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[120])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_permDamBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_chargeDamBase = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[146])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_chargeDamPerTile = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[147])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_numAttacks = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[148])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LightningStaff(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__LightningStaff>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,391u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LightningStaff = {CLS_Gd__gd_core_items__Exclusive__LightningStaff, "LightningStaff", "res://gd_core_items/Exclusive/LightningStaff.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__LightningStaff, &Gd__gd_core_items__Exclusive__LightningStaff::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LightningStaff::call_static_fn};

void Gd__gd_core_items__Exclusive__Markswoman::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_rangedBonusDam = gd::GdVal::null();
    this->f_rangedBonusSpeed = gd::GdVal::null();
    this->f_rangedBonusAcc = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Markswoman::meta() const { return &META_Gd__gd_core_items__Exclusive__Markswoman; }
gd::GdVal Gd__gd_core_items__Exclusive__Markswoman::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Markswoman::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Markswoman::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_rangedBonusDam_2394: out = this->f_rangedBonusDam; return true;
        case SYM_GEN_rangedBonusSpeed_2395: out = this->f_rangedBonusSpeed; return true;
        case SYM_GEN_rangedBonusAcc_2396: out = this->f_rangedBonusAcc; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Markswoman::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rangedBonusDam_2394: this->f_rangedBonusDam = val; return true;
        case SYM_GEN_rangedBonusSpeed_2395: this->f_rangedBonusSpeed = val; return true;
        case SYM_GEN_rangedBonusAcc_2396: this->f_rangedBonusAcc = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Markswoman::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Markswoman::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Markswoman::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Markswoman::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isRangedWeapon_1723, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Markswoman::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t381 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t382 = (_t381.kind == gd::GdVal::Kind::Arr) ? _t381.arr : nullptr;
        uint32_t _len__t383 = _t382 ? _t382->len : 0u;
        for (uint32_t _t383 = 0; _t383 < _len__t383; ++_t383) {
            gd::GdVal lv_item = _t382->data[_t383];
            (void)([&]() { gd::GdVal _ca[] = {this->f_rangedBonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_rangedBonusDam}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_306, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_rangedBonusAcc}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addAccuracy_177, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Markswoman::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_rangedBonusDam = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_rangedBonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_rangedBonusAcc = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[149])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Markswoman(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Markswoman>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,407u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Markswoman = {CLS_Gd__gd_core_items__Exclusive__Markswoman, "Markswoman", "res://gd_core_items/Exclusive/Markswoman.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Markswoman, &Gd__gd_core_items__Exclusive__Markswoman::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Markswoman::call_static_fn};

void Gd__gd_core_items__Exclusive__OilLamp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_bonusDam = gd::GdVal::null();
    this->f_bonusAcc = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__OilLamp::meta() const { return &META_Gd__gd_core_items__Exclusive__OilLamp; }
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__OilLamp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__OilLamp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusDam_1875: out = this->f_bonusDam; return true;
        case SYM_GEN_bonusAcc_2417: out = this->f_bonusAcc; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__OilLamp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDam_1875: this->f_bonusDam = val; return true;
        case SYM_GEN_bonusAcc_2417: this->f_bonusAcc = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__OilLamp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__OilLamp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__OilLamp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[133])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t384 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t385 = (_t384.kind == gd::GdVal::Kind::Arr) ? _t384.arr : nullptr;
        uint32_t _len__t386 = _t385 ? _t385->len : 0u;
        for (uint32_t _t386 = 0; _t386 < _len__t386; ++_t386) {
            gd::GdVal lv_item = _t385->data[_t386];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusAcc}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addAccuracy_177, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OilLamp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_bonusAcc = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[150])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__OilLamp(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__OilLamp>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,423u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__OilLamp = {CLS_Gd__gd_core_items__Exclusive__OilLamp, "OilLamp", "res://gd_core_items/Exclusive/OilLamp.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__OilLamp, &Gd__gd_core_items__Exclusive__OilLamp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__OilLamp::call_static_fn};

void Gd__gd_core_items__Exclusive__Pop::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_previousSpeedBonus = gd::GdVal::from_float(0.0);
    this->f_speedPerMana = gd::GdVal::null();
    this->f_maxSpeedBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Pop::meta() const { return &META_Gd__gd_core_items__Exclusive__Pop; }
gd::GdVal Gd__gd_core_items__Exclusive__Pop::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Pop::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Pop::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_previousSpeedBonus_2432: out = this->f_previousSpeedBonus; return true;
        case SYM_GEN_speedPerMana_2433: out = this->f_speedPerMana; return true;
        case SYM_GEN_maxSpeedBonus_2097: out = this->f_maxSpeedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Pop::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_previousSpeedBonus_2432: this->f_previousSpeedBonus = gd::gd_coerce_float(val); return true;
        case SYM_GEN_speedPerMana_2433: this->f_speedPerMana = val; return true;
        case SYM_GEN_maxSpeedBonus_2097: this->f_maxSpeedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Pop::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Pop::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Pop::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_previousSpeedBonus = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[101]), gd::GdVal::from_str(&battle_string_literals[102])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_speed = gd::gd_min(this->f_maxSpeedBonus, gd::gd_mul(this->f_speedPerMana, gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::gd_sub(lv_speed, this->f_previousSpeedBonus), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_speed, this->f_previousSpeedBonus)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
        this->f_previousSpeedBonus = gd::gd_coerce_float(lv_speed);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pop::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedPerMana = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxSpeedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[151])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Pop(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Pop>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,438u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Pop = {CLS_Gd__gd_core_items__Exclusive__Pop, "Pop", "res://gd_core_items/Exclusive/Pop.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Pop, &Gd__gd_core_items__Exclusive__Pop::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Pop::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_vampirism = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
    this->f_dambonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        case SYM_GEN_blind_1911: out = this->f_blind; return true;
        case SYM_GEN_dambonus_2452: out = this->f_dambonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        case SYM_GEN_blind_1911: this->f_blind = val; return true;
        case SYM_GEN_dambonus_2452: this->f_dambonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    {
        gd::GdVal _t387 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t388 = (_t387.kind == gd::GdVal::Kind::Arr) ? _t387.arr : nullptr;
        uint32_t _len__t389 = _t388 ? _t388->len : 0u;
        for (uint32_t _t389 = 0; _t389 < _len__t389; ++_t389) {
            gd::GdVal lv_item = _t388->data[_t389];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_dambonus}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[152])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[123])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_dambonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[153])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowGoobertEngineer>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,455u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer = {CLS_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer, "RainbowGoobertEngineer", "res://gd_core_items/Exclusive/RainbowGoobertEngineer.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer, &Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowGoobertEngineer::call_static_fn};

void Gd__gd_core_items__Exclusive__SapphireEgg::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__DragonEgg::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SapphireEgg::meta() const { return &META_Gd__gd_core_items__Exclusive__SapphireEgg; }
gd::GdVal Gd__gd_core_items__Exclusive__SapphireEgg::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__DragonEgg::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__DragonEgg::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__DragonEgg::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__DragonEgg::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__DragonEgg::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SapphireEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__DragonEgg::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireEgg::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_144, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireEgg::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__DragonEgg::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SapphireEgg(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SapphireEgg>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,471u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SapphireEgg = {CLS_Gd__gd_core_items__Exclusive__SapphireEgg, "SapphireEgg", "res://gd_core_items/Exclusive/SapphireEgg.gd", &META_Gd__gd_core_items__DragonEgg, true, _alloc_Gd__gd_core_items__Exclusive__SapphireEgg, &Gd__gd_core_items__Exclusive__SapphireEgg::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SapphireEgg::call_static_fn};

void Gd__gd_core_items__Exclusive__SliceofBread::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_staminaThreshold = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SliceofBread::meta() const { return &META_Gd__gd_core_items__Exclusive__SliceofBread; }
gd::GdVal Gd__gd_core_items__Exclusive__SliceofBread::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SliceofBread::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaThreshold_2075: out = this->f_staminaThreshold; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaThreshold_2075: this->f_staminaThreshold = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SliceofBread::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SliceofBread::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentStamina_1262, nullptr, 0), this->f_staminaThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SliceofBread::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[154])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[131])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SliceofBread(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SliceofBread>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,487u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SliceofBread = {CLS_Gd__gd_core_items__Exclusive__SliceofBread, "SliceofBread", "res://gd_core_items/Exclusive/SliceofBread.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__SliceofBread, &Gd__gd_core_items__Exclusive__SliceofBread::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SliceofBread::call_static_fn};

void Gd__gd_core_items__Exclusive__SpellScrollIce::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_coldInflicted = gd::GdVal::from_int(0);
    this->f_cold = gd::GdVal::null();
    this->f_maxCold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpellScrollIce::meta() const { return &META_Gd__gd_core_items__Exclusive__SpellScrollIce; }
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_coldInflicted_2281: out = this->f_coldInflicted; return true;
        case SYM_GEN_cold_2045: out = this->f_cold; return true;
        case SYM_GEN_maxCold_2527: out = this->f_maxCold; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_coldInflicted_2281: this->f_coldInflicted = gd::gd_coerce_int(val); return true;
        case SYM_GEN_cold_2045: this->f_cold = val; return true;
        case SYM_GEN_maxCold_2527: this->f_maxCold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCharacterAttacked_1945: return true;
        case SYM_GEN_onShieldOrArmorActivated_2317: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCharacterAttacked_1945: out = fn_onCharacterAttacked(args, argc); return true;
        case SYM_GEN_onShieldOrArmorActivated_2317: out = fn_onShieldOrArmorActivated(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollIce::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(5LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[155]), gd::GdVal::from_str(&battle_string_literals[156])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    {
        gd::GdVal _t390 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t391 = (_t390.kind == gd::GdVal::Kind::Arr) ? _t390.arr : nullptr;
        uint32_t _len__t392 = _t391 ? _t391->len : 0u;
        for (uint32_t _t392 = 0; _t392 < _len__t392; ++_t392) {
            gd::GdVal lv_item = _t391->data[_t392];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_str(&battle_string_literals[157])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    this->f_coldInflicted = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn_onCharacterAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_willBeLethal_1534, _ca, 1); })())) {
            gd::GdVal lv_opponentCold = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getCold_1254, nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_opponentCold, gd::GdVal::from_int(0LL))))) {
                this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
                (void)([&]() { gd::GdVal _ca[] = {lv_opponentCold, gd::GdVal::from_obj(this), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_loseCold_1257, _ca, 3); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), lv_opponentCold)), gd::GdVal::from_bool(true), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
                (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn_onShieldOrArmorActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_coldInflicted, this->f_maxCold))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        this->f_coldInflicted = gd::gd_coerce_int(gd::gd_min(this->f_cold, gd::gd_sub(this->f_maxCold, this->f_coldInflicted)));
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollIce::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[124])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_maxCold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[151])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpellScrollIce(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__SpellScrollIce>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,503u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollIce = {CLS_Gd__gd_core_items__Exclusive__SpellScrollIce, "SpellScrollIce", "res://gd_core_items/Exclusive/SpellScrollIce.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpellScrollIce, &Gd__gd_core_items__Exclusive__SpellScrollIce::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpellScrollIce::call_static_fn};

void Gd__gd_core_items__Exclusive__StoneBadge::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_goldValue = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StoneBadge::meta() const { return &META_Gd__gd_core_items__Exclusive__StoneBadge; }
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StoneBadge::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_goldValue_2550: out = this->f_goldValue; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_goldValue_2550: this->f_goldValue = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onAddedToStorageBox_681: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_getItemsMaxCost_2551: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onAddedToStorageBox_681: out = fn_onAddedToStorageBox(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getItemsMaxCost_2551: out = fn_getItemsMaxCost(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneBadge::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_onAddedToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_getItemsMaxCost(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxCost = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_goldValue}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsMaxCost_2551, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(4LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_goldValue = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[158])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneBadge(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__StoneBadge>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,520u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneBadge = {CLS_Gd__gd_core_items__Exclusive__StoneBadge, "StoneBadge", "res://gd_core_items/Exclusive/StoneBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__StoneBadge, &Gd__gd_core_items__Exclusive__StoneBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StoneBadge::call_static_fn};

void Gd__gd_core_items__Exclusive__ThunderDrake::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_active = gd::GdVal::from_bool(false);
    this->f_curHitCount = gd::GdVal::from_int(0);
    this->f_lightningMultiplicity = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_numHits = gd::GdVal::null();
    this->f_buffSpeed = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_buffParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ThunderDrake::meta() const { return &META_Gd__gd_core_items__Exclusive__ThunderDrake; }
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_active_1653: out = this->f_active; return true;
        case SYM_GEN_curHitCount_2586: out = this->f_curHitCount; return true;
        case SYM_GEN_lightningMultiplicity_2587: out = this->f_lightningMultiplicity; return true;
        case SYM_GEN_numHits_1004: out = this->f_numHits; return true;
        case SYM_GEN_buffSpeed_2588: out = this->f_buffSpeed; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_buffParticles_1884: out = this->f_buffParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_1653: this->f_active = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_curHitCount_2586: this->f_curHitCount = gd::gd_coerce_int(val); return true;
        case SYM_GEN_lightningMultiplicity_2587: this->f_lightningMultiplicity = val; return true;
        case SYM_GEN_numHits_1004: this->f_numHits = val; return true;
        case SYM_GEN_buffSpeed_2588: this->f_buffSpeed = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_buffParticles_1884: this->f_buffParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_lightning_289: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_zapItem_2589: return true;
        case SYM_GEN_onBuffEnded_2590: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_lightning_289: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_zapItem_2589: out = fn_zapItem(args, argc); return true;
        case SYM_GEN_onBuffEnded_2590: out = fn_onBuffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ThunderDrake::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reactsToCharges_299, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    this->f_curHitCount = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_lightningMultiplicity = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countItemsInAffectedCells_cached_424, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        this->f_curHitCount = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_curHitCount, gd::GdVal::from_int(1LL)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_curHitCount, this->f_numHits)))) {
            if (gd::gd_truth(this->f_active)) {
                {
                    gd::GdVal _t393 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
                    gd::GdArr* _t394 = (_t393.kind == gd::GdVal::Kind::Arr) ? _t393.arr : nullptr;
                    uint32_t _len__t395 = _t394 ? _t394->len : 0u;
                    for (uint32_t _t395 = 0; _t395 < _len__t395; ++_t395) {
                        gd::GdVal lv_item = _t394->data[_t395];
                        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_chargeLeft_325, _ca, 1); })();
                        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_zapItem_2589, _ca, 1); })();
                    }
                }
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
                {
                    gd::GdVal _t396 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
                    gd::GdArr* _t397 = (_t396.kind == gd::GdVal::Kind::Arr) ? _t396.arr : nullptr;
                    uint32_t _len__t398 = _t397 ? _t397->len : 0u;
                    for (uint32_t _t398 = 0; _t398 < _len__t398; ++_t398) {
                        gd::GdVal lv_item = _t397->data[_t398];
                        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_buffSpeed, gd::native_array_index(gd_ctx, this->f_lightningMultiplicity, lv_item))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
                        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_zapItem_2589, _ca, 1); })();
                    }
                }
            }
            (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[145])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
            this->f_curHitCount = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_zapItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_chargeReceived_324, _ca, 1); })();
    if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_hasOnChargeReceivedEffect_65))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(4.0), gd::GdVal::from_float(4.02)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
        gd::GdVal lv_targetPos = gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getGlobalCenter_784, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onBuffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    {
        gd::GdVal _t399 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
        gd::GdArr* _t400 = (_t399.kind == gd::GdVal::Kind::Arr) ? _t399.arr : nullptr;
        uint32_t _len__t401 = _t400 ? _t400->len : 0u;
        for (uint32_t _t401 = 0; _t401 < _len__t401; ++_t401) {
            gd::GdVal lv_item = _t400->data[_t401];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_buffSpeed, gd::native_array_index(gd_ctx, this->f_lightningMultiplicity, lv_item))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_chargeLeft_325, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chargeActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_active = gd::gd_coerce_bool(lv_chargeActive);
    if (gd::gd_truth(lv_chargeActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t402 = lv_forDirection;
        if (gd::native_scalar_eq(_t402, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t402, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t402, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t402, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThunderDrake::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_numHits = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[159])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[99])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[111]), gd::GdVal::from_str(&battle_string_literals[160]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ThunderDrake(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ThunderDrake>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,535u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThunderDrake = {CLS_Gd__gd_core_items__Exclusive__ThunderDrake, "ThunderDrake", "res://gd_core_items/Exclusive/ThunderDrake.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__ThunderDrake, &Gd__gd_core_items__Exclusive__ThunderDrake::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ThunderDrake::call_static_fn};

void Gd__gd_core_items__Exclusive__Wand::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_buffs = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_buffsToUse = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Wand::meta() const { return &META_Gd__gd_core_items__Exclusive__Wand; }
gd::GdVal Gd__gd_core_items__Exclusive__Wand::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Wand::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Wand::get_prop(gd::SymId prop, gd::GdVal& out) const {
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
bool Gd__gd_core_items__Exclusive__Wand::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
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
bool Gd__gd_core_items__Exclusive__Wand::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Wand::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Wand::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Wand::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::null(), this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLeastBuffs_366, _ca, 4); })();
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
gd::GdVal Gd__gd_core_items__Exclusive__Wand::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffs = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(105LL), gd::GdVal::from_int(101LL), gd::GdVal::from_int(102LL)}));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[120])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[161])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[162])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[140])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffsToUse = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[163])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Wand(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Wand>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,553u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Wand = {CLS_Gd__gd_core_items__Exclusive__Wand, "Wand", "res://gd_core_items/Exclusive/Wand.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Wand, &Gd__gd_core_items__Exclusive__Wand::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Wand::call_static_fn};

void Gd__gd_core_items__FlyAgaric::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__FlyAgaric::meta() const { return &META_Gd__gd_core_items__FlyAgaric; }
gd::GdVal Gd__gd_core_items__FlyAgaric::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__FlyAgaric::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__FlyAgaric::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__FlyAgaric::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__FlyAgaric::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__FlyAgaric::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__FlyAgaric::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__FlyAgaric::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FlyAgaric::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__FlyAgaric(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__FlyAgaric>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,569u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__FlyAgaric = {CLS_Gd__gd_core_items__FlyAgaric, "FlyAgaric", "res://gd_core_items/FlyAgaric.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__FlyAgaric, &Gd__gd_core_items__FlyAgaric::get_static_prop_fn, &Gd__gd_core_items__FlyAgaric::call_static_fn};

void Gd__gd_core_items__HeroicPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__HeroicPotion::meta() const { return &META_Gd__gd_core_items__HeroicPotion; }
gd::GdVal Gd__gd_core_items__HeroicPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HeroicPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HeroicPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__HeroicPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HeroicPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_checkStamina_1893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__HeroicPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_checkStamina_1893: out = fn_checkStamina(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HeroicPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[164]), gd::GdVal::from_str(&battle_string_literals[165])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn_checkStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentStamina_1262, nullptr, 0), lv_amount)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HeroicPotion(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__HeroicPotion>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,592u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__HeroicPotion = {CLS_Gd__gd_core_items__HeroicPotion, "HeroicPotion", "res://gd_core_items/HeroicPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__HeroicPotion, &Gd__gd_core_items__HeroicPotion::get_static_prop_fn, &Gd__gd_core_items__HeroicPotion::call_static_fn};

void Gd__gd_core_items__ManaOrb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_stackTypes = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_bonusBuffs = gd::GdVal::from_int(0);
    this->f_mana = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::from_int(0);
    this->f_buffs = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__ManaOrb::meta() const { return &META_Gd__gd_core_items__ManaOrb; }
gd::GdVal Gd__gd_core_items__ManaOrb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ManaOrb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ManaOrb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: out = this->f_stackTypes; return true;
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_bonusBuffs_1927: out = this->f_bonusBuffs; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__ManaOrb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: this->f_stackTypes = val; return true;
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_bonusBuffs_1927: this->f_bonusBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ManaOrb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_addBonusRandomBuffs_1930: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__ManaOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_addBonusRandomBuffs_1930: out = fn_addBonusRandomBuffs(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ManaOrb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__cells = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_414, nullptr, 0);
        gd::GdVal lv__hit = gd::GdVal::from_str(&battle_string_literals[0]);
        {
            gd::GdVal _t403 = gd::gd_iter_seq(gd_ctx.arena, lv__cells);
            gd::GdArr* _t404 = (_t403.kind == gd::GdVal::Kind::Arr) ? _t403.arr : nullptr;
            uint32_t _len__t405 = _t404 ? _t404->len : 0u;
            for (uint32_t _t405 = 0; _t405 < _len__t405; ++_t405) {
                gd::GdVal lv__c = _t404->data[_t405];
                gd::GdVal lv__it = ([&]() { gd::GdVal _ca[] = {lv__c}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_400, nullptr, 0), SYM_GEN_getItemInCell_1607, _ca, 1); })();
                lv__hit = gd::gd_add(gd_ctx, lv__hit, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[166]), ([&]() { gd::GdVal _ca[] = {lv__c}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[167])), (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__it, gd::GdVal::null()))) ? (gd::GdVal::from_str(&battle_string_literals[55])) : (gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__it, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[14])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv__it, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(&battle_string_literals[168])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv__it, SYM_GEN_placed_6))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())))), gd::GdVal::from_str(&battle_string_literals[169])));
            }
        }
        gd::GdVal lv__aff = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
        gd::GdVal lv__aff_names = gd::GdVal::from_str(&battle_string_literals[0]);
        {
            gd::GdVal _t406 = gd::gd_iter_seq(gd_ctx.arena, lv__aff);
            gd::GdArr* _t407 = (_t406.kind == gd::GdVal::Kind::Arr) ? _t406.arr : nullptr;
            uint32_t _len__t408 = _t407 ? _t407->len : 0u;
            for (uint32_t _t408 = 0; _t408 < _len__t408; ++_t408) {
                gd::GdVal lv__a = _t407->data[_t408];
                lv__aff_names = gd::gd_add(gd_ctx, lv__aff_names, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[170])));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[171]), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[14])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), ([&]() { gd::GdVal _ca[] = {lv__cells}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, lv__hit, gd::GdVal::from_str(&battle_string_literals[172])), lv__aff_names)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    this->f_bonusBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    {
        gd::GdVal _t409 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t410 = (_t409.kind == gd::GdVal::Kind::Arr) ? _t409.arr : nullptr;
        uint32_t _len__t411 = _t410 ? _t410->len : 0u;
        for (uint32_t _t411 = 0; _t411 < _len__t411; ++_t411) {
            gd::GdVal lv_item = _t410->data[_t411];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_str(&battle_string_literals[100])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[101]), gd::GdVal::from_str(&battle_string_literals[102])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_buffs, this->f_bonusBuffs), lv_event, this->f_stackTypes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 3); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_addBonusRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_bonusBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusBuffs, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__activated = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__activated = gd::gd_coerce_bool(lv__activated);
    this->f_activated = gd::gd_coerce_bool(lv__activated);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_manaNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    this->f_buffs = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    this->f_stackTypes = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL)}; return gd::native_inline_call(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ManaOrb(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__ManaOrb>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,610u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__ManaOrb = {CLS_Gd__gd_core_items__ManaOrb, "ManaOrb", "res://gd_core_items/ManaOrb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__ManaOrb, &Gd__gd_core_items__ManaOrb::get_static_prop_fn, &Gd__gd_core_items__ManaOrb::call_static_fn};

void Gd__gd_core_items__ProtectivePurse::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__ProtectivePurse::meta() const { return &META_Gd__gd_core_items__ProtectivePurse; }
gd::GdVal Gd__gd_core_items__ProtectivePurse::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ProtectivePurse::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ProtectivePurse::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__ProtectivePurse::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ProtectivePurse::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__ProtectivePurse::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ProtectivePurse::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ProtectivePurse::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_totalBlock = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        lv_totalBlock = gd::gd_add(gd_ctx, lv_totalBlock, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[173])}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[98])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })(), SYM_GEN_getP_188, _ca, 1); })());
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_totalBlock}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ProtectivePurse::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ProtectivePurse(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__ProtectivePurse>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,630u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__ProtectivePurse = {CLS_Gd__gd_core_items__ProtectivePurse, "ProtectivePurse", "res://gd_core_items/ProtectivePurse.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__ProtectivePurse, &Gd__gd_core_items__ProtectivePurse::get_static_prop_fn, &Gd__gd_core_items__ProtectivePurse::call_static_fn};

void Gd__gd_core_items__StrongDemonicFlask::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
    this->f_healingReductionTimer = gd::GdVal::null();
    this->f_healingDebuff = gd::GdVal::null();
    this->f_damPerDebuff = gd::GdVal::null();
    this->f_playerHealthThreshold = gd::GdVal::null();
    this->f_opponentHealthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__StrongDemonicFlask::meta() const { return &META_Gd__gd_core_items__StrongDemonicFlask; }
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StrongDemonicFlask::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StrongDemonicFlask::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healingReductionTimer_1987: out = this->f_healingReductionTimer; return true;
        case SYM_GEN_healingDebuff_1988: out = this->f_healingDebuff; return true;
        case SYM_GEN_damPerDebuff_1827: out = this->f_damPerDebuff; return true;
        case SYM_GEN_playerHealthThreshold_1989: out = this->f_playerHealthThreshold; return true;
        case SYM_GEN_opponentHealthThreshold_1990: out = this->f_opponentHealthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__StrongDemonicFlask::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healingReductionTimer_1987: this->f_healingReductionTimer = val; return true;
        case SYM_GEN_healingDebuff_1988: this->f_healingDebuff = val; return true;
        case SYM_GEN_damPerDebuff_1827: this->f_damPerDebuff = val; return true;
        case SYM_GEN_playerHealthThreshold_1989: this->f_playerHealthThreshold = val; return true;
        case SYM_GEN_opponentHealthThreshold_1990: this->f_opponentHealthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StrongDemonicFlask::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canDamage_89: return true;
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPlayerDamaged_1991: return true;
        case SYM_GEN_onOpponentDamaged_1992: return true;
        case SYM_GEN_drinkStrongDemonicFlask_1993: return true;
        case SYM_GEN_healingReductionTimeout_1994: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__StrongDemonicFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canDamage_89: out = fn_canDamage(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPlayerDamaged_1991: out = fn_onPlayerDamaged(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1992: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_drinkStrongDemonicFlask_1993: out = fn_drinkStrongDemonicFlask(args, argc); return true;
        case SYM_GEN_healingReductionTimeout_1994: out = fn_healingReductionTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StrongDemonicFlask::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_canDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {this->f_healingDebuff}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1183, _ca, 1); })();
    gd::GdVal lv_dam = gd::gd_mul(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getDebuffStacks_1216, nullptr, 0), this->f_damPerDebuff);
    lv_dam = gd::gd_ceil(lv_dam);
    (void)([&]() { gd::GdVal _ca[] = {lv_dam, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[145])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_healingReductionTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[174]), gd::GdVal::from_str(&battle_string_literals[175])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[174]), gd::GdVal::from_str(&battle_string_literals[176])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onPlayerDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0), this->f_playerHealthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drinkStrongDemonicFlask_1993, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0), this->f_opponentHealthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drinkStrongDemonicFlask_1993, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_drinkStrongDemonicFlask(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__aff = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    gd::GdVal lv__aff_names = gd::GdVal::from_str(&battle_string_literals[0]);
    {
        gd::GdVal _t412 = gd::gd_iter_seq(gd_ctx.arena, lv__aff);
        gd::GdArr* _t413 = (_t412.kind == gd::GdVal::Kind::Arr) ? _t412.arr : nullptr;
        uint32_t _len__t414 = _t413 ? _t413->len : 0u;
        for (uint32_t _t414 = 0; _t414 < _len__t414; ++_t414) {
            gd::GdVal lv__a = _t413->data[_t414];
            lv__aff_names = gd::gd_add(gd_ctx, lv__aff_names, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[170])));
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[171]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1673))), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[177]), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv__aff, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), lv__aff_names}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drink_1847, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_triggerPotion_1850, _ca, 1); })();
    gd::GdVal lv_affected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_triggerPotion_1850, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_healingReductionTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_healingDebuff}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_healingReductionTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongDemonicFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healingReductionTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[178]), gd::GdVal::from_str(&battle_string_literals[179]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_healingDebuff = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_damPerDebuff = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_playerHealthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[180])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_opponentHealthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[181])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongDemonicFlask(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__StrongDemonicFlask>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,653u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__StrongDemonicFlask = {CLS_Gd__gd_core_items__StrongDemonicFlask, "StrongDemonicFlask", "res://gd_core_items/StrongDemonicFlask.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__StrongDemonicFlask, &Gd__gd_core_items__StrongDemonicFlask::get_static_prop_fn, &Gd__gd_core_items__StrongDemonicFlask::call_static_fn};

void Gd__gd_core_items__WoodenSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__WoodenSword::meta() const { return &META_Gd__gd_core_items__WoodenSword; }
gd::GdVal Gd__gd_core_items__WoodenSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__WoodenSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__WoodenSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__WoodenSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__WoodenSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__WoodenSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__WoodenSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__WoodenSword::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__WoodenSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__WoodenSword(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__WoodenSword>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,672u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__WoodenSword = {CLS_Gd__gd_core_items__WoodenSword, "WoodenSword", "res://gd_core_items/WoodenSword.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__WoodenSword, &Gd__gd_core_items__WoodenSword::get_static_prop_fn, &Gd__gd_core_items__WoodenSword::call_static_fn};

namespace gd {static thread_local uint64_t private_snapshot_counts[4]{};void native_private_snapshot_hit(unsigned i){if(i<4)++private_snapshot_counts[i];}}
extern "C" uint64_t gd_diag_native_private_snapshot_stat(unsigned i){return i<4?gd::private_snapshot_counts[i]:0;}
