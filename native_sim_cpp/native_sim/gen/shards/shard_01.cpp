#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Item.hpp"
#include "../hdrs/Gd__gd_core__Weapon.hpp"
#include "../hdrs/Gd__gd_core__CoreBuff__INNER__TemporaryStacks.hpp"
#include "../hdrs/Gd__gd_core__CoreBuff.hpp"
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

static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Owner[] = {{"Shop", 0LL}, {"PlayerInventory", 1LL}, {"PlayerStorageBox", 2LL}, {"Opponent", 3LL}, {"Title", 4LL}, {"RecipeBook", 5LL}, {"Tooltip", 6LL}, {"Socket", 7LL}, {"ItemLibrary", 8LL}, {"InfoPanelIcon", 9LL}, {"BuildViewer", 10LL}, {"BuildViewerIcon", 11LL}, {"GridStorage", 12LL}, {"Undefined", 13LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Owner = {"Owner", _ekv_Gd__gd_core__Item_Owner, 14u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Type[] = {{"Bag", 0LL}, {"Consumable", 1LL}, {"Food", 2LL}, {"Pet", 3LL}, {"Weapon", 4LL}, {"Shield", 5LL}, {"Armor", 6LL}, {"Gloves", 7LL}, {"Shoes", 8LL}, {"Helmet", 9LL}, {"Accessory", 10LL}, {"Potion", 11LL}, {"Card", 12LL}, {"Gem", 13LL}, {"Scroll", 14LL}, {"Book", 15LL}, {"Skill", 16LL}, {"ChessPiece", 17LL}, {"Spell", 18LL}, {"Melee", 19LL}, {"Ranged", 20LL}, {"Effect", 21LL}, {"Holy", 22LL}, {"Magic", 23LL}, {"Vampiric", 24LL}, {"Dark", 25LL}, {"Nature", 26LL}, {"Fire", 27LL}, {"Ice", 28LL}, {"Musical", 29LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Type = {"Type", _ekv_Gd__gd_core__Item_Type, 30u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Priority[] = {{"Lowest", -10000LL}, {"Low", -1000LL}, {"Normal", 0LL}, {"High", 1000LL}, {"Highest", 10000LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Priority = {"Priority", _ekv_Gd__gd_core__Item_Priority, 5u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_CraftingPriority[] = {{"Gem", 3LL}, {"Mixed", 2LL}, {"NonGem", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_CraftingPriority = {"CraftingPriority", _ekv_Gd__gd_core__Item_CraftingPriority, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Tag[] = {{"None", 0LL}, {"Lifesteal", 1LL}, {"Stone", 2LL}, {"Scroll", 8LL}, {"Dragon", 16LL}, {"Staff", 32LL}, {"BattleRage", 64LL}, {"Singular", 128LL}, {"Transient", 256LL}, {"Bow", 512LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Tag = {"Tag", _ekv_Gd__gd_core__Item_Tag, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Stack[] = {{"None", 0LL}, {"Block", 1LL}, {"Lucky", 2LL}, {"Regeneration", 4LL}, {"Vampirism", 8LL}, {"Spikes", 16LL}, {"Mana", 32LL}, {"Empower", 64LL}, {"Heat", 128LL}, {"Poison", 256LL}, {"Blind", 512LL}, {"Cold", 1024LL}, {"Buff", 254LL}, {"Debuff", 1792LL}, {"BuffNoLuck", 252LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Stack = {"Stack", _ekv_Gd__gd_core__Item_Stack, 15u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Mat[] = {{"Default", 0LL}, {"Wood", 1LL}, {"Metal", 2LL}, {"Leather", 3LL}, {"Glass", 4LL}, {"Stone", 5LL}, {"Squishy", 6LL}, {"Jewelry", 7LL}, {"Sand", 8LL}, {"Paper", 9LL}, {"Slime", 10LL}, {"Ice", 11LL}, {"Fire", 12LL}, {"Dragon", 13LL}, {"Bird", 14LL}, {"Leaf", 15LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Mat = {"Mat", _ekv_Gd__gd_core__Item_Mat, 16u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Physics[] = {{"Default", 0LL}, {"Light", 1LL}, {"Slime", 2LL}, {"Dense", 3LL}, {"VeryDense", 4LL}, {"Floaty", 5LL}, {"Sand", 6LL}, {"Plush", 7LL}, {"BouncyDense", 8LL}, {"Ice", 9LL}, {"Ghost", 10LL}, {"BlackHole", 11LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Physics = {"Physics", _ekv_Gd__gd_core__Item_Physics, 12u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Rarity[] = {{"Common", 0LL}, {"Rare", 1LL}, {"Epic", 2LL}, {"Legendary", 3LL}, {"Godly", 4LL}, {"Unique", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Rarity = {"Rarity", _ekv_Gd__gd_core__Item_Rarity, 6u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_FaceDirection[] = {{"UP", 0LL}, {"RIGHT", 1LL}, {"DOWN", 2LL}, {"LEFT", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_FaceDirection = {"FaceDirection", _ekv_Gd__gd_core__Item_FaceDirection, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_StatModified[] = {{"No", 0LL}, {"Positive", 1LL}, {"Negative", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_StatModified = {"StatModified", _ekv_Gd__gd_core__Item_StatModified, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_DropResult[] = {{"AddedToInventory", 0LL}, {"Hotswap", 1LL}, {"InventoryCollision", 2LL}, {"OutsideInventory", 3LL}, {"AddedToStorageBox", 4LL}, {"Sold", 5LL}, {"Socketed", 6LL}, {"SocketHotswap", 7LL}, {"Failed", 8LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_DropResult = {"DropResult", _ekv_Gd__gd_core__Item_DropResult, 9u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_PickupType[] = {{"Grabbed", 0LL}, {"Hotswap", 1LL}, {"MultiSelect", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_PickupType = {"PickupType", _ekv_Gd__gd_core__Item_PickupType, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Affected[] = {{"Primary", 0LL}, {"Secondary", 2LL}, {"Tertiary", 4LL}, {"Lightning", 7LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Affected = {"Affected", _ekv_Gd__gd_core__Item_Affected, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Tiles[] = {{"Extension", 2LL}, {"Collision", 3LL}, {"Affected", 4LL}, {"AffectedDynamic", 5LL}, {"AffectedSecondary", 6LL}, {"AffectedSecondaryDynamic", 7LL}, {"AffectedExtension", 8LL}, {"AffectedTertiary", 10LL}, {"AffectedLightning", 11LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Tiles = {"Tiles", _ekv_Gd__gd_core__Item_Tiles, 9u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_ActivationAni[] = {{"Scale", 0LL}, {"Jump", 1LL}, {"SquishyJump", 2LL}, {"VerySquishyJump", 3LL}, {"Slash", 4LL}, {"Stab", 5LL}, {"Bonk", 6LL}, {"ReverseBonk", 7LL}, {"Chop", 8LL}, {"Squish", 9LL}, {"Block", 10LL}, {"Wave", 11LL}, {"Potion", 12LL}, {"Sweep", 13LL}, {"Spin", 14LL}, {"Throw", 15LL}, {"Shoot", 16LL}, {"Struggle", 17LL}, {"ReverseStab", 18LL}, {"Hiss", 19LL}, {"Tackle", 20LL}, {"DoubleSlash", 21LL}, {"Flash", 22LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_ActivationAni = {"ActivationAni", _ekv_Gd__gd_core__Item_ActivationAni, 23u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Stat[] = {{"MinDamage", 0LL}, {"MaxDamage", 1LL}, {"StaminaCost", 2LL}, {"Speed", 3LL}, {"BaseCooldown", 4LL}, {"Accuracy", 5LL}, {"CritChance", 6LL}, {"Chance", 7LL}, {"Chance2", 8LL}, {"Cooldown", 9LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Stat = {"Stat", _ekv_Gd__gd_core__Item_Stat, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_StackChangeType[] = {{"Added_Player", 0LL}, {"Added_Opponent", 1LL}, {"Removed_Player", 2LL}, {"Removed_Opponent", 3LL}, {"Used_Player", 4LL}, {"Used_Opponent", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_StackChangeType = {"StackChangeType", _ekv_Gd__gd_core__Item_StackChangeType, 6u};
void Gd__gd_core__Item::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__CoreItem::init_fields(gd_ctx);
    this->f_numStackChangeTypes = gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_867), gd::SYM_size, nullptr, 0);
    this->f_spriteScale = gd::GdVal::null();
    this->f_hasSquishySprite = gd::GdVal::from_bool(false);
    this->f_specificDragParticles = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_dragParticlesEnabled = gd::GdVal::from_bool(true);
    this->f_frictionTime = gd::GdVal::from_float(15.0);
    this->f_totalWeight = gd::GdVal::from_float(0.0);
    this->f_me = gd::GdVal::from_obj(this);
    this->f_mouseIsOverItem = gd::GdVal::from_bool(false);
    this->f_hovered = gd::GdVal::from_bool(false);
    this->f_focus = gd::GdVal::from_bool(false);
    this->f_spotlight = gd::GdVal::from_bool(false);
    this->f_collisionShape = gd::GdVal::null();
    this->f_wasJustCrafted = gd::GdVal::from_bool(false);
    this->f_pickupPosition = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_pickupRotation = gd::GdVal::from_float(0.0);
    this->f_pickupTopLeftCell = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_pickupFaceDirection = gd::GdVal::from_int(0);
    this->f_sameOrientationAsPickup = gd::GdVal::from_bool(false);
    this->f_movebackTween = gd::GdVal::null();
    this->f_rotationTween = gd::GdVal::null();
    this->f_pickingEnabled = gd::GdVal::from_bool(true);
    this->f_tooltipEnabled = gd::GdVal::from_bool(true);
    this->f_hoverResponseEnabled = gd::GdVal::from_bool(true);
    this->f_focusEnabled = gd::GdVal::from_bool(true);
    this->f_affectedCellsActive = gd::GdVal::from_bool(true);
    this->f_affordable = gd::GdVal::from_bool(false);
    this->f_momentumStrength = gd::GdVal::from_float(0.0);
    this->f_momentum = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_tooltip = gd::GdVal::null();
    this->f_tooltipMargin = gd::GdVal::from_vec2((gd::GdVal::from_int(100LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
    this->f_tooltipUpdateQueued = gd::GdVal::from_bool(false);
    this->f_shadows = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_spritesWithShadows = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_shadowOffset = Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_521);
    this->f_shadowTween = gd::GdVal::null();
    this->f_dropFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_pickupFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_mouseWheelRotationReadyTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_notEnoughGoldLabelReadyTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_averagedPosition = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_impactSoundVolume = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_progressMaterial = gd::GdVal::null();
    this->f_insideRotationNode = gd::GdVal::null();
    this->f_draggedInsideItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_draggingParent = gd::GdVal::null();
    this->f_sold = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_lastVelocity = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_lastCollisionPos = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_lastCollider = gd::GdVal::null();
    this->f_impactSoundReadyTime = gd::GdVal::from_float(0.0);
    this->f_globalAffectVisuals = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_bondedBaseItem = gd::GdVal::null();
    this->f_bondedIngredients = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_locked = gd::GdVal::from_bool(false);
    this->f_bound = gd::GdVal::from_bool(false);
    this->f_curRecipe = gd::GdVal::null();
    this->f_bondVisuals = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_craftingLabel = gd::GdVal::null();
    this->f_craftingAniReadyTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_pooled = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_initialized = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_canAffectVisuals = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_rotationMomentum = gd::GdVal::from_int(0LL);
    this->f_bonusRotation = gd::GdVal::from_int(0LL);
    this->f_brightColor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 4); })();
    this->f_defaultColor = gd::get_named_color("white");
    this->f_buildIntoRecipesTooltip = gd::GdVal::null();
    this->f_owningBuildIntoRecipesTooltip = gd::GdVal::null();
    this->f_ownerTypesWithBuildTooltip = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 5); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_BuildViewer_2553), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerStorageBox_2579), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerInventory_2554), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Opponent_2544), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_GridStorage_2608), gd::GdVal::from_bool(true)); return gd::GdVal::from_dict(d); })();
    this->f_shaderTween = gd::GdVal::null();
    this->f_canCancelShaderTween = gd::GdVal::from_bool(true);
    this->f_nonRotatedProgress = gd::GdVal::from_float(0.0);
    this->f_fusing = gd::GdVal::from_bool(false);
    this->f_willBeConsumed = gd::GdVal::from_bool(false);
    this->f_fuseParticles1 = gd::GdVal::null();
    this->f_fuseParticles2 = gd::GdVal::null();
    this->f_fuseTween = gd::GdVal::null();
    this->f_fusingBonds = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_collisionMap = gd::GdVal::null();
    this->f_animation = gd::GdVal::null();
    this->f_sprite = gd::GdVal::null();
    this->f_clickArea = gd::GdVal::null();
    this->f_dragParticles = gd::GdVal::null();
    this->f_sockets = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_lock = gd::GdVal::null();
    this->f_lockAnimation = gd::GdVal::null();
    this->f_baseBounce = gd::GdVal::from_float(0.0);
    this->f_baseFriction = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core__Item::meta() const { return &META_Gd__gd_core__Item; }
gd::GdVal Gd__gd_core__Item::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_Owner_850: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Owner);
        case SYM_GEN_Type_851: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Type);
        case SYM_GEN_Priority_852: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Priority);
        case SYM_GEN_CraftingPriority_853: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_CraftingPriority);
        case SYM_GEN_Tag_854: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tag);
        case SYM_GEN_Stack_855: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stack);
        case SYM_GEN_Mat_856: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Mat);
        case SYM_GEN_Physics_857: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Physics);
        case SYM_GEN_Rarity_858: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Rarity);
        case SYM_GEN_FaceDirection_859: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_FaceDirection);
        case SYM_GEN_StatModified_860: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StatModified);
        case SYM_GEN_DropResult_861: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_DropResult);
        case SYM_GEN_PickupType_862: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_PickupType);
        case SYM_GEN_Affected_863: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Affected);
        case SYM_GEN_Tiles_864: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tiles);
        case SYM_GEN_ActivationAni_865: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_ActivationAni);
        case SYM_GEN_Stat_866: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stat);
        case SYM_GEN_StackChangeType_867: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StackChangeType);
        case SYM_GEN_affectedColorToTileId_505: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580), gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_864), SYM_GEN_Affected_863)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582), gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_864), SYM_GEN_AffectedSecondary_2609)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Tertiary_2583), gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_864), SYM_GEN_AffectedTertiary_2610)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611), gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_864), SYM_GEN_AffectedLightning_2612)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_rarityColors_507: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.460205), gd::GdVal::from_float(0.874887), gd::GdVal::from_float(0.90625)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.0737), gd::GdVal::from_float(0.337874), gd::GdVal::from_float(0.898438)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.828125), gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.609375), gd::GdVal::from_int(0LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.980469), gd::GdVal::from_float(0.946239), gd::GdVal::from_float(0.582153)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.094223), gd::GdVal::from_float(0.964844), gd::GdVal::from_float(0.250663)}; return gd::make_color_from_args(_ca, 3); })()}));
        case SYM_GEN_offset_512: return gd::GdVal::from_int(40LL);
        case SYM_GEN_impulse_513: return gd::GdVal::from_int(50LL);
        case SYM_GEN_momentumFactor_514: return gd::GdVal::from_float(20.0);
        case SYM_GEN_affectedSoundsVolume_517: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580), gd::gd_neg(gd::GdVal::from_int(8LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Tertiary_2583), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611), gd::gd_neg(gd::GdVal::from_int(1LL))); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_cellSize_518: return gd::GdVal::from_vec2((gd::GdVal::from_int(80LL)).as_float(), (gd::GdVal::from_int(80LL)).as_float());
        case SYM_GEN_halfCellSize_519: return gd::gd_mul(gd::GdVal::from_float(0.5), Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518));
        case SYM_GEN_shadowOffset_shop_520: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        case SYM_GEN_shadowOffset_dropped_521: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(5LL)).as_float());
        case SYM_GEN_shadowOffset_dragged_522: return gd::GdVal::from_vec2((gd::GdVal::from_int(15LL)).as_float(), (gd::GdVal::from_int(15LL)).as_float());
        case SYM_GEN_DRAG_PRIORITY_523: return gd::GdVal::from_int(2LL);
        case SYM_GEN_correction_579: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518), gd::SYM_x))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518), gd::SYM_x))).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518), gd::SYM_y))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518), gd::SYM_y))).as_float())}));
        case SYM_GEN_angleStep_581: return gd::GdVal::from_int(45LL);
        case SYM_GEN_moveRotationMouseFactor_584: return gd::GdVal::from_float(0.015);
        case SYM_GEN_backforce_585: return gd::GdVal::from_float(5.0);
        case SYM_GEN_fric_586: return gd::GdVal::from_float(15.0);
        case SYM_GEN_maxAngle_587: return gd::GdVal::from_int(10LL);
        case SYM_GEN_moveRotationSpeed_588: return gd::GdVal::from_float(60.0);
        case SYM_GEN_hoverableWhenMenuOpen_594: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_ItemLibrary_2613), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_InfoPanelIcon_2614), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Tooltip_2615), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_RecipeBook_2616), gd::GdVal::from_bool(true)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_MISS_OFFSET_598: return gd::GdVal::from_float(100.0);
        case SYM_GEN_PRE_FUSE_DUR_599: return gd::GdVal::from_float(1.0);
        case SYM_GEN_PRE_FUSE_DUR_COG_600: return gd::GdVal::from_float(0.2);
        case SYM_GEN_FUSE_DUR_601: return gd::GdVal::from_float(1.0);
        case SYM_GEN_TRANSFORMATION_DUR_602: return gd::GdVal::from_float(1.0);
        case SYM_GEN_labelOffsets_609: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2((gd::GdVal::from_int(30LL)).as_float(), (gd::GdVal::from_int(30LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(30LL))).as_float(), (gd::GdVal::from_int(30LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(30LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(30LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(30LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(30LL))).as_float())}));
        case SYM_GEN_SignalConnection_873: return gd::GdVal::from_cls(&META_Gd__gd_core__Item__INNER__SignalConnection);
        default: break;
    }
    return Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Item::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Item::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numStackChangeTypes_506: out = this->f_numStackChangeTypes; return true;
        case SYM_GEN_spriteScale_508: out = this->f_spriteScale; return true;
        case SYM_GEN_hasSquishySprite_509: out = this->f_hasSquishySprite; return true;
        case SYM_GEN_specificDragParticles_510: out = this->f_specificDragParticles; return true;
        case SYM_GEN_dragParticlesEnabled_511: out = this->f_dragParticlesEnabled; return true;
        case SYM_GEN_frictionTime_515: out = this->f_frictionTime; return true;
        case SYM_GEN_totalWeight_516: out = this->f_totalWeight; return true;
        case SYM_GEN_me_524: out = this->f_me; return true;
        case SYM_GEN_mouseIsOverItem_525: out = this->f_mouseIsOverItem; return true;
        case SYM_GEN_hovered_526: out = this->f_hovered; return true;
        case SYM_GEN_focus_527: out = this->f_focus; return true;
        case SYM_GEN_spotlight_528: out = this->f_spotlight; return true;
        case SYM_GEN_collisionShape_529: out = this->f_collisionShape; return true;
        case SYM_GEN_wasJustCrafted_530: out = this->f_wasJustCrafted; return true;
        case SYM_GEN_pickupPosition_531: out = this->f_pickupPosition; return true;
        case SYM_GEN_pickupRotation_532: out = this->f_pickupRotation; return true;
        case SYM_GEN_pickupTopLeftCell_533: out = this->f_pickupTopLeftCell; return true;
        case SYM_GEN_pickupFaceDirection_534: out = this->f_pickupFaceDirection; return true;
        case SYM_GEN_sameOrientationAsPickup_535: out = this->f_sameOrientationAsPickup; return true;
        case SYM_GEN_movebackTween_536: out = this->f_movebackTween; return true;
        case SYM_GEN_rotationTween_537: out = this->f_rotationTween; return true;
        case SYM_GEN_pickingEnabled_538: out = this->f_pickingEnabled; return true;
        case SYM_GEN_tooltipEnabled_539: out = this->f_tooltipEnabled; return true;
        case SYM_GEN_hoverResponseEnabled_540: out = this->f_hoverResponseEnabled; return true;
        case SYM_GEN_focusEnabled_541: out = this->f_focusEnabled; return true;
        case SYM_GEN_affectedCellsActive_542: out = this->f_affectedCellsActive; return true;
        case SYM_GEN_affordable_543: out = this->f_affordable; return true;
        case SYM_GEN_momentumStrength_544: out = this->f_momentumStrength; return true;
        case SYM_GEN_momentum_545: out = this->f_momentum; return true;
        case SYM_GEN_tooltip_546: out = this->f_tooltip; return true;
        case SYM_GEN_tooltipMargin_547: out = this->f_tooltipMargin; return true;
        case SYM_GEN_tooltipUpdateQueued_548: out = this->f_tooltipUpdateQueued; return true;
        case SYM_GEN_shadows_549: out = this->f_shadows; return true;
        case SYM_GEN_spritesWithShadows_550: out = this->f_spritesWithShadows; return true;
        case SYM_GEN_shadowOffset_551: out = this->f_shadowOffset; return true;
        case SYM_GEN_shadowTween_552: out = this->f_shadowTween; return true;
        case SYM_GEN_dropFrame_553: out = this->f_dropFrame; return true;
        case SYM_GEN_pickupFrame_554: out = this->f_pickupFrame; return true;
        case SYM_GEN_mouseWheelRotationReadyTime_555: out = this->f_mouseWheelRotationReadyTime; return true;
        case SYM_GEN_notEnoughGoldLabelReadyTime_556: out = this->f_notEnoughGoldLabelReadyTime; return true;
        case SYM_GEN_averagedPosition_557: out = this->f_averagedPosition; return true;
        case SYM_GEN_impactSoundVolume_558: out = this->f_impactSoundVolume; return true;
        case SYM_GEN_progressMaterial_559: out = this->f_progressMaterial; return true;
        case SYM_GEN_insideRotationNode_560: out = this->f_insideRotationNode; return true;
        case SYM_GEN_draggedInsideItems_561: out = this->f_draggedInsideItems; return true;
        case SYM_GEN_draggingParent_562: out = this->f_draggingParent; return true;
        case SYM_GEN_sold_563: out = this->f_sold; return true;
        case SYM_GEN_lastVelocity_564: out = this->f_lastVelocity; return true;
        case SYM_GEN_lastCollisionPos_565: out = this->f_lastCollisionPos; return true;
        case SYM_GEN_lastCollider_566: out = this->f_lastCollider; return true;
        case SYM_GEN_impactSoundReadyTime_567: out = this->f_impactSoundReadyTime; return true;
        case SYM_GEN_globalAffectVisuals_568: out = this->f_globalAffectVisuals; return true;
        case SYM_GEN_bondedBaseItem_569: out = this->f_bondedBaseItem; return true;
        case SYM_GEN_bondedIngredients_570: out = this->f_bondedIngredients; return true;
        case SYM_GEN_locked_571: out = this->f_locked; return true;
        case SYM_GEN_bound_572: out = this->f_bound; return true;
        case SYM_GEN_curRecipe_573: out = this->f_curRecipe; return true;
        case SYM_GEN_bondVisuals_574: out = this->f_bondVisuals; return true;
        case SYM_GEN_craftingLabel_575: out = this->f_craftingLabel; return true;
        case SYM_GEN_craftingAniReadyTime_576: out = this->f_craftingAniReadyTime; return true;
        case SYM_GEN_pooled_577: out = this->f_pooled; return true;
        case SYM_GEN_initialized_578: out = this->f_initialized; return true;
        case SYM_GEN_canAffectVisuals_580: out = this->f_canAffectVisuals; return true;
        case SYM_GEN_rotationMomentum_582: out = this->f_rotationMomentum; return true;
        case SYM_GEN_bonusRotation_583: out = this->f_bonusRotation; return true;
        case SYM_GEN_brightColor_589: out = this->f_brightColor; return true;
        case SYM_GEN_defaultColor_590: out = this->f_defaultColor; return true;
        case SYM_GEN_buildIntoRecipesTooltip_591: out = this->f_buildIntoRecipesTooltip; return true;
        case SYM_GEN_owningBuildIntoRecipesTooltip_592: out = this->f_owningBuildIntoRecipesTooltip; return true;
        case SYM_GEN_ownerTypesWithBuildTooltip_593: out = this->f_ownerTypesWithBuildTooltip; return true;
        case SYM_GEN_shaderTween_595: out = this->f_shaderTween; return true;
        case SYM_GEN_canCancelShaderTween_596: out = this->f_canCancelShaderTween; return true;
        case SYM_GEN_nonRotatedProgress_597: out = this->f_nonRotatedProgress; return true;
        case SYM_GEN_fusing_603: out = this->f_fusing; return true;
        case SYM_GEN_willBeConsumed_604: out = this->f_willBeConsumed; return true;
        case SYM_GEN_fuseParticles1_605: out = this->f_fuseParticles1; return true;
        case SYM_GEN_fuseParticles2_606: out = this->f_fuseParticles2; return true;
        case SYM_GEN_fuseTween_607: out = this->f_fuseTween; return true;
        case SYM_GEN_fusingBonds_608: out = this->f_fusingBonds; return true;
        case SYM_GEN_collisionMap_610: out = this->f_collisionMap; return true;
        case SYM_GEN_animation_611: out = this->f_animation; return true;
        case SYM_GEN_sprite_612: out = this->f_sprite; return true;
        case SYM_GEN_clickArea_613: out = this->f_clickArea; return true;
        case SYM_GEN_dragParticles_614: out = this->f_dragParticles; return true;
        case SYM_GEN_sockets_615: out = this->f_sockets; return true;
        case SYM_GEN_lock_616: out = this->f_lock; return true;
        case SYM_GEN_lockAnimation_617: out = this->f_lockAnimation; return true;
        case SYM_GEN_baseBounce_618: out = this->f_baseBounce; return true;
        case SYM_GEN_baseFriction_619: out = this->f_baseFriction; return true;
        case SYM_GEN_Owner_850: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Owner); return true;
        case SYM_GEN_Type_851: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Type); return true;
        case SYM_GEN_Priority_852: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Priority); return true;
        case SYM_GEN_CraftingPriority_853: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_CraftingPriority); return true;
        case SYM_GEN_Tag_854: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tag); return true;
        case SYM_GEN_Stack_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stack); return true;
        case SYM_GEN_Mat_856: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Mat); return true;
        case SYM_GEN_Physics_857: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Physics); return true;
        case SYM_GEN_Rarity_858: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Rarity); return true;
        case SYM_GEN_FaceDirection_859: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_FaceDirection); return true;
        case SYM_GEN_StatModified_860: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StatModified); return true;
        case SYM_GEN_DropResult_861: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_DropResult); return true;
        case SYM_GEN_PickupType_862: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_PickupType); return true;
        case SYM_GEN_Affected_863: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Affected); return true;
        case SYM_GEN_Tiles_864: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tiles); return true;
        case SYM_GEN_ActivationAni_865: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_ActivationAni); return true;
        case SYM_GEN_Stat_866: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stat); return true;
        case SYM_GEN_StackChangeType_867: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StackChangeType); return true;
        case SYM_GEN_SignalConnection_873: out = gd::GdVal::from_cls(&META_Gd__gd_core__Item__INNER__SignalConnection); return true;
        case SYM_GEN_affectedColorToTileId_505: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_rarityColors_507: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_offset_512: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_impulse_513: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_momentumFactor_514: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_affectedSoundsVolume_517: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_cellSize_518: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_halfCellSize_519: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_shop_520: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_dropped_521: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_dragged_522: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_DRAG_PRIORITY_523: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_correction_579: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_angleStep_581: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_moveRotationMouseFactor_584: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_backforce_585: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_fric_586: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_maxAngle_587: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_moveRotationSpeed_588: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_hoverableWhenMenuOpen_594: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_MISS_OFFSET_598: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PRE_FUSE_DUR_599: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PRE_FUSE_DUR_COG_600: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FUSE_DUR_601: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_TRANSFORMATION_DUR_602: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_labelOffsets_609: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::get_prop(prop, out);
}
bool Gd__gd_core__Item::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numStackChangeTypes_506: this->f_numStackChangeTypes = val; return true;
        case SYM_GEN_spriteScale_508: this->f_spriteScale = val; return true;
        case SYM_GEN_hasSquishySprite_509: this->f_hasSquishySprite = val; return true;
        case SYM_GEN_specificDragParticles_510: this->f_specificDragParticles = val; return true;
        case SYM_GEN_dragParticlesEnabled_511: this->f_dragParticlesEnabled = val; return true;
        case SYM_GEN_frictionTime_515: this->f_frictionTime = val; return true;
        case SYM_GEN_totalWeight_516: this->f_totalWeight = gd::gd_coerce_float(val); return true;
        case SYM_GEN_me_524: this->f_me = val; return true;
        case SYM_GEN_mouseIsOverItem_525: this->f_mouseIsOverItem = val; return true;
        case SYM_GEN_hovered_526: this->f_hovered = val; return true;
        case SYM_GEN_focus_527: this->f_focus = val; return true;
        case SYM_GEN_spotlight_528: this->f_spotlight = val; return true;
        case SYM_GEN_collisionShape_529: this->f_collisionShape = val; return true;
        case SYM_GEN_wasJustCrafted_530: this->f_wasJustCrafted = val; return true;
        case SYM_GEN_pickupPosition_531: this->f_pickupPosition = val; return true;
        case SYM_GEN_pickupRotation_532: this->f_pickupRotation = gd::gd_coerce_float(val); return true;
        case SYM_GEN_pickupTopLeftCell_533: this->f_pickupTopLeftCell = val; return true;
        case SYM_GEN_pickupFaceDirection_534: this->f_pickupFaceDirection = gd::gd_coerce_int(val); return true;
        case SYM_GEN_sameOrientationAsPickup_535: this->f_sameOrientationAsPickup = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_movebackTween_536: this->f_movebackTween = val; return true;
        case SYM_GEN_rotationTween_537: this->f_rotationTween = val; return true;
        case SYM_GEN_pickingEnabled_538: this->f_pickingEnabled = val; return true;
        case SYM_GEN_tooltipEnabled_539: this->f_tooltipEnabled = val; return true;
        case SYM_GEN_hoverResponseEnabled_540: this->f_hoverResponseEnabled = val; return true;
        case SYM_GEN_focusEnabled_541: this->f_focusEnabled = val; return true;
        case SYM_GEN_affectedCellsActive_542: this->f_affectedCellsActive = val; return true;
        case SYM_GEN_affordable_543: this->f_affordable = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_momentumStrength_544: this->f_momentumStrength = gd::gd_coerce_float(val); return true;
        case SYM_GEN_momentum_545: this->f_momentum = val; return true;
        case SYM_GEN_tooltip_546: this->f_tooltip = val; return true;
        case SYM_GEN_tooltipMargin_547: this->f_tooltipMargin = val; return true;
        case SYM_GEN_tooltipUpdateQueued_548: this->f_tooltipUpdateQueued = val; return true;
        case SYM_GEN_shadows_549: this->f_shadows = val; return true;
        case SYM_GEN_spritesWithShadows_550: this->f_spritesWithShadows = val; return true;
        case SYM_GEN_shadowOffset_551: this->f_shadowOffset = val; return true;
        case SYM_GEN_shadowTween_552: this->f_shadowTween = val; return true;
        case SYM_GEN_dropFrame_553: this->f_dropFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_pickupFrame_554: this->f_pickupFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_mouseWheelRotationReadyTime_555: this->f_mouseWheelRotationReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_notEnoughGoldLabelReadyTime_556: this->f_notEnoughGoldLabelReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_averagedPosition_557: this->f_averagedPosition = val; return true;
        case SYM_GEN_impactSoundVolume_558: this->f_impactSoundVolume = gd::gd_coerce_float(val); return true;
        case SYM_GEN_progressMaterial_559: this->f_progressMaterial = val; return true;
        case SYM_GEN_insideRotationNode_560: this->f_insideRotationNode = val; return true;
        case SYM_GEN_draggedInsideItems_561: this->f_draggedInsideItems = val; return true;
        case SYM_GEN_draggingParent_562: this->f_draggingParent = val; return true;
        case SYM_GEN_sold_563: this->f_sold = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_lastVelocity_564: this->f_lastVelocity = val; return true;
        case SYM_GEN_lastCollisionPos_565: this->f_lastCollisionPos = val; return true;
        case SYM_GEN_lastCollider_566: this->f_lastCollider = val; return true;
        case SYM_GEN_impactSoundReadyTime_567: this->f_impactSoundReadyTime = val; return true;
        case SYM_GEN_globalAffectVisuals_568: this->f_globalAffectVisuals = val; return true;
        case SYM_GEN_bondedBaseItem_569: this->f_bondedBaseItem = val; return true;
        case SYM_GEN_bondedIngredients_570: this->f_bondedIngredients = val; return true;
        case SYM_GEN_locked_571: this->f_locked = val; return true;
        case SYM_GEN_bound_572: this->f_bound = val; return true;
        case SYM_GEN_curRecipe_573: this->f_curRecipe = val; return true;
        case SYM_GEN_bondVisuals_574: this->f_bondVisuals = val; return true;
        case SYM_GEN_craftingLabel_575: this->f_craftingLabel = val; return true;
        case SYM_GEN_craftingAniReadyTime_576: this->f_craftingAniReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_pooled_577: this->f_pooled = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_initialized_578: this->f_initialized = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_canAffectVisuals_580: this->f_canAffectVisuals = val; return true;
        case SYM_GEN_rotationMomentum_582: this->f_rotationMomentum = val; return true;
        case SYM_GEN_bonusRotation_583: this->f_bonusRotation = val; return true;
        case SYM_GEN_brightColor_589: this->f_brightColor = val; return true;
        case SYM_GEN_defaultColor_590: this->f_defaultColor = val; return true;
        case SYM_GEN_buildIntoRecipesTooltip_591: this->f_buildIntoRecipesTooltip = val; return true;
        case SYM_GEN_owningBuildIntoRecipesTooltip_592: this->f_owningBuildIntoRecipesTooltip = val; return true;
        case SYM_GEN_ownerTypesWithBuildTooltip_593: this->f_ownerTypesWithBuildTooltip = val; return true;
        case SYM_GEN_shaderTween_595: this->f_shaderTween = val; return true;
        case SYM_GEN_canCancelShaderTween_596: this->f_canCancelShaderTween = val; return true;
        case SYM_GEN_nonRotatedProgress_597: this->f_nonRotatedProgress = val; return true;
        case SYM_GEN_fusing_603: this->f_fusing = val; return true;
        case SYM_GEN_willBeConsumed_604: this->f_willBeConsumed = val; return true;
        case SYM_GEN_fuseParticles1_605: this->f_fuseParticles1 = val; return true;
        case SYM_GEN_fuseParticles2_606: this->f_fuseParticles2 = val; return true;
        case SYM_GEN_fuseTween_607: this->f_fuseTween = val; return true;
        case SYM_GEN_fusingBonds_608: this->f_fusingBonds = val; return true;
        case SYM_GEN_collisionMap_610: this->f_collisionMap = val; return true;
        case SYM_GEN_animation_611: this->f_animation = val; return true;
        case SYM_GEN_sprite_612: this->f_sprite = val; return true;
        case SYM_GEN_clickArea_613: this->f_clickArea = val; return true;
        case SYM_GEN_dragParticles_614: this->f_dragParticles = val; return true;
        case SYM_GEN_sockets_615: this->f_sockets = val; return true;
        case SYM_GEN_lock_616: this->f_lock = val; return true;
        case SYM_GEN_lockAnimation_617: this->f_lockAnimation = val; return true;
        case SYM_GEN_baseBounce_618: this->f_baseBounce = gd::gd_coerce_float(val); return true;
        case SYM_GEN_baseFriction_619: this->f_baseFriction = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Item::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN__readyInit_138: return true;
        case SYM_GEN_preset_622: return true;
        case SYM_GEN_initPhysicsMaterial_623: return true;
        case SYM_GEN_getShadowOffset_624: return true;
        case SYM_GEN_initRecipeBook_625: return true;
        case SYM_GEN_initItemLibrary_626: return true;
        case SYM_GEN_setSpotlight_627: return true;
        case SYM_GEN_initTitle_628: return true;
        case SYM_GEN_initTooltip_629: return true;
        case SYM_GEN_initBuildViewer_630: return true;
        case SYM_GEN_initBuildViewerIcon_631: return true;
        case SYM_GEN_initInfoPanelIcon_632: return true;
        case SYM_GEN_initGridStorageIcon_633: return true;
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_persistDataInShop_636: return true;
        case SYM_GEN_getTranslatedName_637: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_insertParameters_639: return true;
        case SYM_GEN_insertParameter_640: return true;
        case SYM_GEN_getModeDescription_641: return true;
        case SYM_GEN_getFlavorText_642: return true;
        case SYM_GEN_disablePicking_643: return true;
        case SYM_GEN_enablePicking_644: return true;
        case SYM_GEN_enableTooltip_645: return true;
        case SYM_GEN_disableTooltip_646: return true;
        case SYM_GEN_disableFocus_647: return true;
        case SYM_GEN_enableFocus_648: return true;
        case SYM_GEN_setEditMode_649: return true;
        case SYM_GEN_setShadowAlpha_650: return true;
        case SYM_GEN_getTopLeftGlobal_651: return true;
        case SYM_GEN_getBottomRightGlobal_652: return true;
        case SYM_GEN_getBottomCenter_653: return true;
        case SYM_GEN_getInventory_654: return true;
        case SYM_GEN_removeFromInventory_658: return true;
        case SYM_GEN_playAffectedPlacedAnimation_659: return true;
        case SYM_GEN_clearCanAffectVisuals_660: return true;
        case SYM_GEN_liesInStorage_661: return true;
        case SYM_GEN_pushToStorage_662: return true;
        case SYM_GEN_addToStorageBox_663: return true;
        case SYM_GEN_removeFromStorage_664: return true;
        case SYM_GEN_onStorageLeft_665: return true;
        case SYM_GEN_isInGridStorage_666: return true;
        case SYM_GEN_getGridStorageProxy_667: return true;
        case SYM_GEN_onAddedToGridStorage_668: return true;
        case SYM_GEN_onRemovedFromGridStorage_669: return true;
        case SYM_GEN_makeGrabbable_670: return true;
        case SYM_GEN_moveToFreeSpaceInStorage_671: return true;
        case SYM_GEN_checkIfOutofStorageBounds_672: return true;
        case SYM_GEN_checkIfOutofStorageBounds2_673: return true;
        case SYM_GEN_checkIfOutofStorageBounds3_674: return true;
        case SYM_GEN_findFreeSpace_675: return true;
        case SYM_GEN_unclip_676: return true;
        case SYM_GEN_onAddedToStorageBox_677: return true;
        case SYM_GEN__process_678: return true;
        case SYM_GEN__integrate_forces_679: return true;
        case SYM_GEN_updateShadow_680: return true;
        case SYM_GEN_lerpAngle_local_681: return true;
        case SYM_GEN_updateInsideRotationNode_682: return true;
        case SYM_GEN_spawnRotationSparks_683: return true;
        case SYM_GEN_highlight_684: return true;
        case SYM_GEN_unhighlight_685: return true;
        case SYM_GEN_setBright_686: return true;
        case SYM_GEN_resetBright_687: return true;
        case SYM_GEN_getHoverPriority_688: return true;
        case SYM_GEN_canGainFocus_689: return true;
        case SYM_GEN_gainFocus_690: return true;
        case SYM_GEN_respondToHover_691: return true;
        case SYM_GEN_canShowBuildIntoRecipesTooltip_692: return true;
        case SYM_GEN_canShowSubBuildIntoRecipesTooltip_693: return true;
        case SYM_GEN_showBuildIntoRecipesTooltip_694: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN_getRelatedItemHeight_696: return true;
        case SYM_GEN_getRecipeDescriptor_697: return true;
        case SYM_GEN_hideBuildIntoRecipesTooltip_698: return true;
        case SYM_GEN_loseFocus_699: return true;
        case SYM_GEN_respondToHoverEnd_700: return true;
        case SYM_GEN_activateDragParticles_701: return true;
        case SYM_GEN_deactivateDragParticles_702: return true;
        case SYM_GEN_updateTooltip_703: return true;
        case SYM_GEN_queueTooltipUpdate_704: return true;
        case SYM_GEN_clearTooltip_705: return true;
        case SYM_GEN_mouseEntered_706: return true;
        case SYM_GEN_hover_707: return true;
        case SYM_GEN_mouseExited_708: return true;
        case SYM_GEN_hoverEnd_709: return true;
        case SYM_GEN_isHovered_710: return true;
        case SYM_GEN_getScaleProp_711: return true;
        case SYM_GEN_setSpriteScale_712: return true;
        case SYM_GEN_pickup_713: return true;
        case SYM_GEN_onDraggedWithParentStart_714: return true;
        case SYM_GEN_finishMoveback_715: return true;
        case SYM_GEN_onDraggedWithParentEnd_716: return true;
        case SYM_GEN_canSnap_717: return true;
        case SYM_GEN_reactToDropResult_718: return true;
        case SYM_GEN_drop_719: return true;
        case SYM_GEN_showClickArea_720: return true;
        case SYM_GEN_cancelDrag_721: return true;
        case SYM_GEN_emptyTweenCallback_722: return true;
        case SYM_GEN_killMovebackTween_723: return true;
        case SYM_GEN_setSpriteGlobalPos_724: return true;
        case SYM_GEN_dropIntoInventory_725: return true;
        case SYM_GEN_finishInsideItemsRotation_726: return true;
        case SYM_GEN_pushDraggedItemsToStorage_727: return true;
        case SYM_GEN_reparentItemsInside_728: return true;
        case SYM_GEN_clearDraggedInsideItems_729: return true;
        case SYM_GEN_showSockets_730: return true;
        case SYM_GEN_hideSockets_731: return true;
        case SYM_GEN_playPickupSound_732: return true;
        case SYM_GEN_playDropSound_147: return true;
        case SYM_GEN_canBeSold_733: return true;
        case SYM_GEN_isPickingPossible_734: return true;
        case SYM_GEN_canBePicked_735: return true;
        case SYM_GEN_canBeDraggedWithBag_736: return true;
        case SYM_GEN_canBeDropped_737: return true;
        case SYM_GEN__input_738: return true;
        case SYM_GEN_resetSprite_739: return true;
        case SYM_GEN_combatToShop_740: return true;
        case SYM_GEN_shopEntered_741: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_startFusing_inShop_743: return true;
        case SYM_GEN_getCraftingPriority_744: return true;
        case SYM_GEN_addToCraftingQueue_745: return true;
        case SYM_GEN_combatToTitle_746: return true;
        case SYM_GEN_readyToFuse_747: return true;
        case SYM_GEN_startFusing_748: return true;
        case SYM_GEN_readyToTransform_749: return true;
        case SYM_GEN_giveGold_750: return true;
        case SYM_GEN_getTranslatedTypeName_751: return true;
        case SYM_GEN_getTypeDescription_752: return true;
        case SYM_GEN_getTranslatedRarity_753: return true;
        case SYM_GEN_logCooldown_755: return true;
        case SYM_GEN_getCombatDisplayAccuracy_756: return true;
        case SYM_GEN_getDisplayCritChance_757: return true;
        case SYM_GEN_getSalesMultiplier_758: return true;
        case SYM_GEN_prepareDiscard_759: return true;
        case SYM_GEN_discard_760: return true;
        case SYM_GEN_popIn_761: return true;
        case SYM_GEN_disappear_762: return true;
        case SYM_GEN_appearInLibrary_763: return true;
        case SYM_GEN_createParticles_764: return true;
        case SYM_GEN_deactivateParticles_765: return true;
        case SYM_GEN_makeRigidBody_766: return true;
        case SYM_GEN_dropImpulse_767: return true;
        case SYM_GEN_makeNonRigidBody_768: return true;
        case SYM_GEN_rollShopChance_769: return true;
        case SYM_GEN__physics_process_770: return true;
        case SYM_GEN_playActivationAnimation_Scale_771: return true;
        case SYM_GEN_playActivationAnimation_Jump_772: return true;
        case SYM_GEN_playActivationAnimation_JumpSquash_773: return true;
        case SYM_GEN_playActivationAnimation_774: return true;
        case SYM_GEN_playActivationSound_146: return true;
        case SYM_GEN_clearSpriteMaterial_775: return true;
        case SYM_GEN_giveProgressMaterial_776: return true;
        case SYM_GEN_getTextureSize_777: return true;
        case SYM_GEN_scaleToFit_778: return true;
        case SYM_GEN_getSpriteOffset_779: return true;
        case SYM_GEN_getGlobalCenter_780: return true;
        case SYM_GEN_getTextureSize_local_781: return true;
        case SYM_GEN_scaleToFit_local_782: return true;
        case SYM_GEN_getSpriteOffset_local_783: return true;
        case SYM_GEN_setTexture_784: return true;
        case SYM_GEN_updateShadowTexture_785: return true;
        case SYM_GEN_initSpriteMaterial_786: return true;
        case SYM_GEN_updateShaderRotation_787: return true;
        case SYM_GEN_allowCancelShaderTween_788: return true;
        case SYM_GEN_showCooldownSmooth_789: return true;
        case SYM_GEN_showCooldown_790: return true;
        case SYM_GEN_createAnimation_791: return true;
        case SYM_GEN_playAnimation_792: return true;
        case SYM_GEN_hasInventoryDuration_793: return true;
        case SYM_GEN_reveal_794: return true;
        case SYM_GEN_setRevealed_795: return true;
        case SYM_GEN_isCrafted_796: return true;
        case SYM_GEN_isMovingBack_797: return true;
        case SYM_GEN__notification_798: return true;
        case SYM_GEN_getAllInInventoryOfType_799: return true;
        case SYM_GEN_countAllInInventoryOfType_800: return true;
        case SYM_GEN_isTypeInInventory_801: return true;
        case SYM_GEN_isRecipeFinished_802: return true;
        case SYM_GEN_canStartNewRecipe_803: return true;
        case SYM_GEN_getRecipes_804: return true;
        case SYM_GEN_breakBondVisual_805: return true;
        case SYM_GEN_removeBondedBaseItem_806: return true;
        case SYM_GEN_removeBondedIngredient_807: return true;
        case SYM_GEN_removeAllIngredients_808: return true;
        case SYM_GEN_considerAsBond_809: return true;
        case SYM_GEN_addBondedIngredient_810: return true;
        case SYM_GEN_addToBaseItem_811: return true;
        case SYM_GEN_playBondAnimation_812: return true;
        case SYM_GEN_playBondFailedAnimation_813: return true;
        case SYM_GEN_isCatalystBond_814: return true;
        case SYM_GEN_isLocked_815: return true;
        case SYM_GEN_canLockBag_816: return true;
        case SYM_GEN_canBeLocked_817: return true;
        case SYM_GEN_setLocked_818: return true;
        case SYM_GEN_unlockCombining_819: return true;
        case SYM_GEN_lockCombining_820: return true;
        case SYM_GEN_showLockLabel_821: return true;
        case SYM_GEN_getLockPosition_822: return true;
        case SYM_GEN_setBoundAsIngredient_823: return true;
        case SYM_GEN_canPreviewFusions_824: return true;
        case SYM_GEN_getCraftingPreviewPosition_825: return true;
        case SYM_GEN_previewFusions_826: return true;
        case SYM_GEN_previewRecipeIngredients_827: return true;
        case SYM_GEN_previewFusionToItem_828: return true;
        case SYM_GEN_hasShopItemCraftCandidates_829: return true;
        case SYM_GEN_typeInIngredients_830: return true;
        case SYM_GEN_getTextEffect_831: return true;
        case SYM_GEN_getFusionItemName_832: return true;
        case SYM_GEN_showProgressLabel_833: return true;
        case SYM_GEN_onCraftingLabelReturned_834: return true;
        case SYM_GEN_createBondVisual_835: return true;
        case SYM_GEN_updateBondVisuals_836: return true;
        case SYM_GEN_fuse_837: return true;
        case SYM_GEN_onFusingAsIngredient_838: return true;
        case SYM_GEN_onFusingAsCatalystFinished_839: return true;
        case SYM_GEN_createCraftedShockwave_840: return true;
        case SYM_GEN_finishFusing_841: return true;
        case SYM_GEN_allowGeneratingFusionItem_842: return true;
        case SYM_GEN_catalystFusingFinished_843: return true;
        case SYM_GEN_onFusingFinished_844: return true;
        case SYM_GEN_onCraftedFrom_845: return true;
        case SYM_GEN_getCraftingOffset_846: return true;
        case SYM_GEN_playCraftedAnimation_847: return true;
        case SYM_GEN_onRestoreSnapshot_848: return true;
        case SYM_GEN_getShopPriority_849: return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::has_own_method(m);
}
bool Gd__gd_core__Item::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        case SYM_GEN_getNumTooltipStats_620: out = sf_getNumTooltipStats(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumStackChangeTypes_621: out = sf_getNumStackChangeTypes(gd_ctx, args, argc); return true;
        case SYM_GEN_preset_622: out = fn_preset(args, argc); return true;
        case SYM_GEN_initPhysicsMaterial_623: out = fn_initPhysicsMaterial(args, argc); return true;
        case SYM_GEN_getShadowOffset_624: out = fn_getShadowOffset(args, argc); return true;
        case SYM_GEN_initRecipeBook_625: out = fn_initRecipeBook(args, argc); return true;
        case SYM_GEN_initItemLibrary_626: out = fn_initItemLibrary(args, argc); return true;
        case SYM_GEN_setSpotlight_627: out = fn_setSpotlight(args, argc); return true;
        case SYM_GEN_initTitle_628: out = fn_initTitle(args, argc); return true;
        case SYM_GEN_initTooltip_629: out = fn_initTooltip(args, argc); return true;
        case SYM_GEN_initBuildViewer_630: out = fn_initBuildViewer(args, argc); return true;
        case SYM_GEN_initBuildViewerIcon_631: out = fn_initBuildViewerIcon(args, argc); return true;
        case SYM_GEN_initInfoPanelIcon_632: out = fn_initInfoPanelIcon(args, argc); return true;
        case SYM_GEN_initGridStorageIcon_633: out = fn_initGridStorageIcon(args, argc); return true;
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_persistDataInShop_636: out = fn_persistDataInShop(args, argc); return true;
        case SYM_GEN_getTranslatedName_637: out = fn_getTranslatedName(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_insertParameters_639: out = fn_insertParameters(args, argc); return true;
        case SYM_GEN_insertParameter_640: out = fn_insertParameter(args, argc); return true;
        case SYM_GEN_getModeDescription_641: out = fn_getModeDescription(args, argc); return true;
        case SYM_GEN_getFlavorText_642: out = fn_getFlavorText(args, argc); return true;
        case SYM_GEN_disablePicking_643: out = fn_disablePicking(args, argc); return true;
        case SYM_GEN_enablePicking_644: out = fn_enablePicking(args, argc); return true;
        case SYM_GEN_enableTooltip_645: out = fn_enableTooltip(args, argc); return true;
        case SYM_GEN_disableTooltip_646: out = fn_disableTooltip(args, argc); return true;
        case SYM_GEN_disableFocus_647: out = fn_disableFocus(args, argc); return true;
        case SYM_GEN_enableFocus_648: out = fn_enableFocus(args, argc); return true;
        case SYM_GEN_setEditMode_649: out = fn_setEditMode(args, argc); return true;
        case SYM_GEN_setShadowAlpha_650: out = fn_setShadowAlpha(args, argc); return true;
        case SYM_GEN_getTopLeftGlobal_651: out = fn_getTopLeftGlobal(args, argc); return true;
        case SYM_GEN_getBottomRightGlobal_652: out = fn_getBottomRightGlobal(args, argc); return true;
        case SYM_GEN_getBottomCenter_653: out = fn_getBottomCenter(args, argc); return true;
        case SYM_GEN_getInventory_654: out = fn_getInventory(args, argc); return true;
        case SYM_GEN_wasAddedToInventory_655: out = sf_wasAddedToInventory(gd_ctx, args, argc); return true;
        case SYM_GEN_wasBought_656: out = sf_wasBought(gd_ctx, args, argc); return true;
        case SYM_GEN_wasHotSwap_657: out = sf_wasHotSwap(gd_ctx, args, argc); return true;
        case SYM_GEN_removeFromInventory_658: out = fn_removeFromInventory(args, argc); return true;
        case SYM_GEN_playAffectedPlacedAnimation_659: out = fn_playAffectedPlacedAnimation(args, argc); return true;
        case SYM_GEN_clearCanAffectVisuals_660: out = fn_clearCanAffectVisuals(args, argc); return true;
        case SYM_GEN_liesInStorage_661: out = fn_liesInStorage(args, argc); return true;
        case SYM_GEN_pushToStorage_662: out = fn_pushToStorage(args, argc); return true;
        case SYM_GEN_addToStorageBox_663: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_removeFromStorage_664: out = fn_removeFromStorage(args, argc); return true;
        case SYM_GEN_onStorageLeft_665: out = fn_onStorageLeft(args, argc); return true;
        case SYM_GEN_isInGridStorage_666: out = fn_isInGridStorage(args, argc); return true;
        case SYM_GEN_getGridStorageProxy_667: out = fn_getGridStorageProxy(args, argc); return true;
        case SYM_GEN_onAddedToGridStorage_668: out = fn_onAddedToGridStorage(args, argc); return true;
        case SYM_GEN_onRemovedFromGridStorage_669: out = fn_onRemovedFromGridStorage(args, argc); return true;
        case SYM_GEN_makeGrabbable_670: out = fn_makeGrabbable(args, argc); return true;
        case SYM_GEN_moveToFreeSpaceInStorage_671: out = fn_moveToFreeSpaceInStorage(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds_672: out = fn_checkIfOutofStorageBounds(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds2_673: out = fn_checkIfOutofStorageBounds2(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds3_674: out = fn_checkIfOutofStorageBounds3(args, argc); return true;
        case SYM_GEN_findFreeSpace_675: out = fn_findFreeSpace(args, argc); return true;
        case SYM_GEN_unclip_676: out = fn_unclip(args, argc); return true;
        case SYM_GEN_onAddedToStorageBox_677: out = fn_onAddedToStorageBox(args, argc); return true;
        case SYM_GEN__process_678: out = fn__process(args, argc); return true;
        case SYM_GEN__integrate_forces_679: out = fn__integrate_forces(args, argc); return true;
        case SYM_GEN_updateShadow_680: out = fn_updateShadow(args, argc); return true;
        case SYM_GEN_lerpAngle_local_681: out = fn_lerpAngle_local(args, argc); return true;
        case SYM_GEN_updateInsideRotationNode_682: out = fn_updateInsideRotationNode(args, argc); return true;
        case SYM_GEN_spawnRotationSparks_683: out = fn_spawnRotationSparks(args, argc); return true;
        case SYM_GEN_highlight_684: out = fn_highlight(args, argc); return true;
        case SYM_GEN_unhighlight_685: out = fn_unhighlight(args, argc); return true;
        case SYM_GEN_setBright_686: out = fn_setBright(args, argc); return true;
        case SYM_GEN_resetBright_687: out = fn_resetBright(args, argc); return true;
        case SYM_GEN_getHoverPriority_688: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_canGainFocus_689: out = fn_canGainFocus(args, argc); return true;
        case SYM_GEN_gainFocus_690: out = fn_gainFocus(args, argc); return true;
        case SYM_GEN_respondToHover_691: out = fn_respondToHover(args, argc); return true;
        case SYM_GEN_canShowBuildIntoRecipesTooltip_692: out = fn_canShowBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_canShowSubBuildIntoRecipesTooltip_693: out = fn_canShowSubBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_showBuildIntoRecipesTooltip_694: out = fn_showBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_696: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN_getRecipeDescriptor_697: out = fn_getRecipeDescriptor(args, argc); return true;
        case SYM_GEN_hideBuildIntoRecipesTooltip_698: out = fn_hideBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_loseFocus_699: out = fn_loseFocus(args, argc); return true;
        case SYM_GEN_respondToHoverEnd_700: out = fn_respondToHoverEnd(args, argc); return true;
        case SYM_GEN_activateDragParticles_701: out = fn_activateDragParticles(args, argc); return true;
        case SYM_GEN_deactivateDragParticles_702: out = fn_deactivateDragParticles(args, argc); return true;
        case SYM_GEN_updateTooltip_703: out = fn_updateTooltip(args, argc); return true;
        case SYM_GEN_queueTooltipUpdate_704: out = fn_queueTooltipUpdate(args, argc); return true;
        case SYM_GEN_clearTooltip_705: out = fn_clearTooltip(args, argc); return true;
        case SYM_GEN_mouseEntered_706: out = fn_mouseEntered(args, argc); return true;
        case SYM_GEN_hover_707: out = fn_hover(args, argc); return true;
        case SYM_GEN_mouseExited_708: out = fn_mouseExited(args, argc); return true;
        case SYM_GEN_hoverEnd_709: out = fn_hoverEnd(args, argc); return true;
        case SYM_GEN_isHovered_710: out = fn_isHovered(args, argc); return true;
        case SYM_GEN_getScaleProp_711: out = fn_getScaleProp(args, argc); return true;
        case SYM_GEN_setSpriteScale_712: out = fn_setSpriteScale(args, argc); return true;
        case SYM_GEN_pickup_713: out = fn_pickup(args, argc); return true;
        case SYM_GEN_onDraggedWithParentStart_714: out = fn_onDraggedWithParentStart(args, argc); return true;
        case SYM_GEN_finishMoveback_715: out = fn_finishMoveback(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_716: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_canSnap_717: out = fn_canSnap(args, argc); return true;
        case SYM_GEN_reactToDropResult_718: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_drop_719: out = fn_drop(args, argc); return true;
        case SYM_GEN_showClickArea_720: out = fn_showClickArea(args, argc); return true;
        case SYM_GEN_cancelDrag_721: out = fn_cancelDrag(args, argc); return true;
        case SYM_GEN_emptyTweenCallback_722: out = fn_emptyTweenCallback(args, argc); return true;
        case SYM_GEN_killMovebackTween_723: out = fn_killMovebackTween(args, argc); return true;
        case SYM_GEN_setSpriteGlobalPos_724: out = fn_setSpriteGlobalPos(args, argc); return true;
        case SYM_GEN_dropIntoInventory_725: out = fn_dropIntoInventory(args, argc); return true;
        case SYM_GEN_finishInsideItemsRotation_726: out = fn_finishInsideItemsRotation(args, argc); return true;
        case SYM_GEN_pushDraggedItemsToStorage_727: out = fn_pushDraggedItemsToStorage(args, argc); return true;
        case SYM_GEN_reparentItemsInside_728: out = fn_reparentItemsInside(args, argc); return true;
        case SYM_GEN_clearDraggedInsideItems_729: out = fn_clearDraggedInsideItems(args, argc); return true;
        case SYM_GEN_showSockets_730: out = fn_showSockets(args, argc); return true;
        case SYM_GEN_hideSockets_731: out = fn_hideSockets(args, argc); return true;
        case SYM_GEN_playPickupSound_732: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_147: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_canBeSold_733: out = fn_canBeSold(args, argc); return true;
        case SYM_GEN_isPickingPossible_734: out = fn_isPickingPossible(args, argc); return true;
        case SYM_GEN_canBePicked_735: out = fn_canBePicked(args, argc); return true;
        case SYM_GEN_canBeDraggedWithBag_736: out = fn_canBeDraggedWithBag(args, argc); return true;
        case SYM_GEN_canBeDropped_737: out = fn_canBeDropped(args, argc); return true;
        case SYM_GEN__input_738: out = fn__input(args, argc); return true;
        case SYM_GEN_resetSprite_739: out = fn_resetSprite(args, argc); return true;
        case SYM_GEN_combatToShop_740: out = fn_combatToShop(args, argc); return true;
        case SYM_GEN_shopEntered_741: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_startFusing_inShop_743: out = fn_startFusing_inShop(args, argc); return true;
        case SYM_GEN_getCraftingPriority_744: out = fn_getCraftingPriority(args, argc); return true;
        case SYM_GEN_addToCraftingQueue_745: out = fn_addToCraftingQueue(args, argc); return true;
        case SYM_GEN_combatToTitle_746: out = fn_combatToTitle(args, argc); return true;
        case SYM_GEN_readyToFuse_747: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_startFusing_748: out = fn_startFusing(args, argc); return true;
        case SYM_GEN_readyToTransform_749: out = fn_readyToTransform(args, argc); return true;
        case SYM_GEN_giveGold_750: out = fn_giveGold(args, argc); return true;
        case SYM_GEN_getTranslatedTypeName_751: out = fn_getTranslatedTypeName(args, argc); return true;
        case SYM_GEN_getTypeDescription_752: out = fn_getTypeDescription(args, argc); return true;
        case SYM_GEN_getTranslatedRarity_753: out = fn_getTranslatedRarity(args, argc); return true;
        case SYM_GEN_getRarityName_754: out = sf_getRarityName(gd_ctx, args, argc); return true;
        case SYM_GEN_logCooldown_755: out = fn_logCooldown(args, argc); return true;
        case SYM_GEN_getCombatDisplayAccuracy_756: out = fn_getCombatDisplayAccuracy(args, argc); return true;
        case SYM_GEN_getDisplayCritChance_757: out = fn_getDisplayCritChance(args, argc); return true;
        case SYM_GEN_getSalesMultiplier_758: out = fn_getSalesMultiplier(args, argc); return true;
        case SYM_GEN_prepareDiscard_759: out = fn_prepareDiscard(args, argc); return true;
        case SYM_GEN_discard_760: out = fn_discard(args, argc); return true;
        case SYM_GEN_popIn_761: out = fn_popIn(args, argc); return true;
        case SYM_GEN_disappear_762: out = fn_disappear(args, argc); return true;
        case SYM_GEN_appearInLibrary_763: out = fn_appearInLibrary(args, argc); return true;
        case SYM_GEN_createParticles_764: out = fn_createParticles(args, argc); return true;
        case SYM_GEN_deactivateParticles_765: out = fn_deactivateParticles(args, argc); return true;
        case SYM_GEN_makeRigidBody_766: out = fn_makeRigidBody(args, argc); return true;
        case SYM_GEN_dropImpulse_767: out = fn_dropImpulse(args, argc); return true;
        case SYM_GEN_makeNonRigidBody_768: out = fn_makeNonRigidBody(args, argc); return true;
        case SYM_GEN_rollShopChance_769: out = fn_rollShopChance(args, argc); return true;
        case SYM_GEN__physics_process_770: out = fn__physics_process(args, argc); return true;
        case SYM_GEN_playActivationAnimation_Scale_771: out = fn_playActivationAnimation_Scale(args, argc); return true;
        case SYM_GEN_playActivationAnimation_Jump_772: out = fn_playActivationAnimation_Jump(args, argc); return true;
        case SYM_GEN_playActivationAnimation_JumpSquash_773: out = fn_playActivationAnimation_JumpSquash(args, argc); return true;
        case SYM_GEN_playActivationAnimation_774: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_playActivationSound_146: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN_clearSpriteMaterial_775: out = fn_clearSpriteMaterial(args, argc); return true;
        case SYM_GEN_giveProgressMaterial_776: out = fn_giveProgressMaterial(args, argc); return true;
        case SYM_GEN_getTextureSize_777: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN_scaleToFit_778: out = fn_scaleToFit(args, argc); return true;
        case SYM_GEN_getSpriteOffset_779: out = fn_getSpriteOffset(args, argc); return true;
        case SYM_GEN_getGlobalCenter_780: out = fn_getGlobalCenter(args, argc); return true;
        case SYM_GEN_getTextureSize_local_781: out = fn_getTextureSize_local(args, argc); return true;
        case SYM_GEN_scaleToFit_local_782: out = fn_scaleToFit_local(args, argc); return true;
        case SYM_GEN_getSpriteOffset_local_783: out = fn_getSpriteOffset_local(args, argc); return true;
        case SYM_GEN_setTexture_784: out = fn_setTexture(args, argc); return true;
        case SYM_GEN_updateShadowTexture_785: out = fn_updateShadowTexture(args, argc); return true;
        case SYM_GEN_initSpriteMaterial_786: out = fn_initSpriteMaterial(args, argc); return true;
        case SYM_GEN_updateShaderRotation_787: out = fn_updateShaderRotation(args, argc); return true;
        case SYM_GEN_allowCancelShaderTween_788: out = fn_allowCancelShaderTween(args, argc); return true;
        case SYM_GEN_showCooldownSmooth_789: out = fn_showCooldownSmooth(args, argc); return true;
        case SYM_GEN_showCooldown_790: out = fn_showCooldown(args, argc); return true;
        case SYM_GEN_createAnimation_791: out = fn_createAnimation(args, argc); return true;
        case SYM_GEN_playAnimation_792: out = fn_playAnimation(args, argc); return true;
        case SYM_GEN_hasInventoryDuration_793: out = fn_hasInventoryDuration(args, argc); return true;
        case SYM_GEN_reveal_794: out = fn_reveal(args, argc); return true;
        case SYM_GEN_setRevealed_795: out = fn_setRevealed(args, argc); return true;
        case SYM_GEN_isCrafted_796: out = fn_isCrafted(args, argc); return true;
        case SYM_GEN_isMovingBack_797: out = fn_isMovingBack(args, argc); return true;
        case SYM_GEN__notification_798: out = fn__notification(args, argc); return true;
        case SYM_GEN_getAllInInventoryOfType_799: out = fn_getAllInInventoryOfType(args, argc); return true;
        case SYM_GEN_countAllInInventoryOfType_800: out = fn_countAllInInventoryOfType(args, argc); return true;
        case SYM_GEN_isTypeInInventory_801: out = fn_isTypeInInventory(args, argc); return true;
        case SYM_GEN_isRecipeFinished_802: out = fn_isRecipeFinished(args, argc); return true;
        case SYM_GEN_canStartNewRecipe_803: out = fn_canStartNewRecipe(args, argc); return true;
        case SYM_GEN_getRecipes_804: out = fn_getRecipes(args, argc); return true;
        case SYM_GEN_breakBondVisual_805: out = fn_breakBondVisual(args, argc); return true;
        case SYM_GEN_removeBondedBaseItem_806: out = fn_removeBondedBaseItem(args, argc); return true;
        case SYM_GEN_removeBondedIngredient_807: out = fn_removeBondedIngredient(args, argc); return true;
        case SYM_GEN_removeAllIngredients_808: out = fn_removeAllIngredients(args, argc); return true;
        case SYM_GEN_considerAsBond_809: out = fn_considerAsBond(args, argc); return true;
        case SYM_GEN_addBondedIngredient_810: out = fn_addBondedIngredient(args, argc); return true;
        case SYM_GEN_addToBaseItem_811: out = fn_addToBaseItem(args, argc); return true;
        case SYM_GEN_playBondAnimation_812: out = fn_playBondAnimation(args, argc); return true;
        case SYM_GEN_playBondFailedAnimation_813: out = fn_playBondFailedAnimation(args, argc); return true;
        case SYM_GEN_isCatalystBond_814: out = fn_isCatalystBond(args, argc); return true;
        case SYM_GEN_isLocked_815: out = fn_isLocked(args, argc); return true;
        case SYM_GEN_canLockBag_816: out = fn_canLockBag(args, argc); return true;
        case SYM_GEN_canBeLocked_817: out = fn_canBeLocked(args, argc); return true;
        case SYM_GEN_setLocked_818: out = fn_setLocked(args, argc); return true;
        case SYM_GEN_unlockCombining_819: out = fn_unlockCombining(args, argc); return true;
        case SYM_GEN_lockCombining_820: out = fn_lockCombining(args, argc); return true;
        case SYM_GEN_showLockLabel_821: out = fn_showLockLabel(args, argc); return true;
        case SYM_GEN_getLockPosition_822: out = fn_getLockPosition(args, argc); return true;
        case SYM_GEN_setBoundAsIngredient_823: out = fn_setBoundAsIngredient(args, argc); return true;
        case SYM_GEN_canPreviewFusions_824: out = fn_canPreviewFusions(args, argc); return true;
        case SYM_GEN_getCraftingPreviewPosition_825: out = fn_getCraftingPreviewPosition(args, argc); return true;
        case SYM_GEN_previewFusions_826: out = fn_previewFusions(args, argc); return true;
        case SYM_GEN_previewRecipeIngredients_827: out = fn_previewRecipeIngredients(args, argc); return true;
        case SYM_GEN_previewFusionToItem_828: out = fn_previewFusionToItem(args, argc); return true;
        case SYM_GEN_hasShopItemCraftCandidates_829: out = fn_hasShopItemCraftCandidates(args, argc); return true;
        case SYM_GEN_typeInIngredients_830: out = fn_typeInIngredients(args, argc); return true;
        case SYM_GEN_getTextEffect_831: out = fn_getTextEffect(args, argc); return true;
        case SYM_GEN_getFusionItemName_832: out = fn_getFusionItemName(args, argc); return true;
        case SYM_GEN_showProgressLabel_833: out = fn_showProgressLabel(args, argc); return true;
        case SYM_GEN_onCraftingLabelReturned_834: out = fn_onCraftingLabelReturned(args, argc); return true;
        case SYM_GEN_createBondVisual_835: out = fn_createBondVisual(args, argc); return true;
        case SYM_GEN_updateBondVisuals_836: out = fn_updateBondVisuals(args, argc); return true;
        case SYM_GEN_fuse_837: out = fn_fuse(args, argc); return true;
        case SYM_GEN_onFusingAsIngredient_838: out = fn_onFusingAsIngredient(args, argc); return true;
        case SYM_GEN_onFusingAsCatalystFinished_839: out = fn_onFusingAsCatalystFinished(args, argc); return true;
        case SYM_GEN_createCraftedShockwave_840: out = fn_createCraftedShockwave(args, argc); return true;
        case SYM_GEN_finishFusing_841: out = fn_finishFusing(args, argc); return true;
        case SYM_GEN_allowGeneratingFusionItem_842: out = fn_allowGeneratingFusionItem(args, argc); return true;
        case SYM_GEN_catalystFusingFinished_843: out = fn_catalystFusingFinished(args, argc); return true;
        case SYM_GEN_onFusingFinished_844: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_onCraftedFrom_845: out = fn_onCraftedFrom(args, argc); return true;
        case SYM_GEN_getCraftingOffset_846: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN_playCraftedAnimation_847: out = fn_playCraftedAnimation(args, argc); return true;
        case SYM_GEN_onRestoreSnapshot_848: out = fn_onRestoreSnapshot(args, argc); return true;
        case SYM_GEN_getShopPriority_849: out = fn_getShopPriority(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Item::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getNumTooltipStats_620: out = sf_getNumTooltipStats(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumStackChangeTypes_621: out = sf_getNumStackChangeTypes(gd_ctx, args, argc); return true;
        case SYM_GEN_wasAddedToInventory_655: out = sf_wasAddedToInventory(gd_ctx, args, argc); return true;
        case SYM_GEN_wasBought_656: out = sf_wasBought(gd_ctx, args, argc); return true;
        case SYM_GEN_wasHotSwap_657: out = sf_wasHotSwap(gd_ctx, args, argc); return true;
        case SYM_GEN_getRarityName_754: out = sf_getRarityName(gd_ctx, args, argc); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Item::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__CoreItem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_hasPreDealDamageEarlyEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_early", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasPreDealDamageLateEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_late", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasDealtDamageEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDealtDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeReceivedEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeReceived", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeLeftEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeLeft", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_getNumTooltipStats(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_getNumStackChangeTypes(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_867), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_preset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initPhysicsMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getShadowOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Shop_2578))))) {
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_shop_520);
    }
    else {
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_521);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initRecipeBook(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initItemLibrary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setSpotlight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__spotlight = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hoverEnd_709, nullptr, 0);
    if (gd::gd_truth(this->f_spotlight)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHover_691, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHoverEnd_700, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initTitle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initBuildViewer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initBuildViewerIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initInfoPanelIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initGridStorageIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initBuildViewerIcon_631, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_persistDataInShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTranslatedName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_removeLinebreaks = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(false));
    if (gd::gd_truth(lv_removeLinebreaks)) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedName_637, nullptr, 0), gd::SYM_replace, _ca, 2); })();
    }
    else {
        return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedName_637, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getDescription_638, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_requiredItem_2617), gd::GdVal::null())))) {
        gd::GdVal lv_requiredStr = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "itemName", 8u)), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_requiredItem_2617), SYM_GEN_getTranslatedName_637, nullptr, 0)); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TOOLTIP_Requires", 16u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })(), SYM_GEN_format_2619, _ca, 1); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$t", 2u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_begins_with, _ca, 1); })())) {
            lv_descr = gd::gd_add(gd_ctx, lv_requiredStr, lv_descr);
        }
        else {
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_requiredStr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), lv_descr}; return gd::gd_str_fn(gd_ctx.arena, _ca, 3); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_639, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_insertParameters(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_wrapInColor = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_150, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(lv_wrapInColor)) : gd::GdVal::from_bool(false)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$dam", 4u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1577)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_paramColor_2620)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_wrapInColor_fixed_2621, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    {
        gd::GdVal _t423 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_extraCds_1582), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
        gd::GdArr* _t424 = (_t423.kind == gd::GdVal::Kind::Arr) ? _t423.arr : nullptr;
        uint32_t _len__t425 = _t424 ? _t424->len : 0u;
        for (uint32_t _t425 = 0; _t425 < _len__t425; ++_t425) {
            gd::GdVal lv_i = _t424->data[_t425];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })(), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldownIndex_103, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_276, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_102, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_276, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance2", 7u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance2Modified_279, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance", 6u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance1Modified_278, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "shopchance", 10u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getShopChance_235, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_110, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStaminaModified_111, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    {
        gd::GdVal _t426 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_params_1477), gd::SYM_size, nullptr, 0));
        gd::GdArr* _t427 = (_t426.kind == gd::GdVal::Kind::Arr) ? _t426.arr : nullptr;
        uint32_t _len__t428 = _t427 ? _t427->len : 0u;
        for (uint32_t _t428 = 0; _t428 < _len__t428; ++_t428) {
            gd::GdVal lv_i = _t427->data[_t428];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p", 1u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))))), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
        }
    }
    {
        gd::GdVal _t429 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_sortedParamNames_1613));
        gd::GdArr* _t430 = (_t429.kind == gd::GdVal::Kind::Arr) ? _t429.arr : nullptr;
        uint32_t _len__t431 = _t430 ? _t430->len : 0u;
        for (uint32_t _t431 = 0; _t431 < _len__t431; ++_t431) {
            gd::GdVal lv_paramName = _t430->data[_t431];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_", 2u)), lv_paramName), ([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
        }
    }
    if (gd::gd_truth(lv_wrapInColor)) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$block", 6u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0))), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_paramColor_2620)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_wrapInColor_fixed_2621, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_insertParameter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_modified = (_argc > 3) ? _args[3] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547));
    gd::GdVal lv_checkZero = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_wrapInColor = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(true));
    lv_value = gd::gd_stepify(lv_value, gd::GdVal::from_float(0.01));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_value, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_checkZero))))))) {
        gd::GdVal lv_replacedString = gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$", 1u)), lv_paramName);
        gd::GdVal lv_startPos = ([&]() { gd::GdVal _ca[] = {lv_replacedString}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_find, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_startPos, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
            gd::GdVal lv_refEndPos = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, lv_startPos, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_findHighlightEnd_2622, _ca, 2); })();
            gd::GdVal lv_unit = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_startPos, gd::call_method(gd_ctx, lv_replacedString, gd::SYM_length, nullptr, 0)), gd::gd_sub(gd::gd_sub(lv_refEndPos, gd::gd_add(gd_ctx, lv_startPos, gd::GdVal::from_int(1LL))), gd::call_method(gd_ctx, lv_paramName, gd::SYM_length, nullptr, 0))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_substr, _ca, 2); })();
            gd::GdVal lv_replacement = gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_value)), lv_unit);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_startPos, gd::GdVal::from_int(0LL))))) {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, lv_descr, gd::gd_sub(lv_startPos, gd::GdVal::from_int(1LL))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "+", 1u)))))) {
                    lv_replacedString = gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "+", 1u)), lv_replacedString);
                    lv_replacement = gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "+", 1u)), lv_replacement);
                }
                else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, lv_descr, gd::gd_sub(lv_startPos, gd::GdVal::from_int(1LL))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "-", 1u)))))) {
                    lv_replacedString = gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "-", 1u)), lv_replacedString);
                    lv_replacement = gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "-", 1u)), lv_replacement);
                }
            }
            if (gd::gd_truth(lv_wrapInColor)) {
                lv_replacement = ([&]() { gd::GdVal _ca[] = {lv_replacement, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_statColors_2623), lv_modified)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_wrapInColor_fixed_2621, _ca, 2); })();
            }
            lv_descr = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_replacedString, lv_unit), lv_replacement}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        }
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getModeDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_text = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_colors = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_center = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    lv_center = gd::gd_coerce_bool(lv_center);
    gd::GdVal lv_wrapInColor = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(true));
    lv_wrapInColor = gd::gd_coerce_bool(lv_wrapInColor);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getFlavorText(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getFlavorText_642, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_disablePicking(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_enablePicking(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_enableTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_disableTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_disableFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_focus)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseFocus_699, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_enableFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setEditMode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_active = gd::gd_coerce_bool(lv_active);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setShadowAlpha(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_alpha = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_alpha = gd::gd_coerce_float(lv_alpha);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTopLeftGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getBottomRightGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getBottomCenter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        return this->f_inventory;
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_wasAddedToInventory(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_AddedToInventory_2624)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_Hotswap_2625))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_wasBought(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__Item::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_655, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_AddedToStorageBox_2626))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_Socketed_2627))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_SocketHotswap_2628))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_wasHotSwap(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_Hotswap_2625)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_SocketHotswap_2628))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playAffectedPlacedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newItemIsAffected = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_sum = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t432 = gd::gd_iter_seq(gd_ctx.arena, lv_newItemIsAffected);
        gd::GdArr* _t433 = (_t432.kind == gd::GdVal::Kind::Arr) ? _t432.arr : nullptr;
        uint32_t _len__t434 = _t433 ? _t433->len : 0u;
        for (uint32_t _t434 = 0; _t434 < _len__t434; ++_t434) {
            gd::GdVal lv_color = _t433->data[_t434];
            lv_sum = gd::gd_add(gd_ctx, lv_sum, gd::gd_coerce_int(gd::get_index(gd_ctx, lv_newItemIsAffected, lv_color)));
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_sum, gd::GdVal::from_int(1LL))))) {
    }
    else if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580)))) {
    }
    else if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)))) {
    }
    else if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Tertiary_2583)))) {
    }
    else if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611)))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearCanAffectVisuals(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_liesInStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerStorageBox_2579)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_dragged)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_pushToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetPos = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_addImpulse = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_tweenBouncyness = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    gd::GdVal lv_checkCollisions = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_targetPos = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_speed = (_argc > 4) ? _args[4] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_secondCheck = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeFromStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killMovebackTween_723, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStorageLeft_665, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onStorageLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isInGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getGridStorageProxy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onAddedToGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onRemovedFromGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_makeGrabbable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_extended = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_extended = gd::gd_coerce_bool(lv_extended);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_moveToFreeSpaceInStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetPos = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_addImpulse = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_speed = (_argc > 2) ? _args[2] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_secondCheck = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_tweenBouncyness = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_checkIfOutofStorageBounds(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkIfOutofStorageBounds2", 26u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callNextFrame_1701, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_checkIfOutofStorageBounds2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkIfOutofStorageBounds3", 26u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callNextFrame_1701, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_checkIfOutofStorageBounds3(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_findFreeSpace(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_startPos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_unclip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onAddedToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__integrate_forces(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_state, SYM_GEN_get_contact_count_2629, nullptr, 0), gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateShadow(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_lerpAngle_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_interpolationPoint = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_from = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_to = (_argc > 2) ? _args[2] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateInsideRotationNode_682, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_680, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateInsideRotationNode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_insideRotationNode, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_spawnRotationSparks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotateRight = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_highlight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_unhighlight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_739, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setBright(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_resetBright(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getHoverPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_523);
    }
    else {
        return gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canGainFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_gainFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canGainFocus_689, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerInventory_2554)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Socket_2589))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Opponent_2544)))))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_highlightItem_2630, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHover_691, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_respondToHover(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canShowBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
        return gd::GdVal::from_bool(false);
    }
    gd::GdVal lv_effectiveOwner = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEffectiveOwnerType_255, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Tooltip_2615)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_owningBuildIntoRecipesTooltip, gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canShowSubBuildIntoRecipesTooltip_693, nullptr, 0))))) {
            return gd::GdVal::from_bool(false);
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Shop_2578)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_ItemLibrary_2613))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(lv_effectiveOwner, this->f_ownerTypesWithBuildTooltip)))))))) {
        return gd::GdVal::from_bool(false);
    }
    gd::GdVal lv_descr = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRecipeDescriptor_697, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_descr, SYM_GEN_getNumRecipes_2631, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRelatedItems_457, nullptr, 0), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(true);
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canShowSubBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(5LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(150LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRecipeDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_descriptor;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hideBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_buildIntoRecipesTooltip, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_loseFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_focus)))) {
        return gd::GdVal::null();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHoverEnd_700, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_respondToHoverEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_activateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t435 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t436 = (_t435.kind == gd::GdVal::Kind::Arr) ? _t435.arr : nullptr;
        uint32_t _len__t437 = _t436 ? _t436->len : 0u;
        for (uint32_t _t437 = 0; _t437 < _len__t437; ++_t437) {
            gd::GdVal lv_specificParticles = _t436->data[_t437];
            (void)gd::call_method(gd_ctx, lv_specificParticles, SYM_GEN_activate_148, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_deactivateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t438 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t439 = (_t438.kind == gd::GdVal::Kind::Arr) ? _t438.arr : nullptr;
        uint32_t _len__t440 = _t439 ? _t439->len : 0u;
        for (uint32_t _t440 = 0; _t440 < _len__t440; ++_t440) {
            gd::GdVal lv_specificParticles = _t439->data[_t440];
            (void)gd::call_method(gd_ctx, lv_specificParticles, SYM_GEN_deactivate_2632, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_queueTooltipUpdate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hideBuildIntoRecipesTooltip_698, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearCanAffectVisuals_660, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_mouseEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hover(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_mouseExited(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hoverEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isHovered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_hovered) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_dragged)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getScaleProp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_hasSquishySprite)) {
        return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "baseScale", 9u));
    }
    else {
        return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "scale", 5u));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setSpriteScale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newScale = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasSquishySprite)) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_pickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_862), SYM_GEN_Grabbed_2633));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onDraggedWithParentStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_parentItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_715, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_finishMoveback(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canSnap(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::call_method(gd_ctx, this->f_draggedInsideItems, gd::SYM_empty, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_draggingParent, gd::GdVal::null())))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_result = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_drop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showClickArea(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_cancelDrag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_emptyTweenCallback(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_killMovebackTween(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showClickArea_720, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setSpriteGlobalPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_680, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_dropIntoInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hotswap = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_finishInsideItemsRotation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_pushDraggedItemsToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t441 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t442 = (_t441.kind == gd::GdVal::Kind::Arr) ? _t441.arr : nullptr;
        uint32_t _len__t443 = _t442 ? _t442->len : 0u;
        for (uint32_t _t443 = 0; _t443 < _len__t443; ++_t443) {
            gd::GdVal lv_item = _t442->data[_t443];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_pushToStorage_662, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_477, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_729, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_reparentItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t444 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t445 = (_t444.kind == gd::GdVal::Kind::Arr) ? _t444.arr : nullptr;
        uint32_t _len__t446 = _t445 ? _t445->len : 0u;
        for (uint32_t _t446 = 0; _t446 < _len__t446; ++_t446) {
            gd::GdVal lv_item = _t445->data[_t446];
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_477, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_729, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearDraggedInsideItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t447 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t448 = (_t447.kind == gd::GdVal::Kind::Arr) ? _t447.arr : nullptr;
        uint32_t _len__t449 = _t448 ? _t448->len : 0u;
        for (uint32_t _t449 = 0; _t449 < _len__t449; ++_t449) {
            gd::GdVal lv_item = _t448->data[_t449];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_onDraggedWithParentEnd_716, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hideSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeSold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerInventory_2554)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerStorageBox_2579))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Socket_2589))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isPickingPossible(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBePicked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(this->f_focus) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isPickingPossible_734, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1380), this->f_dropFrame)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeDraggedWithBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_dragged) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1380), this->f_pickupFrame)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__input(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_resetSprite(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_combatToShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_249, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_646, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_739, nullptr, 0);
        (void)gd::call_method(gd_ctx, this->f_cachedAffectedItems, gd::SYM_clear, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1581));
    this->f_speedScale = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMinDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    {
        gd::GdVal _t450 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffPowers);
        gd::GdArr* _t451 = (_t450.kind == gd::GdVal::Kind::Arr) ? _t450.arr : nullptr;
        uint32_t _len__t452 = _t451 ? _t451->len : 0u;
        for (uint32_t _t452 = 0; _t452 < _len__t452; ++_t452) {
            gd::GdVal lv_buff = _t451->data[_t452];
            { gd::GdVal _t453 = this->f_buffPowers; gd::GdVal _t454 = lv_buff; gd::set_index(gd_ctx, _t453, _t454, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t455 = this->f_buffAmplificationChances; gd::GdVal _t456 = lv_buff; gd::set_index(gd_ctx, _t455, _t456, gd::GdVal::from_float(0.0)); }
        }
    }
    this->f_critChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critSeverity = gd::gd_coerce_float(Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_BASE_CRIT_SEVERITY_0));
    this->f_bonusChancePercent_mult = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusAccuracy = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleActivationChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleAttackEffectChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)gd::call_method(gd_ctx, this->f_paramMult, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_paramAdd, gd::SYM_clear, nullptr, 0);
    this->f_numCharges = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::call_method(gd_ctx, this->f_statDisplayOverrides, gd::SYM_fill, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, this->f_itemMetrics, gd::SYM_fill, _ca, 1); })();
    this->f_consumed = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_enablePicking_644, nullptr, 0);
    {
        gd::GdVal _t457 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_495, nullptr, 0));
        gd::GdArr* _t458 = (_t457.kind == gd::GdVal::Kind::Arr) ? _t457.arr : nullptr;
        uint32_t _len__t459 = _t458 ? _t458->len : 0u;
        for (uint32_t _t459 = 0; _t459 < _len__t459; ++_t459) {
            gd::GdVal lv_gem = _t458->data[_t459];
            (void)([&]() { gd::GdVal _ca[] = {lv_craft}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN_shopEntered_741, _ca, 1); })();
        }
    }
    if (gd::gd_truth(lv_craft)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addToCraftingQueue_745, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onShopEntered_742, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_startFusing_inShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_COG_600)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFusing_748, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCraftingPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isGem_82, nullptr, 0))) {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_853), SYM_GEN_Gem_2634);
    }
    {
        gd::GdVal _t460 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
        gd::GdArr* _t461 = (_t460.kind == gd::GdVal::Kind::Arr) ? _t460.arr : nullptr;
        uint32_t _len__t462 = _t461 ? _t461->len : 0u;
        for (uint32_t _t462 = 0; _t462 < _len__t462; ++_t462) {
            gd::GdVal lv_bonded = _t461->data[_t462];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_bonded, SYM_GEN_isGem_82, nullptr, 0))) {
                return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_853), SYM_GEN_Mixed_2635);
            }
        }
    }
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_853), SYM_GEN_NonGem_2636);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addToCraftingQueue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_combatToTitle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_249, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_646, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_curRecipe) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2637, _ca, 1); })(), gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_startFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delay = (_argc > 0) ? _args[0] : (Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_599));
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_readyToFuse_747, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fuse", 4u)), lv_delay}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callDelayed_1416, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disablePicking_643, nullptr, 0);
        {
            gd::GdVal _t463 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
            gd::GdArr* _t464 = (_t463.kind == gd::GdVal::Kind::Arr) ? _t463.arr : nullptr;
            uint32_t _len__t465 = _t464 ? _t464->len : 0u;
            for (uint32_t _t465 = 0; _t465 < _len__t465; ++_t465) {
                gd::GdVal lv_bonded = _t464->data[_t465];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_curRecipe, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_bonded}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2638, _ca, 1); })()))))))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bonded, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "disablePicking", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1418, _ca, 3); })();
                    gd::set_prop(gd_ctx, lv_bonded, SYM_GEN_willBeConsumed_604, gd::GdVal::from_bool(true));
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_readyToTransform(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_giveGold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTranslatedTypeName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedTypeName_751, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTypeDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TYPE_", 5u)), gd::get_index(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), gd::SYM_keys, nullptr, 0), lv_type)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_DESCR", 6u)))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTranslatedRarity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_234, nullptr, 0)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__Item::call_static_fn(gd_ctx, SYM_GEN_getRarityName_754, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_getRarityName(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__rarity = gd::gd_coerce_int(lv__rarity);
    return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_logCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCombatDisplayAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_acc = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAccuracy_192, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_acc, gd::GdVal::from_int(100LL))))) {
        return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, ">100", 4u));
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_acc, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "<0", 2u));
    }
    else {
        return gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_acc));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getDisplayCritChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_c = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCritChancePercent_176, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_c, gd::GdVal::from_int(100LL))))) {
        return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, ">100", 4u));
    }
    else {
        return gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::gd_stepify(lv_c, gd::GdVal::from_float(0.1))));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getSalesMultiplier(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_float(1.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_prepareDiscard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_popIn(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_withParticles = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_withParticles = gd::gd_coerce_bool(lv_withParticles);
    gd::GdVal lv_speed = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_jump = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_disappear(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_appearInLibrary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_createParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_scene = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_baseScale = (_argc > 1) ? _args[1] : (gd::GdVal::from_vec2(1.0, 1.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_deactivateParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_makeRigidBody(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_dropImpulse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_direction = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_tweenBouncyness = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_makeNonRigidBody(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_rollShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_shopChance = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_shopChance_1585));
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__physics_process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_isStunned_1151, nullptr, 0))))) {
        this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_triggerTime, gd::gd_mul(lv_delta, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_90, nullptr, 0))));
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_triggerTime, this->f_iterationCooldown))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldown_790, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_triggerTime, gd::GdVal::from_int(0LL))))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_141, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation_Scale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxScale = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation_Jump(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_height = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(1.0));
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation_JumpSquash(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_height = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_intensity = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.2));
    gd::GdVal lv_longScale = gd::gd_add(gd_ctx, gd::GdVal::from_float(1.0), lv_intensity);
    gd::GdVal lv_shortScale = gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), lv_longScale);
    gd::GdVal lv_scaling = gd::GdVal::from_vec2(0.0, 0.0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN)))))))) {
        lv_scaling = gd::GdVal::from_vec2((lv_shortScale).as_float(), (lv_longScale).as_float());
    }
    else {
        lv_scaling = gd::GdVal::from_vec2((lv_longScale).as_float(), (lv_shortScale).as_float());
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1619));
    gd::GdVal lv_consume = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_consume = gd::gd_coerce_bool(lv_consume);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_739, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Jump_2639))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_772, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_SquishyJump_2640))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.1)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_773, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_VerySquishyJump_2641))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.2)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_773, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Slash_2642))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Stab_2643))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_ReverseStab_2644))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Bonk_2645))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_ReverseBonk_2646))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Sweep_2647))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Block_2563))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL), gd::GdVal::from_float(1.3)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_772, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Chop_2648))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Wave_2649))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Throw_2607))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Scale_2650))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Scale_771, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Squish_2651))))) {
        if (gd::gd_truth(this->f_hasSquishySprite)) {
        }
        else {
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Potion_2652))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Hiss_2653))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Spin_2654))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Tackle_2655))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_DoubleSlash_2656))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Struggle_2657))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_772, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Shoot_2658))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Flash_2659))))) {
    }
    if (gd::gd_truth(lv_consume)) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(6LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playDropSound_147, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearSpriteMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_giveProgressMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTextureSize(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_scaleToFit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxSize = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getSpriteOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getGlobalCenter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTextureSize_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_scaleToFit_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxSize = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getSpriteOffset_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newTex = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initSpriteMaterial_786, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateShadowTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initSpriteMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateShaderRotation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_allowCancelShaderTween(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showCooldownSmooth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_progress = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    gd::GdVal lv_fill = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_fill = gd::gd_coerce_bool(lv_fill);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_canCancelShaderTween)))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(lv_fill)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_progress = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_createAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hit = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_hit = gd::gd_coerce_bool(lv_hit);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1597))))) {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hasInventoryDuration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1485, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_reveal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setRevealed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reveal_794, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isCrafted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isCraftedItem_1622, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isMovingBack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__notification(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_what = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_what = gd::gd_coerce_int(lv_what);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getAllInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_249, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getItemsInInventoryOfType_opponent_1569, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getItemsInInventoryOfType_1568, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_countAllInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_249, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_countItemsInInventoryOfType_opponent_1571, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_countItemsInInventoryOfType_1570, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isTypeInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_249, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_isItemInInventory_opponent_1574, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_isItemInInventory_1573, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isRecipeFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2637, _ca, 1); })(), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canStartNewRecipe(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBaseItem_256, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isAvailableForCrafting_491, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRecipes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_checkClassAvailability = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_recipes = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t466 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_recipes_2660));
        gd::GdArr* _t467 = (_t466.kind == gd::GdVal::Kind::Arr) ? _t466.arr : nullptr;
        uint32_t _len__t468 = _t467 ? _t467->len : 0u;
        for (uint32_t _t468 = 0; _t468 < _len__t468; ++_t468) {
            gd::GdVal lv_recipe = _t467->data[_t468];
            (void)([&]() { gd::GdVal _ca[] = {lv_recipe}; return gd::call_method(gd_ctx, lv_recipes, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return lv_recipes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_breakBondVisual(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_bondIndex = ([&]() { gd::GdVal _ca[] = {lv_toItem}; return gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_find, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_bondIndex, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeBondedBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_823, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeBondedIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_breakBondVisual_805, _ca, 1); })();
    if (gd::gd_truth(this->f_fusing)) {
        return gd::GdVal::null();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_833, nullptr, 0);
    if (gd::gd_truth(gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_empty, nullptr, 0))) {
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_836, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeAllIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_833, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_considerAsBond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_neighbor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_score = gd::GdVal::from_float(0.0);
    gd::GdVal lv_recipe = gd::GdVal::null();
    if (gd::gd_truth(this->f_curRecipe)) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isRecipeFinished_802, nullptr, 0))) {
            return gd::GdVal::null();
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients, lv_neighbor}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_checkNeighbor_2661, _ca, 2); })())) {
            gd::GdVal lv_progressBefore = ([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2637, _ca, 1); })();
            gd::GdVal lv_progressWithNeighbor = gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)), gd::gd_coerce_float(gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getNumIngredients_2662, nullptr, 0)));
            lv_score = gd::gd_add(gd_ctx, lv_progressWithNeighbor, gd::gd_mul(gd::GdVal::from_float(0.1), lv_progressBefore));
            lv_recipe = this->f_curRecipe;
        }
    }
    else {
        gd::GdVal lv_bestScore = gd::GdVal::from_float(0.0);
        {
            gd::GdVal _t469 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRecipes_804, nullptr, 0));
            gd::GdArr* _t470 = (_t469.kind == gd::GdVal::Kind::Arr) ? _t469.arr : nullptr;
            uint32_t _len__t471 = _t470 ? _t470->len : 0u;
            for (uint32_t _t471 = 0; _t471 < _len__t471; ++_t471) {
                gd::GdVal lv_r = _t470->data[_t471];
                if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), lv_neighbor}; return gd::call_method(gd_ctx, lv_r, SYM_GEN_checkNeighbor_2661, _ca, 2); })())) {
                    gd::GdVal lv_s = gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), gd::call_method(gd_ctx, lv_r, SYM_GEN_getNumIngredients_2662, nullptr, 0));
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_s, lv_bestScore)))) {
                        lv_bestScore = lv_s;
                        lv_recipe = lv_r;
                    }
                }
            }
        }
        lv_score = lv_bestScore;
    }
    if (gd::gd_truth(lv_recipe)) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_recipe, lv_score}));
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addBondedIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forRecipe = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_neighbor = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_curRecipe)) {
    }
    else {
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createBondVisual_835, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_836, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_812, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, lv_neighbor, SYM_GEN_placedByPlayer_48)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_placedByPlayer))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_833, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addToBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_823, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_812, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playBondAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_catalyst = gd::GdVal::from_bool(false);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_bondedBaseItem, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_bondedBaseItem, SYM_GEN_curRecipe_573), gd::GdVal::null())))) {
            lv_catalyst = gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_bondedBaseItem, SYM_GEN_curRecipe_573), SYM_GEN_isCatalystRecipe_2663, nullptr, 0);
        }
    }
    else {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_curRecipe, gd::GdVal::null())))) {
            lv_catalyst = gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isCatalystRecipe_2663, nullptr, 0);
        }
    }
    if (gd::gd_truth(lv_catalyst)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playBondFailedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isCatalystBond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bondedItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_curRecipe, gd::GdVal::null())))) {
        return gd::GdVal::from_bool(false);
    }
    return ([&]() { gd::GdVal _ca[] = {lv_bondedItem}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2638, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_locked;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canLockBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__locked = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_showLabel = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_locked, lv__locked)))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(lv__locked)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_showLabel}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_lockCombining_820, _ca, 1); })();
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_unlockCombining_819, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_unlockCombining(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playAni = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_playAni = gd::gd_coerce_bool(lv_playAni);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_lockCombining(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_showLabel = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showLockLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getLockPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setBoundAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__bound = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__bound = gd::gd_coerce_bool(lv__bound);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canPreviewFusions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCraftingPreviewPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_previewFusions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_previewRecipeIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_previewFusionToItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hoveredIngredient = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hasShopItemCraftCandidates(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_typeInIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_candidate = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_ingredients = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t472 = gd::gd_iter_seq(gd_ctx.arena, lv_ingredients);
        gd::GdArr* _t473 = (_t472.kind == gd::GdVal::Kind::Arr) ? _t472.arr : nullptr;
        uint32_t _len__t474 = _t473 ? _t473->len : 0u;
        for (uint32_t _t474 = 0; _t474 < _len__t474; ++_t474) {
            gd::GdVal lv_ingredient = _t473->data[_t474];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_ingredient}; return gd::call_method(gd_ctx, lv_candidate, SYM_GEN_hasType_77, _ca, 1); })())) {
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTextEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_textEffect_2275);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getFusionItemName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_fusedItem_2664), SYM_GEN_getTranslatedName_637, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showProgressLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onCraftingLabelReturned(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_createBondVisual(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bondNeighbor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateBondVisuals(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_fuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onFusingAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onFusingAsCatalystFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearSpriteMaterial_775, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_823, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_createCraftedShockwave(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fusedItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_finishFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_allowGeneratingFusionItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_catalystFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_validBonds = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onCraftedFrom(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_ingredients = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playCraftedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_originPosition = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onRestoreSnapshot(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_715, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_Normal_2540);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Item(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Item>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Item = {CLS_Gd__gd_core__Item, "Item", "res://gd_core/Item.gd", &META_Gd__gd_core__CoreItem, false, _alloc_Gd__gd_core__Item, &Gd__gd_core__Item::get_static_prop_fn, &Gd__gd_core__Item::call_static_fn};

void Gd__gd_core__Weapon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Weapon::meta() const { return &META_Gd__gd_core__Weapon; }
gd::GdVal Gd__gd_core__Weapon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Weapon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Weapon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Weapon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Weapon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_attack_937: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Weapon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_attack_937: out = fn_attack(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Weapon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Weapon::fn_attack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Weapon::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attack_937, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Weapon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Weapon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Weapon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Weapon = {CLS_Gd__gd_core__Weapon, "Weapon", "res://gd_core/Weapon.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Weapon, &Gd__gd_core__Weapon::get_static_prop_fn, &Gd__gd_core__Weapon::call_static_fn};

void Gd__gd_core__CoreBuff__INNER__TemporaryStacks::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_amount = gd::GdVal::from_int(0);
    this->f_timeout = gd::GdVal::from_float(0.0);
    this->f_item = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreBuff__INNER__TemporaryStacks::meta() const { return &META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks; }
gd::GdVal Gd__gd_core__CoreBuff__INNER__TemporaryStacks::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_amount_1037: out = this->f_amount; return true;
        case SYM_GEN_timeout_1038: out = this->f_timeout; return true;
        case SYM_GEN_item_1039: out = this->f_item; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_amount_1037: this->f_amount = gd::gd_coerce_int(val); return true;
        case SYM_GEN_timeout_1038: this->f_timeout = gd::gd_coerce_float(val); return true;
        case SYM_GEN_item_1039: this->f_item = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreBuff__INNER__TemporaryStacks::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__timeout = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_amount = gd::gd_coerce_int(lv__amount);
    this->f_timeout = gd::gd_coerce_float(lv__timeout);
    this->f_item = lv__item;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreBuff__INNER__TemporaryStacks(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreBuff__INNER__TemporaryStacks>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks = {CLS_Gd__gd_core__CoreBuff__INNER__TemporaryStacks, "TemporaryStacks", "", nullptr, false, _alloc_Gd__gd_core__CoreBuff__INNER__TemporaryStacks, &Gd__gd_core__CoreBuff__INNER__TemporaryStacks::get_static_prop_fn, &Gd__gd_core__CoreBuff__INNER__TemporaryStacks::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreItemData_ReleaseState[] = {{"Demo", 0LL}, {"Full", 1LL}, {"Unreleased", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreItemData_ReleaseState = {"ReleaseState", _ekv_Gd__gd_core__CoreItemData_ReleaseState, 3u};
void Gd__gd_core__CoreItemData::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_name = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    this->f_identifier = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
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
    this->f_startsSubclass = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
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
    this->f_releaseState = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_ReleaseState_1629), SYM_GEN_Full_2665));
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
        case SYM_GEN_ReleaseState_1629: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreItemData_ReleaseState);
        case SYM_GEN_PARAM_DELIMITER_1612: return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_", 1u));
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
        case SYM_GEN_identifier_1575: out = this->f_identifier; return true;
        case SYM_GEN_itemIndex_1576: out = this->f_itemIndex; return true;
        case SYM_GEN_minDam_1577: out = this->f_minDam; return true;
        case SYM_GEN_maxDam_1578: out = this->f_maxDam; return true;
        case SYM_GEN_staminaCost_1579: out = this->f_staminaCost; return true;
        case SYM_GEN_block_1580: out = this->f_block; return true;
        case SYM_GEN_cd_1581: out = this->f_cd; return true;
        case SYM_GEN_extraCds_1582: out = this->f_extraCds; return true;
        case SYM_GEN_accuracy_1452: out = this->f_accuracy; return true;
        case SYM_GEN_canActivate_89: out = this->f_canActivate; return true;
        case SYM_GEN_chance_1583: out = this->f_chance; return true;
        case SYM_GEN_chance2_1584: out = this->f_chance2; return true;
        case SYM_GEN_shopChance_1585: out = this->f_shopChance; return true;
        case SYM_GEN_types_1451: out = this->f_types; return true;
        case SYM_GEN_tags_1586: out = this->f_tags; return true;
        case SYM_GEN_physics_1587: out = this->f_physics; return true;
        case SYM_GEN_rarity_1588: out = this->f_rarity; return true;
        case SYM_GEN_price_1589: out = this->f_price; return true;
        case SYM_GEN_classes_1590: out = this->f_classes; return true;
        case SYM_GEN_randomUniquePool_1591: out = this->f_randomUniquePool; return true;
        case SYM_GEN_hasBattleRageEffect_1592: out = this->f_hasBattleRageEffect; return true;
        case SYM_GEN_gatedItems_1593: out = this->f_gatedItems; return true;
        case SYM_GEN_startsSubclass_1594: out = this->f_startsSubclass; return true;
        case SYM_GEN_gateItem_1595: out = this->f_gateItem; return true;
        case SYM_GEN_originatingRecipes_1596: out = this->f_originatingRecipes; return true;
        case SYM_GEN_animationScene_1597: out = this->f_animationScene; return true;
        case SYM_GEN_flickerAni_1598: out = this->f_flickerAni; return true;
        case SYM_GEN_flickerMinDist_1599: out = this->f_flickerMinDist; return true;
        case SYM_GEN_flickerMaxDist_1600: out = this->f_flickerMaxDist; return true;
        case SYM_GEN_flickerMinSpeed_1601: out = this->f_flickerMinSpeed; return true;
        case SYM_GEN_flickerMaxSpeed_1602: out = this->f_flickerMaxSpeed; return true;
        case SYM_GEN_connectorReadyRoll_1603: out = this->f_connectorReadyRoll; return true;
        case SYM_GEN_gemRoll_1604: out = this->f_gemRoll; return true;
        case SYM_GEN_sceneDepth_1605: out = this->f_sceneDepth; return true;
        case SYM_GEN_releaseState_1606: out = this->f_releaseState; return true;
        case SYM_GEN__editor_1607: out = this->f__editor; return true;
        case SYM_GEN__playtest_1608: out = this->f__playtest; return true;
        case SYM_GEN__full_version_1609: out = this->f__full_version; return true;
        case SYM_GEN__engineer_test_1610: out = this->f__engineer_test; return true;
        case SYM_GEN_params_1477: out = this->f_params; return true;
        case SYM_GEN_namedParams_1611: out = this->f_namedParams; return true;
        case SYM_GEN_sortedParamNames_1613: out = this->f_sortedParamNames; return true;
        case SYM_GEN_paramBases_1614: out = this->f_paramBases; return true;
        case SYM_GEN_paramBases_inverted_1615: out = this->f_paramBases_inverted; return true;
        case SYM_GEN_gainedStacks_1616: out = this->f_gainedStacks; return true;
        case SYM_GEN_removedStacks_1617: out = this->f_removedStacks; return true;
        case SYM_GEN_usedStacks_1618: out = this->f_usedStacks; return true;
        case SYM_GEN_activationAni_1619: out = this->f_activationAni; return true;
        case SYM_GEN_ReleaseState_1629: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreItemData_ReleaseState); return true;
        case SYM_GEN_PARAM_DELIMITER_1612: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_name_7: this->f_name = val; return true;
        case SYM_GEN_identifier_1575: this->f_identifier = val; return true;
        case SYM_GEN_itemIndex_1576: this->f_itemIndex = gd::gd_coerce_int(val); return true;
        case SYM_GEN_minDam_1577: this->f_minDam = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxDam_1578: this->f_maxDam = gd::gd_coerce_int(val); return true;
        case SYM_GEN_staminaCost_1579: this->f_staminaCost = gd::gd_coerce_float(val); return true;
        case SYM_GEN_block_1580: this->f_block = gd::gd_coerce_int(val); return true;
        case SYM_GEN_cd_1581: this->f_cd = gd::gd_coerce_float(val); return true;
        case SYM_GEN_extraCds_1582: this->f_extraCds = val; return true;
        case SYM_GEN_accuracy_1452: this->f_accuracy = gd::gd_coerce_float(val); return true;
        case SYM_GEN_canActivate_89: this->f_canActivate = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_chance_1583: this->f_chance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_chance2_1584: this->f_chance2 = gd::gd_coerce_float(val); return true;
        case SYM_GEN_shopChance_1585: this->f_shopChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_types_1451: this->f_types = val; return true;
        case SYM_GEN_tags_1586: this->f_tags = gd::gd_coerce_int(val); return true;
        case SYM_GEN_physics_1587: this->f_physics = gd::gd_coerce_int(val); return true;
        case SYM_GEN_rarity_1588: this->f_rarity = gd::gd_coerce_int(val); return true;
        case SYM_GEN_price_1589: this->f_price = gd::gd_coerce_int(val); return true;
        case SYM_GEN_classes_1590: this->f_classes = gd::gd_coerce_int(val); return true;
        case SYM_GEN_randomUniquePool_1591: this->f_randomUniquePool = val; return true;
        case SYM_GEN_hasBattleRageEffect_1592: this->f_hasBattleRageEffect = val; return true;
        case SYM_GEN_gatedItems_1593: this->f_gatedItems = val; return true;
        case SYM_GEN_startsSubclass_1594: this->f_startsSubclass = val; return true;
        case SYM_GEN_gateItem_1595: this->f_gateItem = val; return true;
        case SYM_GEN_originatingRecipes_1596: this->f_originatingRecipes = val; return true;
        case SYM_GEN_animationScene_1597: this->f_animationScene = val; return true;
        case SYM_GEN_flickerAni_1598: this->f_flickerAni = val; return true;
        case SYM_GEN_flickerMinDist_1599: this->f_flickerMinDist = val; return true;
        case SYM_GEN_flickerMaxDist_1600: this->f_flickerMaxDist = val; return true;
        case SYM_GEN_flickerMinSpeed_1601: this->f_flickerMinSpeed = val; return true;
        case SYM_GEN_flickerMaxSpeed_1602: this->f_flickerMaxSpeed = val; return true;
        case SYM_GEN_connectorReadyRoll_1603: this->f_connectorReadyRoll = val; return true;
        case SYM_GEN_gemRoll_1604: this->f_gemRoll = val; return true;
        case SYM_GEN_sceneDepth_1605: this->f_sceneDepth = val; return true;
        case SYM_GEN_releaseState_1606: this->f_releaseState = gd::gd_coerce_int(val); return true;
        case SYM_GEN__editor_1607: this->f__editor = val; return true;
        case SYM_GEN__playtest_1608: this->f__playtest = val; return true;
        case SYM_GEN__full_version_1609: this->f__full_version = val; return true;
        case SYM_GEN__engineer_test_1610: this->f__engineer_test = val; return true;
        case SYM_GEN_params_1477: this->f_params = val; return true;
        case SYM_GEN_namedParams_1611: this->f_namedParams = val; return true;
        case SYM_GEN_sortedParamNames_1613: this->f_sortedParamNames = val; return true;
        case SYM_GEN_paramBases_1614: this->f_paramBases = val; return true;
        case SYM_GEN_paramBases_inverted_1615: this->f_paramBases_inverted = val; return true;
        case SYM_GEN_gainedStacks_1616: this->f_gainedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_removedStacks_1617: this->f_removedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedStacks_1618: this->f_usedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationAni_1619: this->f_activationAni = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getP_186: return true;
        case SYM_GEN_hasParam_1485: return true;
        case SYM_GEN_addNamedParam_1620: return true;
        case SYM_GEN_hasTag_79: return true;
        case SYM_GEN_isWeapon_80: return true;
        case SYM_GEN_getIndex_233: return true;
        case SYM_GEN_getName_232: return true;
        case SYM_GEN_getRarity_234: return true;
        case SYM_GEN_getShopChance_235: return true;
        case SYM_GEN_getTypes_238: return true;
        case SYM_GEN_isAvailableFor_1621: return true;
        case SYM_GEN_isNeutral_244: return true;
        case SYM_GEN_isClassItem_246: return true;
        case SYM_GEN_isSubclassItem_247: return true;
        case SYM_GEN_isCraftedItem_1622: return true;
        case SYM_GEN_isGatedItem_1623: return true;
        case SYM_GEN_isMeleeWeapon_1624: return true;
        case SYM_GEN_isRangedWeapon_1625: return true;
        case SYM_GEN_isStartingWeapon_1626: return true;
        case SYM_GEN_isReleased_1627: return true;
        case SYM_GEN_getPrice_390: return true;
        case SYM_GEN_getSellPrice_392: return true;
        case SYM_GEN_getSalePrice_393: return true;
        case SYM_GEN_getTranslatedName_637: return true;
        case SYM_GEN_fromDict_1628: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getP_186: out = fn_getP(args, argc); return true;
        case SYM_GEN_hasParam_1485: out = fn_hasParam(args, argc); return true;
        case SYM_GEN_addNamedParam_1620: out = fn_addNamedParam(args, argc); return true;
        case SYM_GEN_hasTag_79: out = fn_hasTag(args, argc); return true;
        case SYM_GEN_isWeapon_80: out = fn_isWeapon(args, argc); return true;
        case SYM_GEN_getIndex_233: out = fn_getIndex(args, argc); return true;
        case SYM_GEN_getName_232: out = fn_getName(args, argc); return true;
        case SYM_GEN_getRarity_234: out = fn_getRarity(args, argc); return true;
        case SYM_GEN_getShopChance_235: out = fn_getShopChance(args, argc); return true;
        case SYM_GEN_getTypes_238: out = fn_getTypes(args, argc); return true;
        case SYM_GEN_isAvailableFor_1621: out = fn_isAvailableFor(args, argc); return true;
        case SYM_GEN_isNeutral_244: out = fn_isNeutral(args, argc); return true;
        case SYM_GEN_isClassItem_246: out = fn_isClassItem(args, argc); return true;
        case SYM_GEN_isSubclassItem_247: out = fn_isSubclassItem(args, argc); return true;
        case SYM_GEN_isCraftedItem_1622: out = fn_isCraftedItem(args, argc); return true;
        case SYM_GEN_isGatedItem_1623: out = fn_isGatedItem(args, argc); return true;
        case SYM_GEN_isMeleeWeapon_1624: out = fn_isMeleeWeapon(args, argc); return true;
        case SYM_GEN_isRangedWeapon_1625: out = fn_isRangedWeapon(args, argc); return true;
        case SYM_GEN_isStartingWeapon_1626: out = fn_isStartingWeapon(args, argc); return true;
        case SYM_GEN_isReleased_1627: out = fn_isReleased(args, argc); return true;
        case SYM_GEN_getPrice_390: out = fn_getPrice(args, argc); return true;
        case SYM_GEN_getSellPrice_392: out = fn_getSellPrice(args, argc); return true;
        case SYM_GEN_getSalePrice_393: out = fn_getSalePrice(args, argc); return true;
        case SYM_GEN_getTranslatedName_637: out = fn_getTranslatedName(args, argc); return true;
        case SYM_GEN_fromDict_1628: out = fn_fromDict(args, argc); return true;
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
    { gd::GdVal _t475 = this->f_namedParams; gd::GdVal _t476 = lv_paramName; gd::set_index(gd_ctx, _t475, _t476, lv_paramVal); }
    gd::GdVal lv_sortedPos = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t477 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_sortedParamNames, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t478 = (_t477.kind == gd::GdVal::Kind::Arr) ? _t477.arr : nullptr;
        uint32_t _len__t479 = _t478 ? _t478->len : 0u;
        for (uint32_t _t479 = 0; _t479 < _len__t479; ++_t479) {
            gd::GdVal lv_i = _t478->data[_t479];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_sortedParamNames, lv_i), gd::SYM_begins_with, _ca, 1); })())) {
                lv_sortedPos = gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_sortedPos, lv_paramName}; return gd::call_method(gd_ctx, this->f_sortedParamNames, gd::SYM_insert, _ca, 2); })();
    { gd::GdVal _t480 = this->f_paramBases; gd::GdVal _t481 = lv_paramName; gd::set_index(gd_ctx, _t480, _t481, ([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_PARAM_DELIMITER_1612), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_paramName, gd::SYM_get_slice, _ca, 2); })()); }
    { gd::GdVal _t482 = this->f_paramBases_inverted; gd::GdVal _t483 = gd::get_index(gd_ctx, this->f_paramBases, lv_paramName); gd::set_index(gd_ctx, _t482, _t483, lv_paramName); }
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
    return gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Weapon_2666), this->f_types);
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
    return gd::GdVal::from_bool(gd::gd_eq(this->f_classes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StuffedClasses_1366), SYM_GEN_Neutral_2667)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isClassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_classes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StuffedClasses_1366), SYM_GEN_Neutral_2667)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_classes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StuffedClasses_1366), SYM_GEN_None_2668))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isSubclassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_ne(this->f_startsSubclass, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))));
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
    return (gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Melee_2669), this->f_types)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_80, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isRangedWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ranged_2670), this->f_types)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_80, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isStartingWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_80, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_identifier, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stone", 5u)))))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isReleased(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_releaseState, gd::get_prop(gd_ctx, Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_ReleaseState_1629), SYM_GEN_Demo_2671))))) {
        return gd::GdVal::from_bool(true);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_releaseState, gd::get_prop(gd_ctx, Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_ReleaseState_1629), SYM_GEN_Full_2665))))) {
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
    return gd::gd_ceil(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getPrice_390, nullptr, 0), gd::GdVal::from_float(0.5)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getSalePrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_ceil(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getPrice_390, nullptr, 0), gd::GdVal::from_float(0.5)));
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
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_name_7, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "name", 4u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_identifier_1575, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "identifier", 10u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "name", 4u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_itemIndex_1576, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "index", 5u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_minDam_1577, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "minDam", 6u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_maxDam_1578, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxDam", 6u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_staminaCost_1579, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminaCost", 11u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_block_1580, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_cd_1581, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_extraCds_1582, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "extraCds", 8u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_accuracy_1452, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "accuracy", 8u)), gd::GdVal::from_float(100.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_canActivate_89, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canActivate", 11u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1356, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_chance_1583, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance", 6u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_chance2_1584, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance2", 7u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_shopChance_1585, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "shopChance", 10u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_types_1451, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "types", 5u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_tags_1586, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "tags", 4u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_physics_1587, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "physics", 7u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_rarity_1588, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "rarity", 6u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_price_1589, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "price", 5u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_classes_1590, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "classes", 7u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_randomUniquePool_1591, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randomUniquePool", 16u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1356, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_hasBattleRageEffect_1592, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hasBattleRageEffect", 19u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1356, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gatedItems_1593, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gatedItems", 10u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_startsSubclass_1594, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "startsSubclass", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gateItem_1595, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gateItem", 8u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gate_item", 9u)), gd::GdVal::null()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_originatingRecipes_1596, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "originatingRecipes", 18u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "originating_recipes", 19u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_animationScene_1597, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "animationScene", 14u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1356, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerAni_1598, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerAni", 10u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_animation", 17u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1356, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMinDist_1599, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerMinDist", 14u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_min_dist", 16u)), gd::GdVal::from_float(0.1)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMaxDist_1600, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerMaxDist", 14u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_max_dist", 16u)), gd::GdVal::from_float(3.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMinSpeed_1601, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerMinSpeed", 15u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_min_speed", 17u)), gd::GdVal::from_float(0.3)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMaxSpeed_1602, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerMaxSpeed", 15u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_max_speed", 17u)), gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_connectorReadyRoll_1603, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "connectorReadyRoll", 18u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "connector_ready_roll", 20u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1356, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gemRoll_1604, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gemRoll", 7u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gem_roll", 8u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1356, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_sceneDepth_1605, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sceneDepth", 10u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "scene_depth", 11u)), gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_releaseState_1606, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "releaseState", 12u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "release_state", 13u)), gd::get_prop(gd_ctx, Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_ReleaseState_1629), SYM_GEN_Full_2665)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_params_1477, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "params", 6u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::GdVal lv_np = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "namedParams", 11u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "named_params", 12u)), gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })();
    {
        gd::GdVal _t484 = gd::gd_iter_seq(gd_ctx.arena, lv_np);
        gd::GdArr* _t485 = (_t484.kind == gd::GdVal::Kind::Arr) ? _t484.arr : nullptr;
        uint32_t _len__t486 = _t485 ? _t485->len : 0u;
        for (uint32_t _t486 = 0; _t486 < _len__t486; ++_t486) {
            gd::GdVal lv_k = _t485->data[_t486];
            (void)([&]() { gd::GdVal _ca[] = {lv_k, gd::get_index(gd_ctx, lv_np, lv_k)}; return gd::call_method(gd_ctx, lv_o, SYM_GEN_addNamedParam_1620, _ca, 2); })();
        }
    }
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gainedStacks_1616, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gainedStacks", 12u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_removedStacks_1617, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "removedStacks", 13u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_usedStacks_1618, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "usedStacks", 10u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
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
        case SYM_GEN_damPerDebuff_1731: out = this->f_damPerDebuff; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Darksaber::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damPerDebuff_1731: this->f_damPerDebuff = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Darksaber::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onDebuffsChanged_1732: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Darksaber::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDebuffsChanged_1732: out = fn_onDebuffsChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Darksaber::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Darksaber::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDebuffsChanged", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_374, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn_onDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerDebuff)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_331, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damPerDebuff = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__FlyAgaric::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__FlyAgaric::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__FlyAgaric::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FlyAgaric::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_vampirism_936: out = this->f_vampirism; return true;
        case SYM_GEN_regenNeeded_938: out = this->f_regenNeeded; return true;
        case SYM_GEN_vampirismForRegen_1807: out = this->f_vampirismForRegen; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__HungryBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirism_936: this->f_vampirism = val; return true;
        case SYM_GEN_regenNeeded_938: this->f_regenNeeded = val; return true;
        case SYM_GEN_vampirismForRegen_1807: this->f_vampirismForRegen = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HungryBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onVampirismChanged_939: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HungryBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onVampirismChanged_939: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HungryBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_vampirism_changed", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onVampirismChanged", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core__HungryBlade::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Jump_2639)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMaxDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        gd::GdVal lv_numRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_numRegen, this->f_regenNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_344, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_vampirismForRegen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_vampirism = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    this->f_regenNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    this->f_vampirismForRegen = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
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
        case SYM_GEN_manaGained_1835: out = this->f_manaGained; return true;
        case SYM_GEN_fillingTween_1836: out = this->f_fillingTween; return true;
        case SYM_GEN_filling_1837: out = this->f_filling; return true;
        case SYM_GEN_fillingGlow_1838: out = this->f_fillingGlow; return true;
        case SYM_GEN_fillingHeight_1839: out = this->f_fillingHeight; return true;
        case SYM_GEN_fillingAnimation_1840: out = this->f_fillingAnimation; return true;
        case SYM_GEN_manaNeededForLifesteal_1841: out = this->f_manaNeededForLifesteal; return true;
        case SYM_GEN_dam_935: out = this->f_dam; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Manathirst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaGained_1835: this->f_manaGained = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fillingTween_1836: this->f_fillingTween = val; return true;
        case SYM_GEN_filling_1837: this->f_filling = val; return true;
        case SYM_GEN_fillingGlow_1838: this->f_fillingGlow = val; return true;
        case SYM_GEN_fillingHeight_1839: this->f_fillingHeight = val; return true;
        case SYM_GEN_fillingAnimation_1840: this->f_fillingAnimation = val; return true;
        case SYM_GEN_manaNeededForLifesteal_1841: this->f_manaNeededForLifesteal = val; return true;
        case SYM_GEN_dam_935: this->f_dam = val; return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Manathirst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_tweenFilling_1842: return true;
        case SYM_GEN_onManaChanged_1833: return true;
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Manathirst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_tweenFilling_1842: out = fn_tweenFilling(args, argc); return true;
        case SYM_GEN_onManaChanged_1833: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1842, _ca, 1); })();
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
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getVampirism_1206, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_327, _ca, 3); })();
        }
        gd::GdVal lv_relHeight = gd::gd_div(gd_ctx, this->f_manaGained, this->f_manaNeededForLifesteal);
        (void)([&]() { gd::GdVal _ca[] = {lv_relHeight}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1842, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1842, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaNeededForLifesteal = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_affectedPotions_1869: out = this->f_affectedPotions; return true;
        case SYM_GEN_numConsumed_1870: out = this->f_numConsumed; return true;
        default: break;
    }
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__PotionBelt::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedPotions_1869: this->f_affectedPotions = val; return true;
        case SYM_GEN_numConsumed_1870: this->f_numConsumed = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PotionBelt::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPotionEmptied_1871: return true;
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__PotionBelt::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPotionEmptied_1871: out = fn_onPotionEmptied(args, argc); return true;
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_affectedItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0);
    {
        gd::GdVal _t487 = gd::gd_iter_seq(gd_ctx.arena, lv_affectedItems);
        gd::GdArr* _t488 = (_t487.kind == gd::GdVal::Kind::Arr) ? _t487.arr : nullptr;
        uint32_t _len__t489 = _t488 ? _t488->len : 0u;
        for (uint32_t _t489 = 0; _t489 < _len__t489; ++_t489) {
            gd::GdVal lv_item = _t488->data[_t489];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_affectedPotions, gd::SYM_push_back, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_emptied", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPotionEmptied", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
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
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 1); })();
        lv_active = gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_801, _ca, 1); })())) {
        lv_numBuffs = gd::gd_add(gd_ctx, lv_numBuffs, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })(), SYM_GEN_getP_186, _ca, 1); })()));
        lv_active = gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numBuffs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_numBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 1); })();
    }
    if (gd::gd_truth(lv_active)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PotionBelt::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PotionBelt::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_buffActive_1717: out = this->f_buffActive; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_unhealingTimer_1888: out = this->f_unhealingTimer; return true;
        case SYM_GEN_manaCost_1719: out = this->f_manaCost; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__StaffofUnhealing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffActive_1717: this->f_buffActive = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_unhealingTimer_1888: this->f_unhealingTimer = val; return true;
        case SYM_GEN_manaCost_1719: this->f_manaCost = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StaffofUnhealing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__StaffofUnhealing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StaffofUnhealing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_healAmount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaCost)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffActive)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_giveUnhealing_1158, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_unhealing", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_start_1683, _ca, 1); })();
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_reduceUnhealing_1159, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_unhealingTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "UnhealingTimer", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_manaCost = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0);
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
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__TheFool::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__TheFool::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_886: return true;
        case SYM_GEN_doRevealEffect_889: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__TheFool::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_886: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_889: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "revealspeed", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t490 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1736));
        gd::GdArr* _t491 = (_t490.kind == gd::GdVal::Kind::Arr) ? _t490.arr : nullptr;
        uint32_t _len__t492 = _t491 ? _t491->len : 0u;
        for (uint32_t _t492 = 0; _t492 < _len__t492; ++_t492) {
            gd::GdVal lv_card = _t491->data[_t492];
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::call_method(gd_ctx, lv_card, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_886, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__TheFool::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_activeFront_874: out = this->f_activeFront; return true;
        case SYM_GEN_curActivationDelay_875: out = this->f_curActivationDelay; return true;
        case SYM_GEN_faceUp_876: out = this->f_faceUp; return true;
        case SYM_GEN_activating_877: out = this->f_activating; return true;
        case SYM_GEN_chainPosition_878: out = this->f_chainPosition; return true;
        case SYM_GEN_deck_879: out = this->f_deck; return true;
        case SYM_GEN_cardAnimation_880: out = this->f_cardAnimation; return true;
        case gd::SYM_front: out = this->f_front; return true;
        case SYM_GEN_connector_881: out = this->f_connector; return true;
        case SYM_GEN_notInChainMark_882: out = this->f_notInChainMark; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Card::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case gd::SYM_back: this->f_back = val; return true;
        case SYM_GEN_activeFront_874: this->f_activeFront = val; return true;
        case SYM_GEN_curActivationDelay_875: this->f_curActivationDelay = gd::gd_coerce_float(val); return true;
        case SYM_GEN_faceUp_876: this->f_faceUp = val; return true;
        case SYM_GEN_activating_877: this->f_activating = val; return true;
        case SYM_GEN_chainPosition_878: this->f_chainPosition = val; return true;
        case SYM_GEN_deck_879: this->f_deck = val; return true;
        case SYM_GEN_cardAnimation_880: this->f_cardAnimation = val; return true;
        case gd::SYM_front: this->f_front = val; return true;
        case SYM_GEN_connector_881: this->f_connector = val; return true;
        case SYM_GEN_notInChainMark_882: this->f_notInChainMark = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Card::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_setFaceUp_883: return true;
        case SYM_GEN_setFaceDown_884: return true;
        case SYM_GEN_updateTexture_885: return true;
        case SYM_GEN_cardSecondaryEffectActive_886: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_preCombatStart_122: return true;
        case SYM_GEN_getNextCard_887: return true;
        case SYM_GEN_startActivation_888: return true;
        case SYM_GEN_playActivationAnimation_774: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN_doRevealEffect_889: return true;
        case SYM_GEN_trigger_141: return true;
        case SYM_GEN_combatEnd_129: return true;
        case SYM_GEN_shopEntered_741: return true;
        case SYM_GEN_addToInventory_118: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_notifyChainPosition_890: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_getCardDescription_891: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Card::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_setFaceUp_883: out = fn_setFaceUp(args, argc); return true;
        case SYM_GEN_setFaceDown_884: out = fn_setFaceDown(args, argc); return true;
        case SYM_GEN_updateTexture_885: out = fn_updateTexture(args, argc); return true;
        case SYM_GEN_cardSecondaryEffectActive_886: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_preCombatStart_122: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_getNextCard_887: out = fn_getNextCard(args, argc); return true;
        case SYM_GEN_startActivation_888: out = fn_startActivation(args, argc); return true;
        case SYM_GEN_playActivationAnimation_774: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_doRevealEffect_889: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_trigger_141: out = fn_trigger(args, argc); return true;
        case SYM_GEN_combatEnd_129: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_shopEntered_741: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_addToInventory_118: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_notifyChainPosition_890: out = fn_notifyChainPosition(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getCardDescription_891: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        if (gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(this->f_activeFront)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_886, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
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
        return (gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_878), this->f_chainPosition))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_878), gd::gd_neg(gd::GdVal::from_int(1LL))))))))) : gd::GdVal::from_bool(false));
    }
    else {
        return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_deck_879))))) : gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_122, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_getNextCard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_421, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_hasType_77, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
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
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_100, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_96, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), SYM_GEN_Cooldown_2545)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_snapshotItemTooltipStat_1351, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1619));
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldown_790, _ca, 1); })();
    gd::GdVal lv_nextCard = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextCard_887, nullptr, 0);
    if (gd::gd_truth(lv_nextCard)) {
        (void)gd::call_method(gd_ctx, lv_nextCard, SYM_GEN_startActivation_888, nullptr, 0);
    }
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_97, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doRevealEffect_889, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_129, nullptr, 0, _out); return _out; })();
    this->f_activating = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_741, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceUp_883, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_118, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_deck = gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateTexture_885, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateTexture_885, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_638, _ca, 1, _out); return _out; })();
    return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCardDescription_891, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_COUNT", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "num", 3u)), this->f_chainPosition, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 5); })()));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_HINT", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_paramColor_2620)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_wrapInColor_2673, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Blueberries::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Blueberries::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Blueberries::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_overflow = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_capped_333, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_overflow, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Blueberries::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onAffectedAttacked_1728: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__CursedHairComb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onAffectedAttacked_1728: out = fn_onAffectedAttacked(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Vampiric_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_addHealingEfficiency_1162, _ca, 1); })();
    {
        gd::GdVal _t493 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t494 = (_t493.kind == gd::GdVal::Kind::Arr) ? _t493.arr : nullptr;
        uint32_t _len__t495 = _t494 ? _t494->len : 0u;
        for (uint32_t _t495 = 0; _t495 < _len__t495; ++_t495) {
            gd::GdVal lv_weapon = _t494->data[_t495];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAffectedAttacked", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onAffectedAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        gd::GdVal lv_bonusLifesteal = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal_scaling", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })());
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_div(gd_ctx, gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425), gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_bonusLifesteal)), gd::GdVal::from_float(100.0))), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_amuletColor_1924: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.266667), gd::GdVal::from_float(0.309804), gd::GdVal::from_float(0.960784)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_potionsToTrigger_1927: out = this->f_potionsToTrigger; return true;
        case SYM_GEN_potionTriggerTimer_1928: out = this->f_potionTriggerTimer; return true;
        case SYM_GEN_delay_1929: out = this->f_delay; return true;
        case SYM_GEN_amuletColor_1924: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_potionsToTrigger_1927: this->f_potionsToTrigger = val; return true;
        case SYM_GEN_potionTriggerTimer_1928: this->f_potionTriggerTimer = val; return true;
        case SYM_GEN_delay_1929: this->f_delay = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onPotionEmptied_1871: return true;
        case SYM_GEN_triggerNextPotion_1930: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPotionEmptied_1871: out = fn_onPotionEmptied(args, argc); return true;
        case SYM_GEN_triggerNextPotion_1930: out = fn_triggerNextPotion(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t496 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t497 = (_t496.kind == gd::GdVal::Kind::Arr) ? _t496.arr : nullptr;
        uint32_t _len__t498 = _t497 ? _t497->len : 0u;
        for (uint32_t _t498 = 0; _t498 < _len__t498; ++_t498) {
            gd::GdVal lv_item = _t497->data[_t498];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_emptied", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPotionEmptied", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onPotionEmptied(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_potion = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_potion}; return gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_push_back, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_delay}; return gd::call_method(gd_ctx, this->f_potionTriggerTimer, SYM_GEN_start_1683, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_triggerNextPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_potion = gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_pop_front, nullptr, 0);
    (void)gd::call_method(gd_ctx, lv_potion, SYM_GEN_triggerPotion_1754, nullptr, 0);
    (void)gd::call_method(gd_ctx, lv_potion, SYM_GEN_miniActivate_468, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_potionTriggerTimer, SYM_GEN_stop_1684, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_potionTriggerTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "PotionTriggerTimer", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "triggerNextPotion", 17u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_delay = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "delay", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__PowerPuppy::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Pet_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numFood = gd::GdVal::from_int(0LL);
    gd::GdVal lv_numPets = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t499 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t500 = (_t499.kind == gd::GdVal::Kind::Arr) ? _t499.arr : nullptr;
        uint32_t _len__t501 = _t500 ? _t500->len : 0u;
        for (uint32_t _t501 = 0; _t501 < _len__t501; ++_t501) {
            gd::GdVal lv_item = _t500->data[_t501];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
                lv_numFood = gd::gd_add(gd_ctx, lv_numFood, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Pet_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
                lv_numPets = gd::gd_add(gd_ctx, lv_numPets, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::gd_mul(lv_numPets, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)), gd::gd_mul(lv_numFood, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0))), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__PowerPuppy::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_damPerVampOrSpike_1976: out = this->f_damPerVampOrSpike; return true;
        case SYM_GEN_regenNeeded_938: out = this->f_regenNeeded; return true;
        case SYM_GEN_vampirism_936: out = this->f_vampirism; return true;
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damPerVampOrSpike_1976: this->f_damPerVampOrSpike = val; return true;
        case SYM_GEN_regenNeeded_938: this->f_regenNeeded = val; return true;
        case SYM_GEN_vampirism_936: this->f_vampirism = val; return true;
        case SYM_GEN_spikes_894: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onVampirismChanged_939: return true;
        case SYM_GEN_onSpikesChanged_940: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_939: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onSpikesChanged_940: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Greatsword::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Greatsword::call_method(gd_ctx, SYM_GEN_onPrepare_121, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_vampirism_changed", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onVampirismChanged", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerVampOrSpike)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerVampOrSpike)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0), this->f_regenNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_344, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Greatsword::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damPerVampOrSpike = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_luckNeeded_1778: out = this->f_luckNeeded; return true;
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_luckNeeded_1778: this->f_luckNeeded = val; return true;
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BroccoliGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BroccoliGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_PieceColor_2053: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor);
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
        case SYM_GEN_pieceColor_2038: out = this->f_pieceColor; return true;
        case SYM_GEN_moveCells_2039: out = this->f_moveCells; return true;
        case SYM_GEN_captured_2040: out = this->f_captured; return true;
        case SYM_GEN_numCaptures_2041: out = this->f_numCaptures; return true;
        case SYM_GEN_board_2042: out = this->f_board; return true;
        case SYM_GEN_noBoardMark_2043: out = this->f_noBoardMark; return true;
        case SYM_GEN_PieceColor_2053: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_pieceColor_2038: this->f_pieceColor = gd::gd_coerce_int(val); return true;
        case SYM_GEN_moveCells_2039: this->f_moveCells = val; return true;
        case SYM_GEN_captured_2040: this->f_captured = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_numCaptures_2041: this->f_numCaptures = gd::gd_coerce_int(val); return true;
        case SYM_GEN_board_2042: this->f_board = val; return true;
        case SYM_GEN_noBoardMark_2043: this->f_noBoardMark = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_affectsEmpty_253: return true;
        case SYM_GEN_setBoard_2044: return true;
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_getMoveCells_2045: return true;
        case SYM_GEN_getCaptureCells_2046: return true;
        case SYM_GEN_onPieceMoved_2047: return true;
        case SYM_GEN_onPieceCaptured_2048: return true;
        case SYM_GEN_doCapturingEffect_2049: return true;
        case SYM_GEN_onEliminatedBy_2050: return true;
        case SYM_GEN_doEliminatedEffect_2051: return true;
        case SYM_GEN_repositionPiece_2052: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_discard_760: return true;
        case SYM_GEN_canBeBlocked_1465: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_affectsEmpty_253: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_setBoard_2044: out = fn_setBoard(args, argc); return true;
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_getMoveCells_2045: out = fn_getMoveCells(args, argc); return true;
        case SYM_GEN_getCaptureCells_2046: out = fn_getCaptureCells(args, argc); return true;
        case SYM_GEN_onPieceMoved_2047: out = fn_onPieceMoved(args, argc); return true;
        case SYM_GEN_onPieceCaptured_2048: out = fn_onPieceCaptured(args, argc); return true;
        case SYM_GEN_doCapturingEffect_2049: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_onEliminatedBy_2050: out = fn_onEliminatedBy(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2051: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_repositionPiece_2052: out = fn_repositionPiece(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_discard_760: out = fn_discard(args, argc); return true;
        case SYM_GEN_canBeBlocked_1465: out = fn_canBeBlocked(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_ChessPiece_2674)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_pieceColor_2038), this->f_pieceColor)))) : gd::GdVal::from_bool(false));
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
    (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, this->f_occupiedCells, gd::GdVal::from_int(0LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)gd::call_method(gd_ctx, this->f_moveCells, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t502 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_tilemap_406, nullptr, 0));
        gd::GdArr* _t503 = (_t502.kind == gd::GdVal::Kind::Arr) ? _t502.arr : nullptr;
        uint32_t _len__t504 = _t503 ? _t503->len : 0u;
        for (uint32_t _t504 = 0; _t504 < _len__t504; ++_t504) {
            gd::GdVal lv_cell = _t503->data[_t504];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::gd_sub(lv_cell, gd::get_index(gd_ctx, this->f_occupiedCells, gd::GdVal::from_int(0LL))), gd::SYM_round, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_moveCells, gd::SYM_push_back, _ca, 1); })();
        }
    }
    this->f_numCaptures = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_targetCell}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onPieceCaptured(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_activateEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_numCaptures = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numCaptures, gd::GdVal::from_int(1LL)));
    gd::GdVal lv_targetCell = gd::get_index(gd_ctx, gd::get_prop(gd_ctx, lv_eliminatedPiece, SYM_GEN_occupiedCells_50), gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {lv_eliminatedPiece}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_clearItemCells_1527, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_targetCell, gd::GdVal::from_bool(false), lv_activateEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::null(), gd::GdVal::null(), gd::GdVal::null()})), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Exclusive/Chess/ChessPiece.gd:74", 32u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_pickRandomEngine_1650, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_eliminatedPiece}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCapturingEffect_2049, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_activateEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_capturingPiece}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doEliminatedEffect_2051, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_toCell}))}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_moveItem_1528, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::GdVal::from_int(gd::gd_typeof(lv_state)), gd::GdVal::from_int(5))))) {
        gd::GdVal lv_targetCell = lv_state;
        (void)([&]() { gd::GdVal _ca[] = {lv_targetCell}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_repositionPiece_2052, _ca, 1); })();
    }
    else {
        this->f_captured = gd::gd_coerce_bool(lv_state);
        if (gd::gd_truth(this->f_captured)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_clearItemCells_1527, _ca, 1); })();
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
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_638, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(this->f_placed) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_board, gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "HINT_Chess", 10u)), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_paramColor_2620)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_wrapInColor_2673, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_760, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_canBeBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::gd_in(gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "White", 5u)), this->f_name))) {
        this->f_pieceColor = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, SYM_GEN_PieceColor_2053), SYM_GEN_White_2675));
    }
    else {
        this->f_pieceColor = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, SYM_GEN_PieceColor_2053), SYM_GEN_Black_2676));
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliPepper::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliPepper::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_boosted_2100: out = this->f_boosted; return true;
        case SYM_GEN_crystalDescriptor_2101: out = this->f_crystalDescriptor; return true;
        case SYM_GEN_debuffs_2054: out = this->f_debuffs; return true;
        case SYM_GEN_vampirism_936: out = this->f_vampirism; return true;
        case SYM_GEN_darkSpeed_2102: out = this->f_darkSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2100: this->f_boosted = val; return true;
        case SYM_GEN_crystalDescriptor_2101: this->f_crystalDescriptor = val; return true;
        case SYM_GEN_debuffs_2054: this->f_debuffs = val; return true;
        case SYM_GEN_vampirism_936: this->f_vampirism = val; return true;
        case SYM_GEN_darkSpeed_2102: this->f_darkSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_onBought_453: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemRoll_1922: return true;
        case SYM_GEN_onItemRolled_1923: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_453: out = fn_onBought(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_1922: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1923: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_debuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_355, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numDark = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numDark, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_darkSpeed, lv_numDark)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_crystalDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Corrupted Crystal", 17u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
    this->f_debuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffs", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_darkSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_hasActivated_1810: out = this->f_hasActivated; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1810: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onBattleRageStarted_1970: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1970: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Cold_2573), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeResistChance_1021, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonskinBoots::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonskinBoots::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_battleRageDur_2157: out = this->f_battleRageDur; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1292: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_battleRageDur_2157: this->f_battleRageDur = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_preCombatStart_122: return true;
        case SYM_GEN_onBattleRageStarted_1970: return true;
        case SYM_GEN_onBattleRageEnded_1971: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preCombatStart_122: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1970: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1971: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_122, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        this->f_battleRageDur = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "duration", 8u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1482, _ca, 2); })());
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_96, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dur = gd::gd_div(gd_ctx, gd::gd_mul(this->f_battleRageDur, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()), gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_dur, gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_startBattleRage_1179, _ca, 4); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_FrogState_2181: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__FrogPrince_FrogState);
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
        case SYM_GEN_frogState_2180: out = this->f_frogState; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_light_945: out = this->f_light; return true;
        case SYM_GEN_blind_1815: out = this->f_blind; return true;
        case SYM_GEN_FrogState_2181: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__FrogPrince_FrogState); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_frogState_2180: this->f_frogState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_light_945: this->f_light = val; return true;
        case SYM_GEN_blind_1815: this->f_blind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onGainThresholdReached_2178: return true;
        case SYM_GEN_onUseThresholdReached_2179: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onGainThresholdReached_2178: out = fn_onGainThresholdReached(args, argc); return true;
        case SYM_GEN_onUseThresholdReached_2179: out = fn_onUseThresholdReached(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseBlind_342, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onUseThresholdReached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ticks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_frogState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2181), SYM_GEN_Inactive_2593))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2181), SYM_GEN_Active_2594), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_1", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_makeInvulnerable_1191, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Toad::call_method(gd_ctx, SYM_GEN_onPrepare_121, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2181), SYM_GEN_Inactive_2593)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2181), SYM_GEN_Used_2595), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2181), SYM_GEN_Inactive_2593)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__frogState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__frogState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2181), SYM_GEN_Inactive_2593))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__frogState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2181), SYM_GEN_Active_2594))))) {
    }
    else {
    }
    this->f_frogState = gd::gd_coerce_int(lv__frogState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Toad::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        case SYM_GEN_chainPosition_878: out = this->f_chainPosition; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        case SYM_GEN_chainPosition_878: this->f_chainPosition = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCardRevealed_2202: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCardRevealed_2202: out = fn_onCardRevealed(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t505 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t506 = (_t505.kind == gd::GdVal::Kind::Arr) ? _t505.arr : nullptr;
        uint32_t _len__t507 = _t506 ? _t506->len : 0u;
        for (uint32_t _t507 = 0; _t507 < _len__t507; ++_t507) {
            gd::GdVal lv_item = _t506->data[_t507];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCardRevealed", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::fn_onCardRevealed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_card = gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1487, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_card, SYM_GEN_chainPosition_878), gd::GdVal::from_int(1LL)), this->f_chainPosition)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_chainPosition = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pos", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_quads_2229: out = this->f_quads; return true;
        case SYM_GEN_triplets_2230: out = this->f_triplets; return true;
        case SYM_GEN_pairs_2231: out = this->f_pairs; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_staminaReduction_1917: out = this->f_staminaReduction; return true;
        case SYM_GEN_revealsPerQuad_2232: out = this->f_revealsPerQuad; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Joker::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_quads_2229: this->f_quads = val; return true;
        case SYM_GEN_triplets_2230: this->f_triplets = val; return true;
        case SYM_GEN_pairs_2231: this->f_pairs = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_staminaReduction_1917: this->f_staminaReduction = val; return true;
        case SYM_GEN_revealsPerQuad_2232: this->f_revealsPerQuad = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Joker::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_countChain_2233: return true;
        case SYM_GEN_notifyChainPosition_890: return true;
        case SYM_GEN_doRevealEffect_889: return true;
        case SYM_GEN_getCardDescription_891: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Joker::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_countChain_2233: out = fn_countChain(args, argc); return true;
        case SYM_GEN_notifyChainPosition_890: out = fn_notifyChainPosition(args, argc); return true;
        case SYM_GEN_doRevealEffect_889: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_getCardDescription_891: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
            gd::GdVal _t508 = gd::gd_iter_seq(gd_ctx.arena, this->f_chainPosition);
            gd::GdArr* _t509 = (_t508.kind == gd::GdVal::Kind::Arr) ? _t508.arr : nullptr;
            uint32_t _len__t510 = _t509 ? _t509->len : 0u;
            for (uint32_t _t510 = 0; _t510 < _len__t510; ++_t510) {
                gd::GdVal lv_i = _t509->data[_t510];
                (void)([&]() { gd::GdVal _ca[] = {lv_counter, gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1736), lv_i), SYM_GEN_descriptor_2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_dictAdd_1693, _ca, 2); })();
            }
        }
        {
            gd::GdVal _t511 = gd::gd_iter_seq(gd_ctx.arena, lv_counter);
            gd::GdArr* _t512 = (_t511.kind == gd::GdVal::Kind::Arr) ? _t511.arr : nullptr;
            uint32_t _len__t513 = _t512 ? _t512->len : 0u;
            for (uint32_t _t513 = 0; _t513 < _len__t513; ++_t513) {
                gd::GdVal lv_cardType = _t512->data[_t513];
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
    (void)([&]() { gd::GdVal _ca[] = {lv__deck, lv__chainPos, lv_chainLength}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN_notifyChainPosition_890, _ca, 3, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countChain_2233, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_pairs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_pairs}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_gainCritResistStacks_1155, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_triplets, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t514 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
            gd::GdArr* _t515 = (_t514.kind == gd::GdVal::Kind::Arr) ? _t514.arr : nullptr;
            uint32_t _len__t516 = _t515 ? _t515->len : 0u;
            for (uint32_t _t516 = 0; _t516 < _len__t516; ++_t516) {
                gd::GdVal lv_item = _t515->data[_t516];
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(this->f_staminaReduction), this->f_triplets)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_303, _ca, 1); })();
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_quads, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_legitCards = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t517 = gd::gd_iter_seq(gd_ctx.arena, this->f_chainPosition);
            gd::GdArr* _t518 = (_t517.kind == gd::GdVal::Kind::Arr) ? _t517.arr : nullptr;
            uint32_t _len__t519 = _t518 ? _t518->len : 0u;
            for (uint32_t _t519 = 0; _t519 < _len__t519; ++_t519) {
                gd::GdVal lv_i = _t518->data[_t519];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1736), lv_i), SYM_GEN_descriptor_2), this->f_descriptor)))) {
                    (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1736), lv_i)}; return gd::call_method(gd_ctx, lv_legitCards, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
        {
            gd::GdVal _t520 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_mul(this->f_quads, this->f_revealsPerQuad));
            gd::GdArr* _t521 = (_t520.kind == gd::GdVal::Kind::Arr) ? _t520.arr : nullptr;
            uint32_t _len__t522 = _t521 ? _t521->len : 0u;
            for (uint32_t _t522 = 0; _t522 < _len__t522; ++_t522) {
                gd::GdVal lv_i = _t521->data[_t522];
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_legitCards, gd::SYM_empty, nullptr, 0))))) {
                    gd::GdVal lv_revealedCard = ([&]() { gd::GdVal _ca[] = {lv_legitCards}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_pickRandomElement_1648, _ca, 1); })();
                    (void)gd::call_method(gd_ctx, lv_revealedCard, SYM_GEN_doRevealEffect_889, nullptr, 0);
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_legitCards, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL))))) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_revealedCard}; return gd::call_method(gd_ctx, lv_legitCards, gd::SYM_erase, _ca, 1); })();
                    }
                }
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        gd::GdVal lv_counterText = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Joker_COUNTER", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })();
        gd::GdVal lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_pairs, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_Positive_2548);
        }
        else {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_Negative_2549);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pairs", 5u)), this->f_pairs, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 5); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_triplets, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_Positive_2548);
        }
        else {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_Negative_2549);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "triplets", 8u)), this->f_triplets, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 5); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_quads, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_Positive_2548);
        }
        else {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_Negative_2549);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "quadruples", 10u)), this->f_quads, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 5); })();
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), lv_counterText));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_HINT", 9u)), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_paramColor_2620)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_wrapInColor_2673, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_revealsPerQuad = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cards", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_blockRemoval_1801: out = this->f_blockRemoval; return true;
        case SYM_GEN_damResistance_2256: out = this->f_damResistance; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LongSpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockRemoval_1801: this->f_blockRemoval = val; return true;
        case SYM_GEN_damResistance_2256: this->f_damResistance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LongSpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_addToStorageBox_663: return true;
        case SYM_GEN_affectsEmpty_253: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LongSpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToStorageBox_663: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_affectsEmpty_253: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT)))))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_465, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_addToStorageBox_663, _ca, 6, _out); return _out; })();
        (void)([&]() { gd::GdVal _ca[] = {lv_curDir}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_465, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirection_476, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_addToStorageBox_663, _ca, 6, _out); return _out; })();
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
    this->f_blockRemoval = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_424, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_blockRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_203, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damResistance)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damResistance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_stackTypes_1830: out = this->f_stackTypes; return true;
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_sales_2260: out = this->f_sales; return true;
        case SYM_GEN_luckNeeded_1778: out = this->f_luckNeeded; return true;
        case SYM_GEN_numBuffs_1909: out = this->f_numBuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MegaClover::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1830: this->f_stackTypes = val; return true;
        case SYM_GEN_activated_1292: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_sales_2260: this->f_sales = val; return true;
        case SYM_GEN_luckNeeded_1778: this->f_luckNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_numBuffs_1909: this->f_numBuffs = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MegaClover::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onLuckyChanged_897: return true;
        case SYM_GEN_onSaleRoll_1997: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MegaClover::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_897: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_onSaleRoll_1997: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckyChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MegaClover::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, lv_event, this->f_stackTypes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_sales = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sales", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckneeded", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_stackTypes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Lucky_2569)}; return gd::call_method(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
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
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        case SYM_GEN_fatigueMana_2322: out = this->f_fatigueMana; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        case SYM_GEN_fatigueMana_2322: this->f_fatigueMana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_playPickupSound_732: return true;
        case SYM_GEN_playDropSound_147: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_732: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_147: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_294, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t523 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t524 = (_t523.kind == gd::GdVal::Kind::Arr) ? _t523.arr : nullptr;
        uint32_t _len__t525 = _t524 ? _t524->len : 0u;
        for (uint32_t _t525 = 0; _t525 < _len__t525; ++_t525) {
            gd::GdVal lv_item = _t524->data[_t525];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_195, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1387), SYM_GEN_hasFatigueStarted_1305, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_fatigueMana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_fatigueMana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fatiguemana", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_numFood_2340: out = this->f_numFood; return true;
        case SYM_GEN_foodPotionSpeed_2341: out = this->f_foodPotionSpeed; return true;
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Pot::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numFood_2340: this->f_numFood = gd::gd_coerce_int(val); return true;
        case SYM_GEN_foodPotionSpeed_2341: this->f_foodPotionSpeed = val; return true;
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Pot::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onPotionTriggered_2342: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Pot::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPotionTriggered_2342: out = fn_onPotionTriggered(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numFood = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_foodPotionSpeed, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), this->f_numFood))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    {
        gd::GdVal _t526 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t527 = (_t526.kind == gd::GdVal::Kind::Arr) ? _t526.arr : nullptr;
        uint32_t _len__t528 = _t527 ? _t527->len : 0u;
        for (uint32_t _t528 = 0; _t528 < _len__t528; ++_t528) {
            gd::GdVal lv_item = _t527->data[_t528];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_triggered", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPotionTriggered", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_onPotionTriggered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__potion = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal_food", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), this->f_numFood))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_foodPotionSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 1); })();
    {
        gd::GdVal _t529 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t530 = (_t529.kind == gd::GdVal::Kind::Arr) ? _t529.arr : nullptr;
        uint32_t _len__t531 = _t530 ? _t530->len : 0u;
        for (uint32_t _t531 = 0; _t531 < _len__t531; ++_t531) {
            gd::GdVal lv_item = _t530->data[_t531];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        case SYM_GEN_speedPerGold_2254: out = this->f_speedPerGold; return true;
        case SYM_GEN_maxGoldDif_2380: out = this->f_maxGoldDif; return true;
        case SYM_GEN_equilibriumSpeed_2381: out = this->f_equilibriumSpeed; return true;
        case SYM_GEN_leftCounter_2382: out = this->f_leftCounter; return true;
        case SYM_GEN_rightCounter_2383: out = this->f_rightCounter; return true;
        case SYM_GEN_leftCounterDefaultPos_2384: out = this->f_leftCounterDefaultPos; return true;
        case SYM_GEN_rightCounterDefaultPos_2385: out = this->f_rightCounterDefaultPos; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Scale::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        case SYM_GEN_speedPerGold_2254: this->f_speedPerGold = val; return true;
        case SYM_GEN_maxGoldDif_2380: this->f_maxGoldDif = val; return true;
        case SYM_GEN_equilibriumSpeed_2381: this->f_equilibriumSpeed = val; return true;
        case SYM_GEN_leftCounter_2382: this->f_leftCounter = val; return true;
        case SYM_GEN_rightCounter_2383: this->f_rightCounter = val; return true;
        case SYM_GEN_leftCounterDefaultPos_2384: this->f_leftCounterDefaultPos = val; return true;
        case SYM_GEN_rightCounterDefaultPos_2385: this->f_rightCounterDefaultPos = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Scale::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_ready_deferred_461: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_getCounterValue_2255: return true;
        case SYM_GEN_getCounterValue2_2386: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_updateScale_2387: return true;
        case SYM_GEN_onAffectedItemAdded_433: return true;
        case SYM_GEN_onAffectedItemRemoved_434: return true;
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_updateCounterPositions_2388: return true;
        case SYM_GEN_rotateTo_474: return true;
        case SYM_GEN_onDraggedWithParentEnd_716: return true;
        case SYM_GEN_onCalcTradeChance_1729: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Scale::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_ready_deferred_461: out = fn_ready_deferred(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_getCounterValue_2255: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_getCounterValue2_2386: out = fn_getCounterValue2(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_updateScale_2387: out = fn_updateScale(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_433: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_434: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_updateCounterPositions_2388: out = fn_updateCounterPositions(args, argc); return true;
        case SYM_GEN_rotateTo_474: out = fn_rotateTo(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_716: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1729: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Scale::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_ready_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_ready_deferred_461, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2388, nullptr, 0);
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
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580));
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t532 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
            gd::GdArr* _t533 = (_t532.kind == gd::GdVal::Kind::Arr) ? _t532.arr : nullptr;
            uint32_t _len__t534 = _t533 ? _t533->len : 0u;
            for (uint32_t _t534 = 0; _t534 < _len__t534; ++_t534) {
                gd::GdVal lv_item = _t533->data[_t534];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_390, nullptr, 0));
            }
        }
    }
    else {
        {
            gd::GdVal _t535 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_nocache_419, _ca, 1); })());
            gd::GdArr* _t536 = (_t535.kind == gd::GdVal::Kind::Arr) ? _t535.arr : nullptr;
            uint32_t _len__t537 = _t536 ? _t536->len : 0u;
            for (uint32_t _t537 = 0; _t537 < _len__t537; ++_t537) {
                gd::GdVal lv_item = _t536->data[_t537];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_390, nullptr, 0));
            }
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_getCounterValue2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2255, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_c1 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2255, nullptr, 0);
    gd::GdVal lv_c2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue2_2386, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerGold, gd::gd_min(lv_c1, lv_c2))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::gd_abs(gd::gd_sub(lv_c1, lv_c2)), this->f_maxGoldDif)))) {
        {
            gd::GdVal _t538 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
            gd::GdArr* _t539 = (_t538.kind == gd::GdVal::Kind::Arr) ? _t538.arr : nullptr;
            uint32_t _len__t540 = _t539 ? _t539->len : 0u;
            for (uint32_t _t540 = 0; _t540 < _len__t540; ++_t540) {
                gd::GdVal lv_item = _t539->data[_t540];
                (void)([&]() { gd::GdVal _ca[] = {this->f_equilibriumSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            }
        }
        {
            gd::GdVal _t541 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
            gd::GdArr* _t542 = (_t541.kind == gd::GdVal::Kind::Arr) ? _t541.arr : nullptr;
            uint32_t _len__t543 = _t542 ? _t542->len : 0u;
            for (uint32_t _t543 = 0; _t543 < _len__t543; ++_t543) {
                gd::GdVal lv_item = _t542->data[_t543];
                (void)([&]() { gd::GdVal _ca[] = {this->f_equilibriumSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_curRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0);
    gd::GdVal lv_curMana = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curMana, lv_curRegen)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curRegen, lv_curMana)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    }
    else {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_flip_1637, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_updateScale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_c1 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2255, nullptr, 0);
    gd::GdVal lv_c2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue2_2386, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2387, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2387, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2387, nullptr, 0);
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
    (void)([&]() { gd::GdVal _ca[] = {lv_targetRotation, lv_duration}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_rotateTo_474, _ca, 2, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2388, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentEnd_716, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2388, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_speedPerGold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxGoldDif = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_equilibriumSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_gooblingDescriptor_2402: out = this->f_gooblingDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gooblingDescriptor_2402: this->f_gooblingDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_453: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_getGatedDescriptor_952: return true;
        case SYM_GEN_canAffect_global_1918: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_453: out = fn_onBought(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_952: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_canAffect_global_1918: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t544 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t545 = (_t544.kind == gd::GdVal::Kind::Arr) ? _t544.arr : nullptr;
        uint32_t _len__t546 = _t545 ? _t545->len : 0u;
        for (uint32_t _t546 = 0; _t546 < _len__t546; ++_t546) {
            gd::GdVal lv_item = _t545->data[_t546];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_1918, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_onItemActivated_934, _ca, 1); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_gooblingDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Goobling", 8u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
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
        case SYM_GEN_staminaAcc_2432: out = this->f_staminaAcc; return true;
        case SYM_GEN_staminaNeeded_2433: out = this->f_staminaNeeded; return true;
        case SYM_GEN_stamina_2059: out = this->f_stamina; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaAcc_2432: this->f_staminaAcc = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaNeeded_2433: this->f_staminaNeeded = val; return true;
        case SYM_GEN_stamina_2059: this->f_stamina = val; return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemUsedStamina_2434: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemUsedStamina_2434: out = fn_onItemUsedStamina(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canUseStamina_292, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_staminaAcc = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    {
        gd::GdVal _t547 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t548 = (_t547.kind == gd::GdVal::Kind::Arr) ? _t547.arr : nullptr;
        uint32_t _len__t549 = _t548 ? _t548->len : 0u;
        for (uint32_t _t549 = 0; _t549 < _len__t549; ++_t549) {
            gd::GdVal lv_item = _t548->data[_t549];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used_stamina", 12u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemUsedStamina", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
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
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stamina, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_316, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
            lv_activating = gd::GdVal::from_bool(true);
        }
        this->f_staminaAcc = gd::gd_coerce_float(gd::gd_sub(this->f_staminaAcc, this->f_staminaNeeded));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_staminaAcc, this->f_staminaNeeded), lv_activating}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_staminaNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminat", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_manaNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_speedReduction_2464: out = this->f_speedReduction; return true;
        case SYM_GEN_damBonusFactor_2373: out = this->f_damBonusFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedReduction_2464: this->f_speedReduction = val; return true;
        case SYM_GEN_damBonusFactor_2373: this->f_damBonusFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onWeaponAttacked_946: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_946: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t550 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t551 = (_t550.kind == gd::GdVal::Kind::Arr) ? _t550.arr : nullptr;
        uint32_t _len__t552 = _t551 ? _t551->len : 0u;
        for (uint32_t _t552 = 0; _t552 < _len__t552; ++_t552) {
            gd::GdVal lv_weapon = _t551->data[_t552];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t553 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t554 = (_t553.kind == gd::GdVal::Kind::Arr) ? _t553.arr : nullptr;
        uint32_t _len__t555 = _t554 ? _t554->len : 0u;
        for (uint32_t _t555 = 0; _t555 < _len__t555; ++_t555) {
            gd::GdVal lv_item = _t554->data[_t555];
            (void)([&]() { gd::GdVal _ca[] = {this->f_speedReduction}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_272, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_damBonusFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_304, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), gd::GdVal::from_bool(true), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speedreduction", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damBonusFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dambonus", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_tickI_2497: out = this->f_tickI; return true;
        case SYM_GEN_slow_2498: out = this->f_slow; return true;
        case SYM_GEN_speedUp_2499: out = this->f_speedUp; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_tickI_2497: this->f_tickI = gd::gd_coerce_int(val); return true;
        case SYM_GEN_slow_2498: this->f_slow = val; return true;
        case SYM_GEN_speedUp_2499: this->f_speedUp = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_playActivationSound_146: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playActivationSound_146: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_allItems = gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1280), SYM_GEN_INVENTORY_1089), SYM_GEN_getItems_1510, nullptr, 0), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_73), SYM_GEN_INVENTORY_1089), SYM_GEN_getItems_1510, nullptr, 0));
    {
        gd::GdVal _t556 = gd::gd_iter_seq(gd_ctx.arena, lv_allItems);
        gd::GdArr* _t557 = (_t556.kind == gd::GdVal::Kind::Arr) ? _t556.arr : nullptr;
        uint32_t _len__t558 = _t557 ? _t557->len : 0u;
        for (uint32_t _t558 = 0; _t558 < _len__t558; ++_t558) {
            gd::GdVal lv_item = _t557->data[_t558];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_80, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_slow}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_272, _ca, 1); })();
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
        gd::GdVal _t559 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t560 = (_t559.kind == gd::GdVal::Kind::Arr) ? _t559.arr : nullptr;
        uint32_t _len__t561 = _t560 ? _t560->len : 0u;
        for (uint32_t _t561 = 0; _t561 < _len__t561; ++_t561) {
            gd::GdVal lv_item = _t560->data[_t561];
            if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isCooldownActive_94, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                gd::GdVal lv_cd = gd::call_method(gd_ctx, lv_item, SYM_GEN_getModifiedCooldown_102, nullptr, 0);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_cd, lv_slowestCd)))) {
                    lv_slowestCd = lv_cd;
                    lv_slowestItem = lv_item;
                }
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_speedUp}; return gd::call_method(gd_ctx, lv_slowestItem, SYM_GEN_addSpeed_271, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_slow = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "slow", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speedUp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_poisonNeeded_2517: out = this->f_poisonNeeded; return true;
        case SYM_GEN_critDamage_2518: out = this->f_critDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WarScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonNeeded_2517: this->f_poisonNeeded = val; return true;
        case SYM_GEN_critDamage_2518: this->f_critDamage = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WarScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WarScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Poison_2566)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_84, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t562 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t563 = (_t562.kind == gd::GdVal::Kind::Arr) ? _t562.arr : nullptr;
        uint32_t _len__t564 = _t563 ? _t563->len : 0u;
        for (uint32_t _t564 = 0; _t564 < _len__t564; ++_t564) {
            gd::GdVal lv_item = _t563->data[_t564];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Poison_2566), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_301, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getPoison_1209, nullptr, 0), this->f_poisonNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_poisonNeeded, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_losePoison_1212, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_177, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_critDamage}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritSeverity_183, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_poisonNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poisont", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_critDamage = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "critdam", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_gemColor_991: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.977344), gd::GdVal::from_float(0.8), gd::GdVal::from_int(3LL)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_healReduction_2055: out = this->f_healReduction; return true;
        case SYM_GEN_buffRemoval_2090: out = this->f_buffRemoval; return true;
        case SYM_GEN_gemColor_991: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Amethyst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healReduction_2055: this->f_healReduction = val; return true;
        case SYM_GEN_buffRemoval_2090: this->f_buffRemoval = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Amethyst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_onAttack_1956: return true;
        case SYM_GEN_prepareArmor_979: return true;
        case SYM_GEN_getBaseDescription_986: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Amethyst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1956: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_979: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_getBaseDescription_986: out = fn_getBaseDescription(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Amethyst::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffRemoval, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_370, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0), this->f_healReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1163, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_getBaseDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_234, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_858), SYM_GEN_Godly_2677))))) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Perfect Amethyst_DESCR", 22u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })(), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_639, _ca, 2); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN_getBaseDescription_986, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_healReduction = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_buffRemoval = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__HeroSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroSword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t565 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t566 = (_t565.kind == gd::GdVal::Kind::Arr) ? _t565.arr : nullptr;
        uint32_t _len__t567 = _t566 ? _t566->len : 0u;
        for (uint32_t _t567 = 0; _t567 < _len__t567; ++_t567) {
            gd::GdVal lv_item = _t566->data[_t567];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core_items__HeroSword::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Jump_2639)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_manaGained_1835: out = this->f_manaGained; return true;
        case SYM_GEN_fillingTween_1836: out = this->f_fillingTween; return true;
        case SYM_GEN_filling_1837: out = this->f_filling; return true;
        case SYM_GEN_fillingGlow_1838: out = this->f_fillingGlow; return true;
        case SYM_GEN_fillingHeight_1839: out = this->f_fillingHeight; return true;
        case SYM_GEN_fillingAnimation_1840: out = this->f_fillingAnimation; return true;
        case SYM_GEN_manaNeededForLifesteal_1841: out = this->f_manaNeededForLifesteal; return true;
        case SYM_GEN_dam_935: out = this->f_dam; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Manathirst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaGained_1835: this->f_manaGained = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fillingTween_1836: this->f_fillingTween = val; return true;
        case SYM_GEN_filling_1837: this->f_filling = val; return true;
        case SYM_GEN_fillingGlow_1838: this->f_fillingGlow = val; return true;
        case SYM_GEN_fillingHeight_1839: this->f_fillingHeight = val; return true;
        case SYM_GEN_fillingAnimation_1840: this->f_fillingAnimation = val; return true;
        case SYM_GEN_manaNeededForLifesteal_1841: this->f_manaNeededForLifesteal = val; return true;
        case SYM_GEN_dam_935: this->f_dam = val; return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Manathirst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_tweenFilling_1842: return true;
        case SYM_GEN_onManaChanged_1833: return true;
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Manathirst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_tweenFilling_1842: out = fn_tweenFilling(args, argc); return true;
        case SYM_GEN_onManaChanged_1833: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1842, _ca, 1); })();
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
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getVampirism_1206, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_327, _ca, 3); })();
        }
        gd::GdVal lv_relHeight = gd::gd_div(gd_ctx, this->f_manaGained, this->f_manaNeededForLifesteal);
        (void)([&]() { gd::GdVal _ca[] = {lv_relHeight}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1842, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1842, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaNeededForLifesteal = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__RainbowGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RainbowGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RainbowGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    {
        gd::GdVal _t568 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t569 = (_t568.kind == gd::GdVal::Kind::Arr) ? _t568.arr : nullptr;
        uint32_t _len__t570 = _t569 ? _t569->len : 0u;
        for (uint32_t _t570 = 0; _t570 < _len__t570; ++_t570) {
            gd::GdVal lv_item = _t569->data[_t570];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RainbowGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_poisonTimer_1899: out = this->f_poisonTimer; return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::get_prop(prop, out);
}
bool Gd__gd_core_items__StrongPestilenceFlask::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonTimer_1899: this->f_poisonTimer = val; return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StrongPestilenceFlask::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getAffectedItems_418: return true;
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_poisonTimerTimeout_1900: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::has_own_method(m);
}
bool Gd__gd_core_items__StrongPestilenceFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getAffectedItems_418: out = fn_getAffectedItems(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_poisonTimerTimeout_1900: out = fn_poisonTimerTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StrongPestilenceFlask::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__PestilenceFlask::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_getAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580));
    gd::GdVal lv__r = ([&]() { gd::GdVal _ca[] = {lv_color}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN_getAffectedItems_418, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__cp = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCollisionPoints_404, nullptr, 0);
        gd::GdVal lv__rc = ([&]() { gd::GdVal _ca[] = {lv__cp}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCellsForGlobalPositions_399, _ca, 1); })();
        gd::GdVal lv__cc = ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_413, _ca, 1); })();
        gd::GdVal lv__names = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
        {
            gd::GdVal _t571 = gd::gd_iter_seq(gd_ctx.arena, lv__r);
            gd::GdArr* _t572 = (_t571.kind == gd::GdVal::Kind::Arr) ? _t571.arr : nullptr;
            uint32_t _len__t573 = _t572 ? _t572->len : 0u;
            for (uint32_t _t573 = 0; _t573 < _len__t573; ++_t573) {
                gd::GdVal lv__a = _t572->data[_t573];
                lv__names = gd::gd_add(gd_ctx, lv__names, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1575))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "@", 1u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv__a, SYM_GEN_occupiedCells_50)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, ",", 1u))));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "GRD", 3u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1575))), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fd=", 3u)), ([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " cp=", 4u))), ([&]() { gd::GdVal _ca[] = {lv__cp}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " aff=", 5u))), ([&]() { gd::GdVal _ca[] = {lv__cc}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, lv__names, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n=", 2u))), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv__r, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_trace_diag_1643, _ca, 4); })();
    }
    return lv__r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1753, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_poisonTimer, SYM_GEN_start_1683, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_poisonTimerTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_poisonTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_poisonTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "PoisonTimer", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poisonTimerTimeout", 18u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongPestilenceFlask(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StrongPestilenceFlask>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StrongPestilenceFlask = {CLS_Gd__gd_core_items__StrongPestilenceFlask, "StrongPestilenceFlask", "res://gd_core_items/StrongPestilenceFlask.gd", &META_Gd__gd_core_items__PestilenceFlask, true, _alloc_Gd__gd_core_items__StrongPestilenceFlask, &Gd__gd_core_items__StrongPestilenceFlask::get_static_prop_fn, &Gd__gd_core_items__StrongPestilenceFlask::call_static_fn};
