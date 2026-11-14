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
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofAgility.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ArmoredPowerPuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BigBloodthorne.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BroccoliGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__ChessPiece.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChiliPepper.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DarkRitual.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DragonskinBoots.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ExtraAngy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FrogPrince.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HeartShield.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Joker.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LongSpear.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MegaClover.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__OwlSpirit.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Pot.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Scale.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SlimeTime.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpellScrollNature.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StoneGolem.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__TimeDilator.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WarScythe.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__Amethyst.hpp"
#include "../hdrs/Gd__gd_core_items__HeroicPotion.hpp"
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
    this->f_numStackChangeTypes = gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0);
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
    this->f_shadowOffset = Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_525);
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
    this->f_ownerTypesWithBuildTooltip = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 5); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_BuildViewer_2554), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerStorageBox_2580), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Opponent_2545), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_GridStorage_2610), gd::GdVal::from_bool(true)); return gd::GdVal::from_dict(d); })();
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
        case SYM_GEN_Owner_854: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Owner);
        case SYM_GEN_Type_855: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Type);
        case SYM_GEN_Priority_856: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Priority);
        case SYM_GEN_CraftingPriority_857: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_CraftingPriority);
        case SYM_GEN_Tag_858: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tag);
        case SYM_GEN_Stack_859: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stack);
        case SYM_GEN_Mat_860: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Mat);
        case SYM_GEN_Physics_861: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Physics);
        case SYM_GEN_Rarity_862: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Rarity);
        case SYM_GEN_FaceDirection_863: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_FaceDirection);
        case SYM_GEN_StatModified_864: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StatModified);
        case SYM_GEN_DropResult_865: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_DropResult);
        case SYM_GEN_PickupType_866: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_PickupType);
        case SYM_GEN_Affected_867: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Affected);
        case SYM_GEN_Tiles_868: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tiles);
        case SYM_GEN_ActivationAni_869: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_ActivationAni);
        case SYM_GEN_Stat_870: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stat);
        case SYM_GEN_StackChangeType_871: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StackChangeType);
        case SYM_GEN_affectedColorToTileId_509: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581), gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_868), SYM_GEN_Affected_867)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583), gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_868), SYM_GEN_AffectedSecondary_2611)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Tertiary_2584), gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_868), SYM_GEN_AffectedTertiary_2612)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Lightning_2613), gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_868), SYM_GEN_AffectedLightning_2614)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_rarityColors_511: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.460205), gd::GdVal::from_float(0.874887), gd::GdVal::from_float(0.90625)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.0737), gd::GdVal::from_float(0.337874), gd::GdVal::from_float(0.898438)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.828125), gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.609375), gd::GdVal::from_int(0LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.980469), gd::GdVal::from_float(0.946239), gd::GdVal::from_float(0.582153)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.094223), gd::GdVal::from_float(0.964844), gd::GdVal::from_float(0.250663)}; return gd::make_color_from_args(_ca, 3); })()}));
        case SYM_GEN_offset_516: return gd::GdVal::from_int(40LL);
        case SYM_GEN_impulse_517: return gd::GdVal::from_int(50LL);
        case SYM_GEN_momentumFactor_518: return gd::GdVal::from_float(20.0);
        case SYM_GEN_affectedSoundsVolume_521: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581), gd::gd_neg(gd::GdVal::from_int(8LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Tertiary_2584), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Lightning_2613), gd::gd_neg(gd::GdVal::from_int(1LL))); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_cellSize_522: return gd::GdVal::from_vec2((gd::GdVal::from_int(80LL)).as_float(), (gd::GdVal::from_int(80LL)).as_float());
        case SYM_GEN_halfCellSize_523: return gd::gd_mul(gd::GdVal::from_float(0.5), Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522));
        case SYM_GEN_shadowOffset_shop_524: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        case SYM_GEN_shadowOffset_dropped_525: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(5LL)).as_float());
        case SYM_GEN_shadowOffset_dragged_526: return gd::GdVal::from_vec2((gd::GdVal::from_int(15LL)).as_float(), (gd::GdVal::from_int(15LL)).as_float());
        case SYM_GEN_DRAG_PRIORITY_527: return gd::GdVal::from_int(2LL);
        case SYM_GEN_correction_583: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_x))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_x))).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_y))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_y))).as_float())}));
        case SYM_GEN_angleStep_585: return gd::GdVal::from_int(45LL);
        case SYM_GEN_moveRotationMouseFactor_588: return gd::GdVal::from_float(0.015);
        case SYM_GEN_backforce_589: return gd::GdVal::from_float(5.0);
        case SYM_GEN_fric_590: return gd::GdVal::from_float(15.0);
        case SYM_GEN_maxAngle_591: return gd::GdVal::from_int(10LL);
        case SYM_GEN_moveRotationSpeed_592: return gd::GdVal::from_float(60.0);
        case SYM_GEN_hoverableWhenMenuOpen_598: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_ItemLibrary_2615), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_InfoPanelIcon_2616), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Tooltip_2617), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_RecipeBook_2618), gd::GdVal::from_bool(true)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_MISS_OFFSET_602: return gd::GdVal::from_float(100.0);
        case SYM_GEN_PRE_FUSE_DUR_603: return gd::GdVal::from_float(1.0);
        case SYM_GEN_PRE_FUSE_DUR_COG_604: return gd::GdVal::from_float(0.2);
        case SYM_GEN_FUSE_DUR_605: return gd::GdVal::from_float(1.0);
        case SYM_GEN_TRANSFORMATION_DUR_606: return gd::GdVal::from_float(1.0);
        case SYM_GEN_labelOffsets_613: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2((gd::GdVal::from_int(30LL)).as_float(), (gd::GdVal::from_int(30LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(30LL))).as_float(), (gd::GdVal::from_int(30LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(30LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(30LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(30LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(30LL))).as_float())}));
        case SYM_GEN_SignalConnection_877: return gd::GdVal::from_cls(&META_Gd__gd_core__Item__INNER__SignalConnection);
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
        case SYM_GEN_numStackChangeTypes_510: out = this->f_numStackChangeTypes; return true;
        case SYM_GEN_spriteScale_512: out = this->f_spriteScale; return true;
        case SYM_GEN_hasSquishySprite_513: out = this->f_hasSquishySprite; return true;
        case SYM_GEN_specificDragParticles_514: out = this->f_specificDragParticles; return true;
        case SYM_GEN_dragParticlesEnabled_515: out = this->f_dragParticlesEnabled; return true;
        case SYM_GEN_frictionTime_519: out = this->f_frictionTime; return true;
        case SYM_GEN_totalWeight_520: out = this->f_totalWeight; return true;
        case SYM_GEN_me_528: out = this->f_me; return true;
        case SYM_GEN_mouseIsOverItem_529: out = this->f_mouseIsOverItem; return true;
        case SYM_GEN_hovered_530: out = this->f_hovered; return true;
        case SYM_GEN_focus_531: out = this->f_focus; return true;
        case SYM_GEN_spotlight_532: out = this->f_spotlight; return true;
        case SYM_GEN_collisionShape_533: out = this->f_collisionShape; return true;
        case SYM_GEN_wasJustCrafted_534: out = this->f_wasJustCrafted; return true;
        case SYM_GEN_pickupPosition_535: out = this->f_pickupPosition; return true;
        case SYM_GEN_pickupRotation_536: out = this->f_pickupRotation; return true;
        case SYM_GEN_pickupTopLeftCell_537: out = this->f_pickupTopLeftCell; return true;
        case SYM_GEN_pickupFaceDirection_538: out = this->f_pickupFaceDirection; return true;
        case SYM_GEN_sameOrientationAsPickup_539: out = this->f_sameOrientationAsPickup; return true;
        case SYM_GEN_movebackTween_540: out = this->f_movebackTween; return true;
        case SYM_GEN_rotationTween_541: out = this->f_rotationTween; return true;
        case SYM_GEN_pickingEnabled_542: out = this->f_pickingEnabled; return true;
        case SYM_GEN_tooltipEnabled_543: out = this->f_tooltipEnabled; return true;
        case SYM_GEN_hoverResponseEnabled_544: out = this->f_hoverResponseEnabled; return true;
        case SYM_GEN_focusEnabled_545: out = this->f_focusEnabled; return true;
        case SYM_GEN_affectedCellsActive_546: out = this->f_affectedCellsActive; return true;
        case SYM_GEN_affordable_547: out = this->f_affordable; return true;
        case SYM_GEN_momentumStrength_548: out = this->f_momentumStrength; return true;
        case SYM_GEN_momentum_549: out = this->f_momentum; return true;
        case SYM_GEN_tooltip_550: out = this->f_tooltip; return true;
        case SYM_GEN_tooltipMargin_551: out = this->f_tooltipMargin; return true;
        case SYM_GEN_tooltipUpdateQueued_552: out = this->f_tooltipUpdateQueued; return true;
        case SYM_GEN_shadows_553: out = this->f_shadows; return true;
        case SYM_GEN_spritesWithShadows_554: out = this->f_spritesWithShadows; return true;
        case SYM_GEN_shadowOffset_555: out = this->f_shadowOffset; return true;
        case SYM_GEN_shadowTween_556: out = this->f_shadowTween; return true;
        case SYM_GEN_dropFrame_557: out = this->f_dropFrame; return true;
        case SYM_GEN_pickupFrame_558: out = this->f_pickupFrame; return true;
        case SYM_GEN_mouseWheelRotationReadyTime_559: out = this->f_mouseWheelRotationReadyTime; return true;
        case SYM_GEN_notEnoughGoldLabelReadyTime_560: out = this->f_notEnoughGoldLabelReadyTime; return true;
        case SYM_GEN_averagedPosition_561: out = this->f_averagedPosition; return true;
        case SYM_GEN_impactSoundVolume_562: out = this->f_impactSoundVolume; return true;
        case SYM_GEN_progressMaterial_563: out = this->f_progressMaterial; return true;
        case SYM_GEN_insideRotationNode_564: out = this->f_insideRotationNode; return true;
        case SYM_GEN_draggedInsideItems_565: out = this->f_draggedInsideItems; return true;
        case SYM_GEN_draggingParent_566: out = this->f_draggingParent; return true;
        case SYM_GEN_sold_567: out = this->f_sold; return true;
        case SYM_GEN_lastVelocity_568: out = this->f_lastVelocity; return true;
        case SYM_GEN_lastCollisionPos_569: out = this->f_lastCollisionPos; return true;
        case SYM_GEN_lastCollider_570: out = this->f_lastCollider; return true;
        case SYM_GEN_impactSoundReadyTime_571: out = this->f_impactSoundReadyTime; return true;
        case SYM_GEN_globalAffectVisuals_572: out = this->f_globalAffectVisuals; return true;
        case SYM_GEN_bondedBaseItem_573: out = this->f_bondedBaseItem; return true;
        case SYM_GEN_bondedIngredients_574: out = this->f_bondedIngredients; return true;
        case SYM_GEN_locked_575: out = this->f_locked; return true;
        case SYM_GEN_bound_576: out = this->f_bound; return true;
        case SYM_GEN_curRecipe_577: out = this->f_curRecipe; return true;
        case SYM_GEN_bondVisuals_578: out = this->f_bondVisuals; return true;
        case SYM_GEN_craftingLabel_579: out = this->f_craftingLabel; return true;
        case SYM_GEN_craftingAniReadyTime_580: out = this->f_craftingAniReadyTime; return true;
        case SYM_GEN_pooled_581: out = this->f_pooled; return true;
        case SYM_GEN_initialized_582: out = this->f_initialized; return true;
        case SYM_GEN_canAffectVisuals_584: out = this->f_canAffectVisuals; return true;
        case SYM_GEN_rotationMomentum_586: out = this->f_rotationMomentum; return true;
        case SYM_GEN_bonusRotation_587: out = this->f_bonusRotation; return true;
        case SYM_GEN_brightColor_593: out = this->f_brightColor; return true;
        case SYM_GEN_defaultColor_594: out = this->f_defaultColor; return true;
        case SYM_GEN_buildIntoRecipesTooltip_595: out = this->f_buildIntoRecipesTooltip; return true;
        case SYM_GEN_owningBuildIntoRecipesTooltip_596: out = this->f_owningBuildIntoRecipesTooltip; return true;
        case SYM_GEN_ownerTypesWithBuildTooltip_597: out = this->f_ownerTypesWithBuildTooltip; return true;
        case SYM_GEN_shaderTween_599: out = this->f_shaderTween; return true;
        case SYM_GEN_canCancelShaderTween_600: out = this->f_canCancelShaderTween; return true;
        case SYM_GEN_nonRotatedProgress_601: out = this->f_nonRotatedProgress; return true;
        case SYM_GEN_fusing_607: out = this->f_fusing; return true;
        case SYM_GEN_willBeConsumed_608: out = this->f_willBeConsumed; return true;
        case SYM_GEN_fuseParticles1_609: out = this->f_fuseParticles1; return true;
        case SYM_GEN_fuseParticles2_610: out = this->f_fuseParticles2; return true;
        case SYM_GEN_fuseTween_611: out = this->f_fuseTween; return true;
        case SYM_GEN_fusingBonds_612: out = this->f_fusingBonds; return true;
        case SYM_GEN_collisionMap_614: out = this->f_collisionMap; return true;
        case SYM_GEN_animation_615: out = this->f_animation; return true;
        case SYM_GEN_sprite_616: out = this->f_sprite; return true;
        case SYM_GEN_clickArea_617: out = this->f_clickArea; return true;
        case SYM_GEN_dragParticles_618: out = this->f_dragParticles; return true;
        case SYM_GEN_sockets_619: out = this->f_sockets; return true;
        case SYM_GEN_lock_620: out = this->f_lock; return true;
        case SYM_GEN_lockAnimation_621: out = this->f_lockAnimation; return true;
        case SYM_GEN_baseBounce_622: out = this->f_baseBounce; return true;
        case SYM_GEN_baseFriction_623: out = this->f_baseFriction; return true;
        case SYM_GEN_Owner_854: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Owner); return true;
        case SYM_GEN_Type_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Type); return true;
        case SYM_GEN_Priority_856: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Priority); return true;
        case SYM_GEN_CraftingPriority_857: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_CraftingPriority); return true;
        case SYM_GEN_Tag_858: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tag); return true;
        case SYM_GEN_Stack_859: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stack); return true;
        case SYM_GEN_Mat_860: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Mat); return true;
        case SYM_GEN_Physics_861: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Physics); return true;
        case SYM_GEN_Rarity_862: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Rarity); return true;
        case SYM_GEN_FaceDirection_863: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_FaceDirection); return true;
        case SYM_GEN_StatModified_864: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StatModified); return true;
        case SYM_GEN_DropResult_865: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_DropResult); return true;
        case SYM_GEN_PickupType_866: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_PickupType); return true;
        case SYM_GEN_Affected_867: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Affected); return true;
        case SYM_GEN_Tiles_868: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tiles); return true;
        case SYM_GEN_ActivationAni_869: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_ActivationAni); return true;
        case SYM_GEN_Stat_870: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stat); return true;
        case SYM_GEN_StackChangeType_871: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StackChangeType); return true;
        case SYM_GEN_SignalConnection_877: out = gd::GdVal::from_cls(&META_Gd__gd_core__Item__INNER__SignalConnection); return true;
        case SYM_GEN_affectedColorToTileId_509: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_rarityColors_511: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_offset_516: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_impulse_517: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_momentumFactor_518: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_affectedSoundsVolume_521: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_cellSize_522: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_halfCellSize_523: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_shop_524: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_dropped_525: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_dragged_526: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_DRAG_PRIORITY_527: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_correction_583: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_angleStep_585: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_moveRotationMouseFactor_588: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_backforce_589: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_fric_590: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_maxAngle_591: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_moveRotationSpeed_592: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_hoverableWhenMenuOpen_598: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_MISS_OFFSET_602: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PRE_FUSE_DUR_603: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PRE_FUSE_DUR_COG_604: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FUSE_DUR_605: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_TRANSFORMATION_DUR_606: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_labelOffsets_613: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::get_prop(prop, out);
}
bool Gd__gd_core__Item::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numStackChangeTypes_510: this->f_numStackChangeTypes = val; return true;
        case SYM_GEN_spriteScale_512: this->f_spriteScale = val; return true;
        case SYM_GEN_hasSquishySprite_513: this->f_hasSquishySprite = val; return true;
        case SYM_GEN_specificDragParticles_514: this->f_specificDragParticles = val; return true;
        case SYM_GEN_dragParticlesEnabled_515: this->f_dragParticlesEnabled = val; return true;
        case SYM_GEN_frictionTime_519: this->f_frictionTime = val; return true;
        case SYM_GEN_totalWeight_520: this->f_totalWeight = gd::gd_coerce_float(val); return true;
        case SYM_GEN_me_528: this->f_me = val; return true;
        case SYM_GEN_mouseIsOverItem_529: this->f_mouseIsOverItem = val; return true;
        case SYM_GEN_hovered_530: this->f_hovered = val; return true;
        case SYM_GEN_focus_531: this->f_focus = val; return true;
        case SYM_GEN_spotlight_532: this->f_spotlight = val; return true;
        case SYM_GEN_collisionShape_533: this->f_collisionShape = val; return true;
        case SYM_GEN_wasJustCrafted_534: this->f_wasJustCrafted = val; return true;
        case SYM_GEN_pickupPosition_535: this->f_pickupPosition = val; return true;
        case SYM_GEN_pickupRotation_536: this->f_pickupRotation = gd::gd_coerce_float(val); return true;
        case SYM_GEN_pickupTopLeftCell_537: this->f_pickupTopLeftCell = val; return true;
        case SYM_GEN_pickupFaceDirection_538: this->f_pickupFaceDirection = gd::gd_coerce_int(val); return true;
        case SYM_GEN_sameOrientationAsPickup_539: this->f_sameOrientationAsPickup = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_movebackTween_540: this->f_movebackTween = val; return true;
        case SYM_GEN_rotationTween_541: this->f_rotationTween = val; return true;
        case SYM_GEN_pickingEnabled_542: this->f_pickingEnabled = val; return true;
        case SYM_GEN_tooltipEnabled_543: this->f_tooltipEnabled = val; return true;
        case SYM_GEN_hoverResponseEnabled_544: this->f_hoverResponseEnabled = val; return true;
        case SYM_GEN_focusEnabled_545: this->f_focusEnabled = val; return true;
        case SYM_GEN_affectedCellsActive_546: this->f_affectedCellsActive = val; return true;
        case SYM_GEN_affordable_547: this->f_affordable = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_momentumStrength_548: this->f_momentumStrength = gd::gd_coerce_float(val); return true;
        case SYM_GEN_momentum_549: this->f_momentum = val; return true;
        case SYM_GEN_tooltip_550: this->f_tooltip = val; return true;
        case SYM_GEN_tooltipMargin_551: this->f_tooltipMargin = val; return true;
        case SYM_GEN_tooltipUpdateQueued_552: this->f_tooltipUpdateQueued = val; return true;
        case SYM_GEN_shadows_553: this->f_shadows = val; return true;
        case SYM_GEN_spritesWithShadows_554: this->f_spritesWithShadows = val; return true;
        case SYM_GEN_shadowOffset_555: this->f_shadowOffset = val; return true;
        case SYM_GEN_shadowTween_556: this->f_shadowTween = val; return true;
        case SYM_GEN_dropFrame_557: this->f_dropFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_pickupFrame_558: this->f_pickupFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_mouseWheelRotationReadyTime_559: this->f_mouseWheelRotationReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_notEnoughGoldLabelReadyTime_560: this->f_notEnoughGoldLabelReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_averagedPosition_561: this->f_averagedPosition = val; return true;
        case SYM_GEN_impactSoundVolume_562: this->f_impactSoundVolume = gd::gd_coerce_float(val); return true;
        case SYM_GEN_progressMaterial_563: this->f_progressMaterial = val; return true;
        case SYM_GEN_insideRotationNode_564: this->f_insideRotationNode = val; return true;
        case SYM_GEN_draggedInsideItems_565: this->f_draggedInsideItems = val; return true;
        case SYM_GEN_draggingParent_566: this->f_draggingParent = val; return true;
        case SYM_GEN_sold_567: this->f_sold = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_lastVelocity_568: this->f_lastVelocity = val; return true;
        case SYM_GEN_lastCollisionPos_569: this->f_lastCollisionPos = val; return true;
        case SYM_GEN_lastCollider_570: this->f_lastCollider = val; return true;
        case SYM_GEN_impactSoundReadyTime_571: this->f_impactSoundReadyTime = val; return true;
        case SYM_GEN_globalAffectVisuals_572: this->f_globalAffectVisuals = val; return true;
        case SYM_GEN_bondedBaseItem_573: this->f_bondedBaseItem = val; return true;
        case SYM_GEN_bondedIngredients_574: this->f_bondedIngredients = val; return true;
        case SYM_GEN_locked_575: this->f_locked = val; return true;
        case SYM_GEN_bound_576: this->f_bound = val; return true;
        case SYM_GEN_curRecipe_577: this->f_curRecipe = val; return true;
        case SYM_GEN_bondVisuals_578: this->f_bondVisuals = val; return true;
        case SYM_GEN_craftingLabel_579: this->f_craftingLabel = val; return true;
        case SYM_GEN_craftingAniReadyTime_580: this->f_craftingAniReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_pooled_581: this->f_pooled = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_initialized_582: this->f_initialized = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_canAffectVisuals_584: this->f_canAffectVisuals = val; return true;
        case SYM_GEN_rotationMomentum_586: this->f_rotationMomentum = val; return true;
        case SYM_GEN_bonusRotation_587: this->f_bonusRotation = val; return true;
        case SYM_GEN_brightColor_593: this->f_brightColor = val; return true;
        case SYM_GEN_defaultColor_594: this->f_defaultColor = val; return true;
        case SYM_GEN_buildIntoRecipesTooltip_595: this->f_buildIntoRecipesTooltip = val; return true;
        case SYM_GEN_owningBuildIntoRecipesTooltip_596: this->f_owningBuildIntoRecipesTooltip = val; return true;
        case SYM_GEN_ownerTypesWithBuildTooltip_597: this->f_ownerTypesWithBuildTooltip = val; return true;
        case SYM_GEN_shaderTween_599: this->f_shaderTween = val; return true;
        case SYM_GEN_canCancelShaderTween_600: this->f_canCancelShaderTween = val; return true;
        case SYM_GEN_nonRotatedProgress_601: this->f_nonRotatedProgress = val; return true;
        case SYM_GEN_fusing_607: this->f_fusing = val; return true;
        case SYM_GEN_willBeConsumed_608: this->f_willBeConsumed = val; return true;
        case SYM_GEN_fuseParticles1_609: this->f_fuseParticles1 = val; return true;
        case SYM_GEN_fuseParticles2_610: this->f_fuseParticles2 = val; return true;
        case SYM_GEN_fuseTween_611: this->f_fuseTween = val; return true;
        case SYM_GEN_fusingBonds_612: this->f_fusingBonds = val; return true;
        case SYM_GEN_collisionMap_614: this->f_collisionMap = val; return true;
        case SYM_GEN_animation_615: this->f_animation = val; return true;
        case SYM_GEN_sprite_616: this->f_sprite = val; return true;
        case SYM_GEN_clickArea_617: this->f_clickArea = val; return true;
        case SYM_GEN_dragParticles_618: this->f_dragParticles = val; return true;
        case SYM_GEN_sockets_619: this->f_sockets = val; return true;
        case SYM_GEN_lock_620: this->f_lock = val; return true;
        case SYM_GEN_lockAnimation_621: this->f_lockAnimation = val; return true;
        case SYM_GEN_baseBounce_622: this->f_baseBounce = gd::gd_coerce_float(val); return true;
        case SYM_GEN_baseFriction_623: this->f_baseFriction = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Item::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN__readyInit_142: return true;
        case SYM_GEN_preset_626: return true;
        case SYM_GEN_initPhysicsMaterial_627: return true;
        case SYM_GEN_getShadowOffset_628: return true;
        case SYM_GEN_initRecipeBook_629: return true;
        case SYM_GEN_initItemLibrary_630: return true;
        case SYM_GEN_setSpotlight_631: return true;
        case SYM_GEN_initTitle_632: return true;
        case SYM_GEN_initTooltip_633: return true;
        case SYM_GEN_initBuildViewer_634: return true;
        case SYM_GEN_initBuildViewerIcon_635: return true;
        case SYM_GEN_initInfoPanelIcon_636: return true;
        case SYM_GEN_initGridStorageIcon_637: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_persistDataInShop_640: return true;
        case SYM_GEN_getTranslatedName_641: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_insertParameters_643: return true;
        case SYM_GEN_insertParameter_644: return true;
        case SYM_GEN_getModeDescription_645: return true;
        case SYM_GEN_getFlavorText_646: return true;
        case SYM_GEN_disablePicking_647: return true;
        case SYM_GEN_enablePicking_648: return true;
        case SYM_GEN_enableTooltip_649: return true;
        case SYM_GEN_disableTooltip_650: return true;
        case SYM_GEN_disableFocus_651: return true;
        case SYM_GEN_enableFocus_652: return true;
        case SYM_GEN_setEditMode_653: return true;
        case SYM_GEN_setShadowAlpha_654: return true;
        case SYM_GEN_getTopLeftGlobal_655: return true;
        case SYM_GEN_getBottomRightGlobal_656: return true;
        case SYM_GEN_getBottomCenter_657: return true;
        case SYM_GEN_getInventory_658: return true;
        case SYM_GEN_removeFromInventory_662: return true;
        case SYM_GEN_playAffectedPlacedAnimation_663: return true;
        case SYM_GEN_clearCanAffectVisuals_664: return true;
        case SYM_GEN_liesInStorage_665: return true;
        case SYM_GEN_pushToStorage_666: return true;
        case SYM_GEN_addToStorageBox_667: return true;
        case SYM_GEN_removeFromStorage_668: return true;
        case SYM_GEN_onStorageLeft_669: return true;
        case SYM_GEN_isInGridStorage_670: return true;
        case SYM_GEN_getGridStorageProxy_671: return true;
        case SYM_GEN_onAddedToGridStorage_672: return true;
        case SYM_GEN_onRemovedFromGridStorage_673: return true;
        case SYM_GEN_makeGrabbable_674: return true;
        case SYM_GEN_moveToFreeSpaceInStorage_675: return true;
        case SYM_GEN_checkIfOutofStorageBounds_676: return true;
        case SYM_GEN_checkIfOutofStorageBounds2_677: return true;
        case SYM_GEN_checkIfOutofStorageBounds3_678: return true;
        case SYM_GEN_findFreeSpace_679: return true;
        case SYM_GEN_unclip_680: return true;
        case SYM_GEN_onAddedToStorageBox_681: return true;
        case SYM_GEN__process_682: return true;
        case SYM_GEN__integrate_forces_683: return true;
        case SYM_GEN_updateShadow_684: return true;
        case SYM_GEN_lerpAngle_local_685: return true;
        case SYM_GEN_updateInsideRotationNode_686: return true;
        case SYM_GEN_spawnRotationSparks_687: return true;
        case SYM_GEN_highlight_688: return true;
        case SYM_GEN_unhighlight_689: return true;
        case SYM_GEN_setBright_690: return true;
        case SYM_GEN_resetBright_691: return true;
        case SYM_GEN_getHoverPriority_692: return true;
        case SYM_GEN_canGainFocus_693: return true;
        case SYM_GEN_gainFocus_694: return true;
        case SYM_GEN_respondToHover_695: return true;
        case SYM_GEN_canShowBuildIntoRecipesTooltip_696: return true;
        case SYM_GEN_canShowSubBuildIntoRecipesTooltip_697: return true;
        case SYM_GEN_showBuildIntoRecipesTooltip_698: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN_getRecipeDescriptor_701: return true;
        case SYM_GEN_hideBuildIntoRecipesTooltip_702: return true;
        case SYM_GEN_loseFocus_703: return true;
        case SYM_GEN_respondToHoverEnd_704: return true;
        case SYM_GEN_activateDragParticles_705: return true;
        case SYM_GEN_deactivateDragParticles_706: return true;
        case SYM_GEN_updateTooltip_707: return true;
        case SYM_GEN_queueTooltipUpdate_708: return true;
        case SYM_GEN_clearTooltip_709: return true;
        case SYM_GEN_mouseEntered_710: return true;
        case SYM_GEN_hover_711: return true;
        case SYM_GEN_mouseExited_712: return true;
        case SYM_GEN_hoverEnd_713: return true;
        case SYM_GEN_isHovered_714: return true;
        case SYM_GEN_getScaleProp_715: return true;
        case SYM_GEN_setSpriteScale_716: return true;
        case SYM_GEN_pickup_717: return true;
        case SYM_GEN_onDraggedWithParentStart_718: return true;
        case SYM_GEN_finishMoveback_719: return true;
        case SYM_GEN_onDraggedWithParentEnd_720: return true;
        case SYM_GEN_canSnap_721: return true;
        case SYM_GEN_reactToDropResult_722: return true;
        case SYM_GEN_drop_723: return true;
        case SYM_GEN_showClickArea_724: return true;
        case SYM_GEN_cancelDrag_725: return true;
        case SYM_GEN_emptyTweenCallback_726: return true;
        case SYM_GEN_killMovebackTween_727: return true;
        case SYM_GEN_setSpriteGlobalPos_728: return true;
        case SYM_GEN_dropIntoInventory_729: return true;
        case SYM_GEN_finishInsideItemsRotation_730: return true;
        case SYM_GEN_pushDraggedItemsToStorage_731: return true;
        case SYM_GEN_reparentItemsInside_732: return true;
        case SYM_GEN_clearDraggedInsideItems_733: return true;
        case SYM_GEN_showSockets_734: return true;
        case SYM_GEN_hideSockets_735: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN_canBeSold_737: return true;
        case SYM_GEN_isPickingPossible_738: return true;
        case SYM_GEN_canBePicked_739: return true;
        case SYM_GEN_canBeDraggedWithBag_740: return true;
        case SYM_GEN_canBeDropped_741: return true;
        case SYM_GEN__input_742: return true;
        case SYM_GEN_resetSprite_743: return true;
        case SYM_GEN_combatToShop_744: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_startFusing_inShop_747: return true;
        case SYM_GEN_getCraftingPriority_748: return true;
        case SYM_GEN_addToCraftingQueue_749: return true;
        case SYM_GEN_combatToTitle_750: return true;
        case SYM_GEN_readyToFuse_751: return true;
        case SYM_GEN_startFusing_752: return true;
        case SYM_GEN_readyToTransform_753: return true;
        case SYM_GEN_giveGold_754: return true;
        case SYM_GEN_getTranslatedTypeName_755: return true;
        case SYM_GEN_getTypeDescription_756: return true;
        case SYM_GEN_getTranslatedRarity_757: return true;
        case SYM_GEN_logCooldown_759: return true;
        case SYM_GEN_getCombatDisplayAccuracy_760: return true;
        case SYM_GEN_getDisplayCritChance_761: return true;
        case SYM_GEN_getSalesMultiplier_762: return true;
        case SYM_GEN_prepareDiscard_763: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN_popIn_765: return true;
        case SYM_GEN_disappear_766: return true;
        case SYM_GEN_appearInLibrary_767: return true;
        case SYM_GEN_createParticles_768: return true;
        case SYM_GEN_deactivateParticles_769: return true;
        case SYM_GEN_makeRigidBody_770: return true;
        case SYM_GEN_dropImpulse_771: return true;
        case SYM_GEN_makeNonRigidBody_772: return true;
        case SYM_GEN_rollShopChance_773: return true;
        case SYM_GEN__physics_process_774: return true;
        case SYM_GEN_playActivationAnimation_Scale_775: return true;
        case SYM_GEN_playActivationAnimation_Jump_776: return true;
        case SYM_GEN_playActivationAnimation_JumpSquash_777: return true;
        case SYM_GEN_playActivationAnimation_778: return true;
        case SYM_GEN_playActivationSound_150: return true;
        case SYM_GEN_clearSpriteMaterial_779: return true;
        case SYM_GEN_giveProgressMaterial_780: return true;
        case SYM_GEN_getTextureSize_781: return true;
        case SYM_GEN_scaleToFit_782: return true;
        case SYM_GEN_getSpriteOffset_783: return true;
        case SYM_GEN_getGlobalCenter_784: return true;
        case SYM_GEN_getTextureSize_local_785: return true;
        case SYM_GEN_scaleToFit_local_786: return true;
        case SYM_GEN_getSpriteOffset_local_787: return true;
        case SYM_GEN_setTexture_788: return true;
        case SYM_GEN_updateShadowTexture_789: return true;
        case SYM_GEN_initSpriteMaterial_790: return true;
        case SYM_GEN_updateShaderRotation_791: return true;
        case SYM_GEN_allowCancelShaderTween_792: return true;
        case SYM_GEN_showCooldownSmooth_793: return true;
        case SYM_GEN_showCooldown_794: return true;
        case SYM_GEN_createAnimation_795: return true;
        case SYM_GEN_playAnimation_796: return true;
        case SYM_GEN_hasInventoryDuration_797: return true;
        case SYM_GEN_reveal_798: return true;
        case SYM_GEN_setRevealed_799: return true;
        case SYM_GEN_isCrafted_800: return true;
        case SYM_GEN_isMovingBack_801: return true;
        case SYM_GEN__notification_802: return true;
        case SYM_GEN_getAllInInventoryOfType_803: return true;
        case SYM_GEN_countAllInInventoryOfType_804: return true;
        case SYM_GEN_isTypeInInventory_805: return true;
        case SYM_GEN_isRecipeFinished_806: return true;
        case SYM_GEN_canStartNewRecipe_807: return true;
        case SYM_GEN_getRecipes_808: return true;
        case SYM_GEN_breakBondVisual_809: return true;
        case SYM_GEN_removeBondedBaseItem_810: return true;
        case SYM_GEN_removeBondedIngredient_811: return true;
        case SYM_GEN_removeAllIngredients_812: return true;
        case SYM_GEN_considerAsBond_813: return true;
        case SYM_GEN_addBondedIngredient_814: return true;
        case SYM_GEN_addToBaseItem_815: return true;
        case SYM_GEN_playBondAnimation_816: return true;
        case SYM_GEN_playBondFailedAnimation_817: return true;
        case SYM_GEN_isCatalystBond_818: return true;
        case SYM_GEN_isLocked_819: return true;
        case SYM_GEN_canLockBag_820: return true;
        case SYM_GEN_canBeLocked_821: return true;
        case SYM_GEN_setLocked_822: return true;
        case SYM_GEN_unlockCombining_823: return true;
        case SYM_GEN_lockCombining_824: return true;
        case SYM_GEN_showLockLabel_825: return true;
        case SYM_GEN_getLockPosition_826: return true;
        case SYM_GEN_setBoundAsIngredient_827: return true;
        case SYM_GEN_canPreviewFusions_828: return true;
        case SYM_GEN_getCraftingPreviewPosition_829: return true;
        case SYM_GEN_previewFusions_830: return true;
        case SYM_GEN_previewRecipeIngredients_831: return true;
        case SYM_GEN_previewFusionToItem_832: return true;
        case SYM_GEN_hasShopItemCraftCandidates_833: return true;
        case SYM_GEN_typeInIngredients_834: return true;
        case SYM_GEN_getTextEffect_835: return true;
        case SYM_GEN_getFusionItemName_836: return true;
        case SYM_GEN_showProgressLabel_837: return true;
        case SYM_GEN_onCraftingLabelReturned_838: return true;
        case SYM_GEN_createBondVisual_839: return true;
        case SYM_GEN_updateBondVisuals_840: return true;
        case SYM_GEN_fuse_841: return true;
        case SYM_GEN_onFusingAsIngredient_842: return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: return true;
        case SYM_GEN_createCraftedShockwave_844: return true;
        case SYM_GEN_finishFusing_845: return true;
        case SYM_GEN_allowGeneratingFusionItem_846: return true;
        case SYM_GEN_catalystFusingFinished_847: return true;
        case SYM_GEN_onFusingFinished_848: return true;
        case SYM_GEN_onCraftedFrom_849: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN_playCraftedAnimation_851: return true;
        case SYM_GEN_onRestoreSnapshot_852: return true;
        case SYM_GEN_getShopPriority_853: return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::has_own_method(m);
}
bool Gd__gd_core__Item::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        case SYM_GEN_getNumTooltipStats_624: out = sf_getNumTooltipStats(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumStackChangeTypes_625: out = sf_getNumStackChangeTypes(gd_ctx, args, argc); return true;
        case SYM_GEN_preset_626: out = fn_preset(args, argc); return true;
        case SYM_GEN_initPhysicsMaterial_627: out = fn_initPhysicsMaterial(args, argc); return true;
        case SYM_GEN_getShadowOffset_628: out = fn_getShadowOffset(args, argc); return true;
        case SYM_GEN_initRecipeBook_629: out = fn_initRecipeBook(args, argc); return true;
        case SYM_GEN_initItemLibrary_630: out = fn_initItemLibrary(args, argc); return true;
        case SYM_GEN_setSpotlight_631: out = fn_setSpotlight(args, argc); return true;
        case SYM_GEN_initTitle_632: out = fn_initTitle(args, argc); return true;
        case SYM_GEN_initTooltip_633: out = fn_initTooltip(args, argc); return true;
        case SYM_GEN_initBuildViewer_634: out = fn_initBuildViewer(args, argc); return true;
        case SYM_GEN_initBuildViewerIcon_635: out = fn_initBuildViewerIcon(args, argc); return true;
        case SYM_GEN_initInfoPanelIcon_636: out = fn_initInfoPanelIcon(args, argc); return true;
        case SYM_GEN_initGridStorageIcon_637: out = fn_initGridStorageIcon(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_persistDataInShop_640: out = fn_persistDataInShop(args, argc); return true;
        case SYM_GEN_getTranslatedName_641: out = fn_getTranslatedName(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_insertParameters_643: out = fn_insertParameters(args, argc); return true;
        case SYM_GEN_insertParameter_644: out = fn_insertParameter(args, argc); return true;
        case SYM_GEN_getModeDescription_645: out = fn_getModeDescription(args, argc); return true;
        case SYM_GEN_getFlavorText_646: out = fn_getFlavorText(args, argc); return true;
        case SYM_GEN_disablePicking_647: out = fn_disablePicking(args, argc); return true;
        case SYM_GEN_enablePicking_648: out = fn_enablePicking(args, argc); return true;
        case SYM_GEN_enableTooltip_649: out = fn_enableTooltip(args, argc); return true;
        case SYM_GEN_disableTooltip_650: out = fn_disableTooltip(args, argc); return true;
        case SYM_GEN_disableFocus_651: out = fn_disableFocus(args, argc); return true;
        case SYM_GEN_enableFocus_652: out = fn_enableFocus(args, argc); return true;
        case SYM_GEN_setEditMode_653: out = fn_setEditMode(args, argc); return true;
        case SYM_GEN_setShadowAlpha_654: out = fn_setShadowAlpha(args, argc); return true;
        case SYM_GEN_getTopLeftGlobal_655: out = fn_getTopLeftGlobal(args, argc); return true;
        case SYM_GEN_getBottomRightGlobal_656: out = fn_getBottomRightGlobal(args, argc); return true;
        case SYM_GEN_getBottomCenter_657: out = fn_getBottomCenter(args, argc); return true;
        case SYM_GEN_getInventory_658: out = fn_getInventory(args, argc); return true;
        case SYM_GEN_wasAddedToInventory_659: out = sf_wasAddedToInventory(gd_ctx, args, argc); return true;
        case SYM_GEN_wasBought_660: out = sf_wasBought(gd_ctx, args, argc); return true;
        case SYM_GEN_wasHotSwap_661: out = sf_wasHotSwap(gd_ctx, args, argc); return true;
        case SYM_GEN_removeFromInventory_662: out = fn_removeFromInventory(args, argc); return true;
        case SYM_GEN_playAffectedPlacedAnimation_663: out = fn_playAffectedPlacedAnimation(args, argc); return true;
        case SYM_GEN_clearCanAffectVisuals_664: out = fn_clearCanAffectVisuals(args, argc); return true;
        case SYM_GEN_liesInStorage_665: out = fn_liesInStorage(args, argc); return true;
        case SYM_GEN_pushToStorage_666: out = fn_pushToStorage(args, argc); return true;
        case SYM_GEN_addToStorageBox_667: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_removeFromStorage_668: out = fn_removeFromStorage(args, argc); return true;
        case SYM_GEN_onStorageLeft_669: out = fn_onStorageLeft(args, argc); return true;
        case SYM_GEN_isInGridStorage_670: out = fn_isInGridStorage(args, argc); return true;
        case SYM_GEN_getGridStorageProxy_671: out = fn_getGridStorageProxy(args, argc); return true;
        case SYM_GEN_onAddedToGridStorage_672: out = fn_onAddedToGridStorage(args, argc); return true;
        case SYM_GEN_onRemovedFromGridStorage_673: out = fn_onRemovedFromGridStorage(args, argc); return true;
        case SYM_GEN_makeGrabbable_674: out = fn_makeGrabbable(args, argc); return true;
        case SYM_GEN_moveToFreeSpaceInStorage_675: out = fn_moveToFreeSpaceInStorage(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds_676: out = fn_checkIfOutofStorageBounds(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds2_677: out = fn_checkIfOutofStorageBounds2(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds3_678: out = fn_checkIfOutofStorageBounds3(args, argc); return true;
        case SYM_GEN_findFreeSpace_679: out = fn_findFreeSpace(args, argc); return true;
        case SYM_GEN_unclip_680: out = fn_unclip(args, argc); return true;
        case SYM_GEN_onAddedToStorageBox_681: out = fn_onAddedToStorageBox(args, argc); return true;
        case SYM_GEN__process_682: out = fn__process(args, argc); return true;
        case SYM_GEN__integrate_forces_683: out = fn__integrate_forces(args, argc); return true;
        case SYM_GEN_updateShadow_684: out = fn_updateShadow(args, argc); return true;
        case SYM_GEN_lerpAngle_local_685: out = fn_lerpAngle_local(args, argc); return true;
        case SYM_GEN_updateInsideRotationNode_686: out = fn_updateInsideRotationNode(args, argc); return true;
        case SYM_GEN_spawnRotationSparks_687: out = fn_spawnRotationSparks(args, argc); return true;
        case SYM_GEN_highlight_688: out = fn_highlight(args, argc); return true;
        case SYM_GEN_unhighlight_689: out = fn_unhighlight(args, argc); return true;
        case SYM_GEN_setBright_690: out = fn_setBright(args, argc); return true;
        case SYM_GEN_resetBright_691: out = fn_resetBright(args, argc); return true;
        case SYM_GEN_getHoverPriority_692: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_canGainFocus_693: out = fn_canGainFocus(args, argc); return true;
        case SYM_GEN_gainFocus_694: out = fn_gainFocus(args, argc); return true;
        case SYM_GEN_respondToHover_695: out = fn_respondToHover(args, argc); return true;
        case SYM_GEN_canShowBuildIntoRecipesTooltip_696: out = fn_canShowBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_canShowSubBuildIntoRecipesTooltip_697: out = fn_canShowSubBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_showBuildIntoRecipesTooltip_698: out = fn_showBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN_getRecipeDescriptor_701: out = fn_getRecipeDescriptor(args, argc); return true;
        case SYM_GEN_hideBuildIntoRecipesTooltip_702: out = fn_hideBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_loseFocus_703: out = fn_loseFocus(args, argc); return true;
        case SYM_GEN_respondToHoverEnd_704: out = fn_respondToHoverEnd(args, argc); return true;
        case SYM_GEN_activateDragParticles_705: out = fn_activateDragParticles(args, argc); return true;
        case SYM_GEN_deactivateDragParticles_706: out = fn_deactivateDragParticles(args, argc); return true;
        case SYM_GEN_updateTooltip_707: out = fn_updateTooltip(args, argc); return true;
        case SYM_GEN_queueTooltipUpdate_708: out = fn_queueTooltipUpdate(args, argc); return true;
        case SYM_GEN_clearTooltip_709: out = fn_clearTooltip(args, argc); return true;
        case SYM_GEN_mouseEntered_710: out = fn_mouseEntered(args, argc); return true;
        case SYM_GEN_hover_711: out = fn_hover(args, argc); return true;
        case SYM_GEN_mouseExited_712: out = fn_mouseExited(args, argc); return true;
        case SYM_GEN_hoverEnd_713: out = fn_hoverEnd(args, argc); return true;
        case SYM_GEN_isHovered_714: out = fn_isHovered(args, argc); return true;
        case SYM_GEN_getScaleProp_715: out = fn_getScaleProp(args, argc); return true;
        case SYM_GEN_setSpriteScale_716: out = fn_setSpriteScale(args, argc); return true;
        case SYM_GEN_pickup_717: out = fn_pickup(args, argc); return true;
        case SYM_GEN_onDraggedWithParentStart_718: out = fn_onDraggedWithParentStart(args, argc); return true;
        case SYM_GEN_finishMoveback_719: out = fn_finishMoveback(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_720: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_canSnap_721: out = fn_canSnap(args, argc); return true;
        case SYM_GEN_reactToDropResult_722: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_drop_723: out = fn_drop(args, argc); return true;
        case SYM_GEN_showClickArea_724: out = fn_showClickArea(args, argc); return true;
        case SYM_GEN_cancelDrag_725: out = fn_cancelDrag(args, argc); return true;
        case SYM_GEN_emptyTweenCallback_726: out = fn_emptyTweenCallback(args, argc); return true;
        case SYM_GEN_killMovebackTween_727: out = fn_killMovebackTween(args, argc); return true;
        case SYM_GEN_setSpriteGlobalPos_728: out = fn_setSpriteGlobalPos(args, argc); return true;
        case SYM_GEN_dropIntoInventory_729: out = fn_dropIntoInventory(args, argc); return true;
        case SYM_GEN_finishInsideItemsRotation_730: out = fn_finishInsideItemsRotation(args, argc); return true;
        case SYM_GEN_pushDraggedItemsToStorage_731: out = fn_pushDraggedItemsToStorage(args, argc); return true;
        case SYM_GEN_reparentItemsInside_732: out = fn_reparentItemsInside(args, argc); return true;
        case SYM_GEN_clearDraggedInsideItems_733: out = fn_clearDraggedInsideItems(args, argc); return true;
        case SYM_GEN_showSockets_734: out = fn_showSockets(args, argc); return true;
        case SYM_GEN_hideSockets_735: out = fn_hideSockets(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_canBeSold_737: out = fn_canBeSold(args, argc); return true;
        case SYM_GEN_isPickingPossible_738: out = fn_isPickingPossible(args, argc); return true;
        case SYM_GEN_canBePicked_739: out = fn_canBePicked(args, argc); return true;
        case SYM_GEN_canBeDraggedWithBag_740: out = fn_canBeDraggedWithBag(args, argc); return true;
        case SYM_GEN_canBeDropped_741: out = fn_canBeDropped(args, argc); return true;
        case SYM_GEN__input_742: out = fn__input(args, argc); return true;
        case SYM_GEN_resetSprite_743: out = fn_resetSprite(args, argc); return true;
        case SYM_GEN_combatToShop_744: out = fn_combatToShop(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_startFusing_inShop_747: out = fn_startFusing_inShop(args, argc); return true;
        case SYM_GEN_getCraftingPriority_748: out = fn_getCraftingPriority(args, argc); return true;
        case SYM_GEN_addToCraftingQueue_749: out = fn_addToCraftingQueue(args, argc); return true;
        case SYM_GEN_combatToTitle_750: out = fn_combatToTitle(args, argc); return true;
        case SYM_GEN_readyToFuse_751: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_startFusing_752: out = fn_startFusing(args, argc); return true;
        case SYM_GEN_readyToTransform_753: out = fn_readyToTransform(args, argc); return true;
        case SYM_GEN_giveGold_754: out = fn_giveGold(args, argc); return true;
        case SYM_GEN_getTranslatedTypeName_755: out = fn_getTranslatedTypeName(args, argc); return true;
        case SYM_GEN_getTypeDescription_756: out = fn_getTypeDescription(args, argc); return true;
        case SYM_GEN_getTranslatedRarity_757: out = fn_getTranslatedRarity(args, argc); return true;
        case SYM_GEN_getRarityName_758: out = sf_getRarityName(gd_ctx, args, argc); return true;
        case SYM_GEN_logCooldown_759: out = fn_logCooldown(args, argc); return true;
        case SYM_GEN_getCombatDisplayAccuracy_760: out = fn_getCombatDisplayAccuracy(args, argc); return true;
        case SYM_GEN_getDisplayCritChance_761: out = fn_getDisplayCritChance(args, argc); return true;
        case SYM_GEN_getSalesMultiplier_762: out = fn_getSalesMultiplier(args, argc); return true;
        case SYM_GEN_prepareDiscard_763: out = fn_prepareDiscard(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN_popIn_765: out = fn_popIn(args, argc); return true;
        case SYM_GEN_disappear_766: out = fn_disappear(args, argc); return true;
        case SYM_GEN_appearInLibrary_767: out = fn_appearInLibrary(args, argc); return true;
        case SYM_GEN_createParticles_768: out = fn_createParticles(args, argc); return true;
        case SYM_GEN_deactivateParticles_769: out = fn_deactivateParticles(args, argc); return true;
        case SYM_GEN_makeRigidBody_770: out = fn_makeRigidBody(args, argc); return true;
        case SYM_GEN_dropImpulse_771: out = fn_dropImpulse(args, argc); return true;
        case SYM_GEN_makeNonRigidBody_772: out = fn_makeNonRigidBody(args, argc); return true;
        case SYM_GEN_rollShopChance_773: out = fn_rollShopChance(args, argc); return true;
        case SYM_GEN__physics_process_774: out = fn__physics_process(args, argc); return true;
        case SYM_GEN_playActivationAnimation_Scale_775: out = fn_playActivationAnimation_Scale(args, argc); return true;
        case SYM_GEN_playActivationAnimation_Jump_776: out = fn_playActivationAnimation_Jump(args, argc); return true;
        case SYM_GEN_playActivationAnimation_JumpSquash_777: out = fn_playActivationAnimation_JumpSquash(args, argc); return true;
        case SYM_GEN_playActivationAnimation_778: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_playActivationSound_150: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN_clearSpriteMaterial_779: out = fn_clearSpriteMaterial(args, argc); return true;
        case SYM_GEN_giveProgressMaterial_780: out = fn_giveProgressMaterial(args, argc); return true;
        case SYM_GEN_getTextureSize_781: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN_scaleToFit_782: out = fn_scaleToFit(args, argc); return true;
        case SYM_GEN_getSpriteOffset_783: out = fn_getSpriteOffset(args, argc); return true;
        case SYM_GEN_getGlobalCenter_784: out = fn_getGlobalCenter(args, argc); return true;
        case SYM_GEN_getTextureSize_local_785: out = fn_getTextureSize_local(args, argc); return true;
        case SYM_GEN_scaleToFit_local_786: out = fn_scaleToFit_local(args, argc); return true;
        case SYM_GEN_getSpriteOffset_local_787: out = fn_getSpriteOffset_local(args, argc); return true;
        case SYM_GEN_setTexture_788: out = fn_setTexture(args, argc); return true;
        case SYM_GEN_updateShadowTexture_789: out = fn_updateShadowTexture(args, argc); return true;
        case SYM_GEN_initSpriteMaterial_790: out = fn_initSpriteMaterial(args, argc); return true;
        case SYM_GEN_updateShaderRotation_791: out = fn_updateShaderRotation(args, argc); return true;
        case SYM_GEN_allowCancelShaderTween_792: out = fn_allowCancelShaderTween(args, argc); return true;
        case SYM_GEN_showCooldownSmooth_793: out = fn_showCooldownSmooth(args, argc); return true;
        case SYM_GEN_showCooldown_794: out = fn_showCooldown(args, argc); return true;
        case SYM_GEN_createAnimation_795: out = fn_createAnimation(args, argc); return true;
        case SYM_GEN_playAnimation_796: out = fn_playAnimation(args, argc); return true;
        case SYM_GEN_hasInventoryDuration_797: out = fn_hasInventoryDuration(args, argc); return true;
        case SYM_GEN_reveal_798: out = fn_reveal(args, argc); return true;
        case SYM_GEN_setRevealed_799: out = fn_setRevealed(args, argc); return true;
        case SYM_GEN_isCrafted_800: out = fn_isCrafted(args, argc); return true;
        case SYM_GEN_isMovingBack_801: out = fn_isMovingBack(args, argc); return true;
        case SYM_GEN__notification_802: out = fn__notification(args, argc); return true;
        case SYM_GEN_getAllInInventoryOfType_803: out = fn_getAllInInventoryOfType(args, argc); return true;
        case SYM_GEN_countAllInInventoryOfType_804: out = fn_countAllInInventoryOfType(args, argc); return true;
        case SYM_GEN_isTypeInInventory_805: out = fn_isTypeInInventory(args, argc); return true;
        case SYM_GEN_isRecipeFinished_806: out = fn_isRecipeFinished(args, argc); return true;
        case SYM_GEN_canStartNewRecipe_807: out = fn_canStartNewRecipe(args, argc); return true;
        case SYM_GEN_getRecipes_808: out = fn_getRecipes(args, argc); return true;
        case SYM_GEN_breakBondVisual_809: out = fn_breakBondVisual(args, argc); return true;
        case SYM_GEN_removeBondedBaseItem_810: out = fn_removeBondedBaseItem(args, argc); return true;
        case SYM_GEN_removeBondedIngredient_811: out = fn_removeBondedIngredient(args, argc); return true;
        case SYM_GEN_removeAllIngredients_812: out = fn_removeAllIngredients(args, argc); return true;
        case SYM_GEN_considerAsBond_813: out = fn_considerAsBond(args, argc); return true;
        case SYM_GEN_addBondedIngredient_814: out = fn_addBondedIngredient(args, argc); return true;
        case SYM_GEN_addToBaseItem_815: out = fn_addToBaseItem(args, argc); return true;
        case SYM_GEN_playBondAnimation_816: out = fn_playBondAnimation(args, argc); return true;
        case SYM_GEN_playBondFailedAnimation_817: out = fn_playBondFailedAnimation(args, argc); return true;
        case SYM_GEN_isCatalystBond_818: out = fn_isCatalystBond(args, argc); return true;
        case SYM_GEN_isLocked_819: out = fn_isLocked(args, argc); return true;
        case SYM_GEN_canLockBag_820: out = fn_canLockBag(args, argc); return true;
        case SYM_GEN_canBeLocked_821: out = fn_canBeLocked(args, argc); return true;
        case SYM_GEN_setLocked_822: out = fn_setLocked(args, argc); return true;
        case SYM_GEN_unlockCombining_823: out = fn_unlockCombining(args, argc); return true;
        case SYM_GEN_lockCombining_824: out = fn_lockCombining(args, argc); return true;
        case SYM_GEN_showLockLabel_825: out = fn_showLockLabel(args, argc); return true;
        case SYM_GEN_getLockPosition_826: out = fn_getLockPosition(args, argc); return true;
        case SYM_GEN_setBoundAsIngredient_827: out = fn_setBoundAsIngredient(args, argc); return true;
        case SYM_GEN_canPreviewFusions_828: out = fn_canPreviewFusions(args, argc); return true;
        case SYM_GEN_getCraftingPreviewPosition_829: out = fn_getCraftingPreviewPosition(args, argc); return true;
        case SYM_GEN_previewFusions_830: out = fn_previewFusions(args, argc); return true;
        case SYM_GEN_previewRecipeIngredients_831: out = fn_previewRecipeIngredients(args, argc); return true;
        case SYM_GEN_previewFusionToItem_832: out = fn_previewFusionToItem(args, argc); return true;
        case SYM_GEN_hasShopItemCraftCandidates_833: out = fn_hasShopItemCraftCandidates(args, argc); return true;
        case SYM_GEN_typeInIngredients_834: out = fn_typeInIngredients(args, argc); return true;
        case SYM_GEN_getTextEffect_835: out = fn_getTextEffect(args, argc); return true;
        case SYM_GEN_getFusionItemName_836: out = fn_getFusionItemName(args, argc); return true;
        case SYM_GEN_showProgressLabel_837: out = fn_showProgressLabel(args, argc); return true;
        case SYM_GEN_onCraftingLabelReturned_838: out = fn_onCraftingLabelReturned(args, argc); return true;
        case SYM_GEN_createBondVisual_839: out = fn_createBondVisual(args, argc); return true;
        case SYM_GEN_updateBondVisuals_840: out = fn_updateBondVisuals(args, argc); return true;
        case SYM_GEN_fuse_841: out = fn_fuse(args, argc); return true;
        case SYM_GEN_onFusingAsIngredient_842: out = fn_onFusingAsIngredient(args, argc); return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: out = fn_onFusingAsCatalystFinished(args, argc); return true;
        case SYM_GEN_createCraftedShockwave_844: out = fn_createCraftedShockwave(args, argc); return true;
        case SYM_GEN_finishFusing_845: out = fn_finishFusing(args, argc); return true;
        case SYM_GEN_allowGeneratingFusionItem_846: out = fn_allowGeneratingFusionItem(args, argc); return true;
        case SYM_GEN_catalystFusingFinished_847: out = fn_catalystFusingFinished(args, argc); return true;
        case SYM_GEN_onFusingFinished_848: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_onCraftedFrom_849: out = fn_onCraftedFrom(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN_playCraftedAnimation_851: out = fn_playCraftedAnimation(args, argc); return true;
        case SYM_GEN_onRestoreSnapshot_852: out = fn_onRestoreSnapshot(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Item::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getNumTooltipStats_624: out = sf_getNumTooltipStats(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumStackChangeTypes_625: out = sf_getNumStackChangeTypes(gd_ctx, args, argc); return true;
        case SYM_GEN_wasAddedToInventory_659: out = sf_wasAddedToInventory(gd_ctx, args, argc); return true;
        case SYM_GEN_wasBought_660: out = sf_wasBought(gd_ctx, args, argc); return true;
        case SYM_GEN_wasHotSwap_661: out = sf_wasHotSwap(gd_ctx, args, argc); return true;
        case SYM_GEN_getRarityName_758: out = sf_getRarityName(gd_ctx, args, argc); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Item::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__CoreItem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_hasPreDealDamageEarlyEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_early", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasPreDealDamageLateEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_late", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasDealtDamageEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDealtDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeReceivedEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeReceived", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeLeftEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeLeft", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_getNumTooltipStats(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_getNumStackChangeTypes(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0);
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Shop_2579))))) {
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_shop_524);
    }
    else {
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_525);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hoverEnd_713, nullptr, 0);
    if (gd::gd_truth(this->f_spotlight)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHover_695, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHoverEnd_704, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initBuildViewerIcon_635, nullptr, 0);
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
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedName_641, nullptr, 0), gd::SYM_replace, _ca, 2); })();
    }
    else {
        return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedName_641, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getDescription_642, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_requiredItem_2619), gd::GdVal::null())))) {
        gd::GdVal lv_requiredStr = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "itemName", 8u)), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_requiredItem_2619), SYM_GEN_getTranslatedName_641, nullptr, 0)); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TOOLTIP_Requires", 16u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })(), SYM_GEN_format_2621, _ca, 1); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$t", 2u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_begins_with, _ca, 1); })())) {
            lv_descr = gd::gd_add(gd_ctx, lv_requiredStr, lv_descr);
        }
        else {
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_requiredStr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), lv_descr}; return gd::gd_str_fn(gd_ctx.arena, _ca, 3); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_643, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_insertParameters(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_wrapInColor = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_154, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(lv_wrapInColor)) : gd::GdVal::from_bool(false)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$dam", 4u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_fixed_2623, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    {
        gd::GdVal _t418 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_extraCds_1584), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
        gd::GdArr* _t419 = (_t418.kind == gd::GdVal::Kind::Arr) ? _t418.arr : nullptr;
        uint32_t _len__t420 = _t419 ? _t419->len : 0u;
        for (uint32_t _t420 = 0; _t420 < _len__t420; ++_t420) {
            gd::GdVal lv_i = _t419->data[_t420];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })(), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldownIndex_107, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_280, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_106, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_280, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance2", 7u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance2Modified_283, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance", 6u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance1Modified_282, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "shopchance", 10u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getShopChance_239, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_114, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStaminaModified_115, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    {
        gd::GdVal _t421 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_params_1479), gd::SYM_size, nullptr, 0));
        gd::GdArr* _t422 = (_t421.kind == gd::GdVal::Kind::Arr) ? _t421.arr : nullptr;
        uint32_t _len__t423 = _t422 ? _t422->len : 0u;
        for (uint32_t _t423 = 0; _t423 < _len__t423; ++_t423) {
            gd::GdVal lv_i = _t422->data[_t423];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p", 1u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))))), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    {
        gd::GdVal _t424 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_sortedParamNames_1615));
        gd::GdArr* _t425 = (_t424.kind == gd::GdVal::Kind::Arr) ? _t424.arr : nullptr;
        uint32_t _len__t426 = _t425 ? _t425->len : 0u;
        for (uint32_t _t426 = 0; _t426 < _len__t426; ++_t426) {
            gd::GdVal lv_paramName = _t425->data[_t426];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_", 2u)), lv_paramName), ([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    if (gd::gd_truth(lv_wrapInColor)) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$block", 6u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0))), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_fixed_2623, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_insertParameter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_modified = (_argc > 3) ? _args[3] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548));
    gd::GdVal lv_checkZero = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_wrapInColor = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(true));
    lv_value = gd::gd_stepify(lv_value, gd::GdVal::from_float(0.01));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_value, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_checkZero))))))) {
        gd::GdVal lv_replacedString = gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$", 1u)), lv_paramName);
        gd::GdVal lv_startPos = ([&]() { gd::GdVal _ca[] = {lv_replacedString}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_find, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_startPos, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
            gd::GdVal lv_refEndPos = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, lv_startPos, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_findHighlightEnd_2624, _ca, 2); })();
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
                lv_replacement = ([&]() { gd::GdVal _ca[] = {lv_replacement, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_statColors_2625), lv_modified)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_fixed_2623, _ca, 2); })();
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
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getFlavorText_646, nullptr, 0);
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
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseFocus_703, nullptr, 0);
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
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToInventory_2626)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_Hotswap_2627))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_wasBought(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__Item::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2599))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_Socketed_2628))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_SocketHotswap_2629))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_wasHotSwap(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_Hotswap_2627)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_SocketHotswap_2629))))));
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
        gd::GdVal _t427 = gd::gd_iter_seq(gd_ctx.arena, lv_newItemIsAffected);
        gd::GdArr* _t428 = (_t427.kind == gd::GdVal::Kind::Arr) ? _t427.arr : nullptr;
        uint32_t _len__t429 = _t428 ? _t428->len : 0u;
        for (uint32_t _t429 = 0; _t429 < _len__t429; ++_t429) {
            gd::GdVal lv_color = _t428->data[_t429];
            lv_sum = gd::gd_add(gd_ctx, lv_sum, gd::gd_coerce_int(gd::get_index(gd_ctx, lv_newItemIsAffected, lv_color)));
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_sum, gd::GdVal::from_int(1LL))))) {
    }
    else if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)))) {
    }
    else if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)))) {
    }
    else if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Tertiary_2584)))) {
    }
    else if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Lightning_2613)))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearCanAffectVisuals(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_liesInStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerStorageBox_2580)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_dragged)))) : gd::GdVal::from_bool(false));
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killMovebackTween_727, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStorageLeft_669, nullptr, 0);
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkIfOutofStorageBounds2", 26u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_callNextFrame_1702, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_checkIfOutofStorageBounds2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkIfOutofStorageBounds3", 26u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_callNextFrame_1702, _ca, 2); })();
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_state, SYM_GEN_get_contact_count_2630, nullptr, 0), gd::GdVal::from_int(0LL))))) {
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateInsideRotationNode_686, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_684, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_743, nullptr, 0);
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
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_527);
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
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canGainFocus_693, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Socket_2590))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Opponent_2545)))))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_highlightItem_2631, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHover_695, nullptr, 0);
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
    gd::GdVal lv_effectiveOwner = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEffectiveOwnerType_259, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Tooltip_2617)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_owningBuildIntoRecipesTooltip, gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canShowSubBuildIntoRecipesTooltip_697, nullptr, 0))))) {
            return gd::GdVal::from_bool(false);
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Shop_2579)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_ItemLibrary_2615))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(lv_effectiveOwner, this->f_ownerTypesWithBuildTooltip)))))))) {
        return gd::GdVal::from_bool(false);
    }
    gd::GdVal lv_descr = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRecipeDescriptor_701, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_descr, SYM_GEN_getNumRecipes_2632, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRelatedItems_461, nullptr, 0), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(0LL))))) {
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHoverEnd_704, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_respondToHoverEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_activateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t430 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t431 = (_t430.kind == gd::GdVal::Kind::Arr) ? _t430.arr : nullptr;
        uint32_t _len__t432 = _t431 ? _t431->len : 0u;
        for (uint32_t _t432 = 0; _t432 < _len__t432; ++_t432) {
            gd::GdVal lv_specificParticles = _t431->data[_t432];
            (void)gd::call_method(gd_ctx, lv_specificParticles, SYM_GEN_activate_152, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_deactivateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t433 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t434 = (_t433.kind == gd::GdVal::Kind::Arr) ? _t433.arr : nullptr;
        uint32_t _len__t435 = _t434 ? _t434->len : 0u;
        for (uint32_t _t435 = 0; _t435 < _len__t435; ++_t435) {
            gd::GdVal lv_specificParticles = _t434->data[_t435];
            (void)gd::call_method(gd_ctx, lv_specificParticles, SYM_GEN_deactivate_2633, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hideBuildIntoRecipesTooltip_702, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearCanAffectVisuals_664, nullptr, 0);
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
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_866), SYM_GEN_Grabbed_2634));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onDraggedWithParentStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_parentItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_719, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showClickArea_724, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setSpriteGlobalPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_684, nullptr, 0);
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
        gd::GdVal _t436 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t437 = (_t436.kind == gd::GdVal::Kind::Arr) ? _t436.arr : nullptr;
        uint32_t _len__t438 = _t437 ? _t437->len : 0u;
        for (uint32_t _t438 = 0; _t438 < _len__t438; ++_t438) {
            gd::GdVal lv_item = _t437->data[_t438];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_pushToStorage_666, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_481, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_733, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_reparentItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t439 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t440 = (_t439.kind == gd::GdVal::Kind::Arr) ? _t439.arr : nullptr;
        uint32_t _len__t441 = _t440 ? _t440->len : 0u;
        for (uint32_t _t441 = 0; _t441 < _len__t441; ++_t441) {
            gd::GdVal lv_item = _t440->data[_t441];
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_481, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_733, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearDraggedInsideItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t442 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t443 = (_t442.kind == gd::GdVal::Kind::Arr) ? _t442.arr : nullptr;
        uint32_t _len__t444 = _t443 ? _t443->len : 0u;
        for (uint32_t _t444 = 0; _t444 < _len__t444; ++_t444) {
            gd::GdVal lv_item = _t443->data[_t444];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_onDraggedWithParentEnd_720, nullptr, 0);
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
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerStorageBox_2580))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Socket_2590))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isPickingPossible(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBePicked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(this->f_focus) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isPickingPossible_738, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1384), this->f_dropFrame)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeDraggedWithBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_dragged) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1384), this->f_pickupFrame)))) : gd::GdVal::from_bool(false));
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
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_253, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_650, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_743, nullptr, 0);
        (void)gd::call_method(gd_ctx, this->f_cachedAffectedItems, gd::SYM_clear, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1583));
    this->f_speedScale = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMinDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    {
        gd::GdVal _t445 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffPowers);
        gd::GdArr* _t446 = (_t445.kind == gd::GdVal::Kind::Arr) ? _t445.arr : nullptr;
        uint32_t _len__t447 = _t446 ? _t446->len : 0u;
        for (uint32_t _t447 = 0; _t447 < _len__t447; ++_t447) {
            gd::GdVal lv_buff = _t446->data[_t447];
            { gd::GdVal _t448 = this->f_buffPowers; gd::GdVal _t449 = lv_buff; gd::set_index(gd_ctx, _t448, _t449, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t450 = this->f_buffAmplificationChances; gd::GdVal _t451 = lv_buff; gd::set_index(gd_ctx, _t450, _t451, gd::GdVal::from_float(0.0)); }
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_enablePicking_648, nullptr, 0);
    {
        gd::GdVal _t452 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t453 = (_t452.kind == gd::GdVal::Kind::Arr) ? _t452.arr : nullptr;
        uint32_t _len__t454 = _t453 ? _t453->len : 0u;
        for (uint32_t _t454 = 0; _t454 < _len__t454; ++_t454) {
            gd::GdVal lv_gem = _t453->data[_t454];
            (void)([&]() { gd::GdVal _ca[] = {lv_craft}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN_shopEntered_745, _ca, 1); })();
        }
    }
    if (gd::gd_truth(lv_craft)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addToCraftingQueue_749, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onShopEntered_746, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_startFusing_inShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_COG_604)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFusing_752, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCraftingPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isGem_86, nullptr, 0))) {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_Gem_2635);
    }
    {
        gd::GdVal _t455 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
        gd::GdArr* _t456 = (_t455.kind == gd::GdVal::Kind::Arr) ? _t455.arr : nullptr;
        uint32_t _len__t457 = _t456 ? _t456->len : 0u;
        for (uint32_t _t457 = 0; _t457 < _len__t457; ++_t457) {
            gd::GdVal lv_bonded = _t456->data[_t457];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_bonded, SYM_GEN_isGem_86, nullptr, 0))) {
                return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_Mixed_2636);
            }
        }
    }
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_NonGem_2637);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addToCraftingQueue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_combatToTitle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_253, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_650, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_curRecipe) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2638, _ca, 1); })(), gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_startFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delay = (_argc > 0) ? _args[0] : (Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_603));
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_readyToFuse_751, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fuse", 4u)), lv_delay}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_callDelayed_1420, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disablePicking_647, nullptr, 0);
        {
            gd::GdVal _t458 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
            gd::GdArr* _t459 = (_t458.kind == gd::GdVal::Kind::Arr) ? _t458.arr : nullptr;
            uint32_t _len__t460 = _t459 ? _t459->len : 0u;
            for (uint32_t _t460 = 0; _t460 < _len__t460; ++_t460) {
                gd::GdVal lv_bonded = _t459->data[_t460];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_curRecipe, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_bonded}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2639, _ca, 1); })()))))))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bonded, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "disablePicking", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
                    gd::set_prop(gd_ctx, lv_bonded, SYM_GEN_willBeConsumed_608, gd::GdVal::from_bool(true));
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
    return ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedTypeName_755, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTypeDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TYPE_", 5u)), gd::get_index(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), gd::SYM_keys, nullptr, 0), lv_type)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_DESCR", 6u)))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTranslatedRarity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_238, nullptr, 0)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__Item::call_static_fn(gd_ctx, SYM_GEN_getRarityName_758, _ca, 1, _out); return _out; })();
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
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCombatDisplayAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_acc = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAccuracy_196, nullptr, 0);
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
    gd::GdVal lv_c = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCritChancePercent_180, nullptr, 0);
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
    gd::GdVal lv_shopChance = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_shopChance_1587));
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__physics_process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_isStunned_1155, nullptr, 0))))) {
        this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_triggerTime, gd::gd_mul(lv_delta, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_94, nullptr, 0))));
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_triggerTime, this->f_iterationCooldown))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldown_794, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_triggerTime, gd::GdVal::from_int(0LL))))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_145, nullptr, 0);
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
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN)))))))) {
        lv_scaling = gd::GdVal::from_vec2((lv_shortScale).as_float(), (lv_longScale).as_float());
    }
    else {
        lv_scaling = gd::GdVal::from_vec2((lv_longScale).as_float(), (lv_shortScale).as_float());
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1621));
    gd::GdVal lv_consume = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_consume = gd::gd_coerce_bool(lv_consume);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_743, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Jump_2608))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_SquishyJump_2640))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.1)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_777, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_VerySquishyJump_2641))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.2)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_777, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Slash_2642))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Stab_2643))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_ReverseStab_2644))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Bonk_2645))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_ReverseBonk_2646))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Sweep_2647))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Block_2564))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL), gd::GdVal::from_float(1.3)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Chop_2648))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Wave_2649))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Throw_2609))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Scale_2650))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Scale_775, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Squish_2651))))) {
        if (gd::gd_truth(this->f_hasSquishySprite)) {
        }
        else {
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Potion_2652))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Hiss_2653))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Spin_2654))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Tackle_2655))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_DoubleSlash_2656))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Struggle_2657))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Shoot_2658))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Flash_2659))))) {
    }
    if (gd::gd_truth(lv_consume)) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(6LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playDropSound_151, _ca, 1); })();
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initSpriteMaterial_790, nullptr, 0);
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
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1599))))) {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hasInventoryDuration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1487, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_reveal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setRevealed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reveal_798, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isCrafted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isCraftedItem_1624, nullptr, 0);
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
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_253, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getItemsInInventoryOfType_opponent_1571, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getItemsInInventoryOfType_1570, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_countAllInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_253, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_countItemsInInventoryOfType_opponent_1573, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_countItemsInInventoryOfType_1572, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isTypeInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_253, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_isItemInInventory_opponent_1576, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_isItemInInventory_1575, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isRecipeFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2638, _ca, 1); })(), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canStartNewRecipe(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBaseItem_260, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isAvailableForCrafting_495, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRecipes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_checkClassAvailability = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_recipes = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t461 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_recipes_2660));
        gd::GdArr* _t462 = (_t461.kind == gd::GdVal::Kind::Arr) ? _t461.arr : nullptr;
        uint32_t _len__t463 = _t462 ? _t462->len : 0u;
        for (uint32_t _t463 = 0; _t463 < _len__t463; ++_t463) {
            gd::GdVal lv_recipe = _t462->data[_t463];
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeBondedIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_breakBondVisual_809, _ca, 1); })();
    if (gd::gd_truth(this->f_fusing)) {
        return gd::GdVal::null();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_837, nullptr, 0);
    if (gd::gd_truth(gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_empty, nullptr, 0))) {
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_840, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeAllIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_837, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_considerAsBond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_neighbor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_score = gd::GdVal::from_float(0.0);
    gd::GdVal lv_recipe = gd::GdVal::null();
    if (gd::gd_truth(this->f_curRecipe)) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isRecipeFinished_806, nullptr, 0))) {
            return gd::GdVal::null();
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients, lv_neighbor}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_checkNeighbor_2661, _ca, 2); })())) {
            gd::GdVal lv_progressBefore = ([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2638, _ca, 1); })();
            gd::GdVal lv_progressWithNeighbor = gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)), gd::gd_coerce_float(gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getNumIngredients_2662, nullptr, 0)));
            lv_score = gd::gd_add(gd_ctx, lv_progressWithNeighbor, gd::gd_mul(gd::GdVal::from_float(0.1), lv_progressBefore));
            lv_recipe = this->f_curRecipe;
        }
    }
    else {
        gd::GdVal lv_bestScore = gd::GdVal::from_float(0.0);
        {
            gd::GdVal _t464 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRecipes_808, nullptr, 0));
            gd::GdArr* _t465 = (_t464.kind == gd::GdVal::Kind::Arr) ? _t464.arr : nullptr;
            uint32_t _len__t466 = _t465 ? _t465->len : 0u;
            for (uint32_t _t466 = 0; _t466 < _len__t466; ++_t466) {
                gd::GdVal lv_r = _t465->data[_t466];
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
    (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createBondVisual_839, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_840, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_816, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, lv_neighbor, SYM_GEN_placedByPlayer_52)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_placedByPlayer))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_837, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addToBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_816, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playBondAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_catalyst = gd::GdVal::from_bool(false);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_bondedBaseItem, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_bondedBaseItem, SYM_GEN_curRecipe_577), gd::GdVal::null())))) {
            lv_catalyst = gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_bondedBaseItem, SYM_GEN_curRecipe_577), SYM_GEN_isCatalystRecipe_2663, nullptr, 0);
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
    return ([&]() { gd::GdVal _ca[] = {lv_bondedItem}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2639, _ca, 1); })();
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
        (void)([&]() { gd::GdVal _ca[] = {lv_showLabel}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_lockCombining_824, _ca, 1); })();
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_unlockCombining_823, nullptr, 0);
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
        gd::GdVal _t467 = gd::gd_iter_seq(gd_ctx.arena, lv_ingredients);
        gd::GdArr* _t468 = (_t467.kind == gd::GdVal::Kind::Arr) ? _t467.arr : nullptr;
        uint32_t _len__t469 = _t468 ? _t468->len : 0u;
        for (uint32_t _t469 = 0; _t469 < _len__t469; ++_t469) {
            gd::GdVal lv_ingredient = _t468->data[_t469];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_ingredient}; return gd::call_method(gd_ctx, lv_candidate, SYM_GEN_hasType_81, _ca, 1); })())) {
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTextEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_textEffect_2276);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getFusionItemName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_fusedItem_2664), SYM_GEN_getTranslatedName_641, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearSpriteMaterial_779, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_719, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Normal_2541);
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
        case SYM_GEN_attack_941: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Weapon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_attack_941: out = fn_attack(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Weapon::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attack_941, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Weapon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
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
        case SYM_GEN_amount_1041: out = this->f_amount; return true;
        case SYM_GEN_timeout_1042: out = this->f_timeout; return true;
        case SYM_GEN_item_1043: out = this->f_item; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_amount_1041: this->f_amount = gd::gd_coerce_int(val); return true;
        case SYM_GEN_timeout_1042: this->f_timeout = gd::gd_coerce_float(val); return true;
        case SYM_GEN_item_1043: this->f_item = val; return true;
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
    this->f_releaseState = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_ReleaseState_1631), SYM_GEN_Full_2665));
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
        case SYM_GEN_ReleaseState_1631: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreItemData_ReleaseState);
        case SYM_GEN_PARAM_DELIMITER_1614: return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_", 1u));
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
        case SYM_GEN_identifier_1577: out = this->f_identifier; return true;
        case SYM_GEN_itemIndex_1578: out = this->f_itemIndex; return true;
        case SYM_GEN_minDam_1579: out = this->f_minDam; return true;
        case SYM_GEN_maxDam_1580: out = this->f_maxDam; return true;
        case SYM_GEN_staminaCost_1581: out = this->f_staminaCost; return true;
        case SYM_GEN_block_1582: out = this->f_block; return true;
        case SYM_GEN_cd_1583: out = this->f_cd; return true;
        case SYM_GEN_extraCds_1584: out = this->f_extraCds; return true;
        case SYM_GEN_accuracy_1454: out = this->f_accuracy; return true;
        case SYM_GEN_canActivate_93: out = this->f_canActivate; return true;
        case SYM_GEN_chance_1585: out = this->f_chance; return true;
        case SYM_GEN_chance2_1586: out = this->f_chance2; return true;
        case SYM_GEN_shopChance_1587: out = this->f_shopChance; return true;
        case SYM_GEN_types_1453: out = this->f_types; return true;
        case SYM_GEN_tags_1588: out = this->f_tags; return true;
        case SYM_GEN_physics_1589: out = this->f_physics; return true;
        case SYM_GEN_rarity_1590: out = this->f_rarity; return true;
        case SYM_GEN_price_1591: out = this->f_price; return true;
        case SYM_GEN_classes_1592: out = this->f_classes; return true;
        case SYM_GEN_randomUniquePool_1593: out = this->f_randomUniquePool; return true;
        case SYM_GEN_hasBattleRageEffect_1594: out = this->f_hasBattleRageEffect; return true;
        case SYM_GEN_gatedItems_1595: out = this->f_gatedItems; return true;
        case SYM_GEN_startsSubclass_1596: out = this->f_startsSubclass; return true;
        case SYM_GEN_gateItem_1597: out = this->f_gateItem; return true;
        case SYM_GEN_originatingRecipes_1598: out = this->f_originatingRecipes; return true;
        case SYM_GEN_animationScene_1599: out = this->f_animationScene; return true;
        case SYM_GEN_flickerAni_1600: out = this->f_flickerAni; return true;
        case SYM_GEN_flickerMinDist_1601: out = this->f_flickerMinDist; return true;
        case SYM_GEN_flickerMaxDist_1602: out = this->f_flickerMaxDist; return true;
        case SYM_GEN_flickerMinSpeed_1603: out = this->f_flickerMinSpeed; return true;
        case SYM_GEN_flickerMaxSpeed_1604: out = this->f_flickerMaxSpeed; return true;
        case SYM_GEN_connectorReadyRoll_1605: out = this->f_connectorReadyRoll; return true;
        case SYM_GEN_gemRoll_1606: out = this->f_gemRoll; return true;
        case SYM_GEN_sceneDepth_1607: out = this->f_sceneDepth; return true;
        case SYM_GEN_releaseState_1608: out = this->f_releaseState; return true;
        case SYM_GEN__editor_1609: out = this->f__editor; return true;
        case SYM_GEN__playtest_1610: out = this->f__playtest; return true;
        case SYM_GEN__full_version_1611: out = this->f__full_version; return true;
        case SYM_GEN__engineer_test_1612: out = this->f__engineer_test; return true;
        case SYM_GEN_params_1479: out = this->f_params; return true;
        case SYM_GEN_namedParams_1613: out = this->f_namedParams; return true;
        case SYM_GEN_sortedParamNames_1615: out = this->f_sortedParamNames; return true;
        case SYM_GEN_paramBases_1616: out = this->f_paramBases; return true;
        case SYM_GEN_paramBases_inverted_1617: out = this->f_paramBases_inverted; return true;
        case SYM_GEN_gainedStacks_1618: out = this->f_gainedStacks; return true;
        case SYM_GEN_removedStacks_1619: out = this->f_removedStacks; return true;
        case SYM_GEN_usedStacks_1620: out = this->f_usedStacks; return true;
        case SYM_GEN_activationAni_1621: out = this->f_activationAni; return true;
        case SYM_GEN_ReleaseState_1631: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreItemData_ReleaseState); return true;
        case SYM_GEN_PARAM_DELIMITER_1614: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_name_7: this->f_name = val; return true;
        case SYM_GEN_identifier_1577: this->f_identifier = val; return true;
        case SYM_GEN_itemIndex_1578: this->f_itemIndex = gd::gd_coerce_int(val); return true;
        case SYM_GEN_minDam_1579: this->f_minDam = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxDam_1580: this->f_maxDam = gd::gd_coerce_int(val); return true;
        case SYM_GEN_staminaCost_1581: this->f_staminaCost = gd::gd_coerce_float(val); return true;
        case SYM_GEN_block_1582: this->f_block = gd::gd_coerce_int(val); return true;
        case SYM_GEN_cd_1583: this->f_cd = gd::gd_coerce_float(val); return true;
        case SYM_GEN_extraCds_1584: this->f_extraCds = val; return true;
        case SYM_GEN_accuracy_1454: this->f_accuracy = gd::gd_coerce_float(val); return true;
        case SYM_GEN_canActivate_93: this->f_canActivate = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_chance_1585: this->f_chance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_chance2_1586: this->f_chance2 = gd::gd_coerce_float(val); return true;
        case SYM_GEN_shopChance_1587: this->f_shopChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_types_1453: this->f_types = val; return true;
        case SYM_GEN_tags_1588: this->f_tags = gd::gd_coerce_int(val); return true;
        case SYM_GEN_physics_1589: this->f_physics = gd::gd_coerce_int(val); return true;
        case SYM_GEN_rarity_1590: this->f_rarity = gd::gd_coerce_int(val); return true;
        case SYM_GEN_price_1591: this->f_price = gd::gd_coerce_int(val); return true;
        case SYM_GEN_classes_1592: this->f_classes = gd::gd_coerce_int(val); return true;
        case SYM_GEN_randomUniquePool_1593: this->f_randomUniquePool = val; return true;
        case SYM_GEN_hasBattleRageEffect_1594: this->f_hasBattleRageEffect = val; return true;
        case SYM_GEN_gatedItems_1595: this->f_gatedItems = val; return true;
        case SYM_GEN_startsSubclass_1596: this->f_startsSubclass = val; return true;
        case SYM_GEN_gateItem_1597: this->f_gateItem = val; return true;
        case SYM_GEN_originatingRecipes_1598: this->f_originatingRecipes = val; return true;
        case SYM_GEN_animationScene_1599: this->f_animationScene = val; return true;
        case SYM_GEN_flickerAni_1600: this->f_flickerAni = val; return true;
        case SYM_GEN_flickerMinDist_1601: this->f_flickerMinDist = val; return true;
        case SYM_GEN_flickerMaxDist_1602: this->f_flickerMaxDist = val; return true;
        case SYM_GEN_flickerMinSpeed_1603: this->f_flickerMinSpeed = val; return true;
        case SYM_GEN_flickerMaxSpeed_1604: this->f_flickerMaxSpeed = val; return true;
        case SYM_GEN_connectorReadyRoll_1605: this->f_connectorReadyRoll = val; return true;
        case SYM_GEN_gemRoll_1606: this->f_gemRoll = val; return true;
        case SYM_GEN_sceneDepth_1607: this->f_sceneDepth = val; return true;
        case SYM_GEN_releaseState_1608: this->f_releaseState = gd::gd_coerce_int(val); return true;
        case SYM_GEN__editor_1609: this->f__editor = val; return true;
        case SYM_GEN__playtest_1610: this->f__playtest = val; return true;
        case SYM_GEN__full_version_1611: this->f__full_version = val; return true;
        case SYM_GEN__engineer_test_1612: this->f__engineer_test = val; return true;
        case SYM_GEN_params_1479: this->f_params = val; return true;
        case SYM_GEN_namedParams_1613: this->f_namedParams = val; return true;
        case SYM_GEN_sortedParamNames_1615: this->f_sortedParamNames = val; return true;
        case SYM_GEN_paramBases_1616: this->f_paramBases = val; return true;
        case SYM_GEN_paramBases_inverted_1617: this->f_paramBases_inverted = val; return true;
        case SYM_GEN_gainedStacks_1618: this->f_gainedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_removedStacks_1619: this->f_removedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedStacks_1620: this->f_usedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationAni_1621: this->f_activationAni = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getP_190: return true;
        case SYM_GEN_hasParam_1487: return true;
        case SYM_GEN_addNamedParam_1622: return true;
        case SYM_GEN_hasTag_83: return true;
        case SYM_GEN_isWeapon_84: return true;
        case SYM_GEN_getIndex_237: return true;
        case SYM_GEN_getName_236: return true;
        case SYM_GEN_getRarity_238: return true;
        case SYM_GEN_getShopChance_239: return true;
        case SYM_GEN_getTypes_242: return true;
        case SYM_GEN_isAvailableFor_1623: return true;
        case SYM_GEN_isNeutral_248: return true;
        case SYM_GEN_isClassItem_250: return true;
        case SYM_GEN_isSubclassItem_251: return true;
        case SYM_GEN_isCraftedItem_1624: return true;
        case SYM_GEN_isGatedItem_1625: return true;
        case SYM_GEN_isMeleeWeapon_1626: return true;
        case SYM_GEN_isRangedWeapon_1627: return true;
        case SYM_GEN_isStartingWeapon_1628: return true;
        case SYM_GEN_isReleased_1629: return true;
        case SYM_GEN_getPrice_394: return true;
        case SYM_GEN_getSellPrice_396: return true;
        case SYM_GEN_getSalePrice_397: return true;
        case SYM_GEN_getTranslatedName_641: return true;
        case SYM_GEN_fromDict_1630: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemData::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getP_190: out = fn_getP(args, argc); return true;
        case SYM_GEN_hasParam_1487: out = fn_hasParam(args, argc); return true;
        case SYM_GEN_addNamedParam_1622: out = fn_addNamedParam(args, argc); return true;
        case SYM_GEN_hasTag_83: out = fn_hasTag(args, argc); return true;
        case SYM_GEN_isWeapon_84: out = fn_isWeapon(args, argc); return true;
        case SYM_GEN_getIndex_237: out = fn_getIndex(args, argc); return true;
        case SYM_GEN_getName_236: out = fn_getName(args, argc); return true;
        case SYM_GEN_getRarity_238: out = fn_getRarity(args, argc); return true;
        case SYM_GEN_getShopChance_239: out = fn_getShopChance(args, argc); return true;
        case SYM_GEN_getTypes_242: out = fn_getTypes(args, argc); return true;
        case SYM_GEN_isAvailableFor_1623: out = fn_isAvailableFor(args, argc); return true;
        case SYM_GEN_isNeutral_248: out = fn_isNeutral(args, argc); return true;
        case SYM_GEN_isClassItem_250: out = fn_isClassItem(args, argc); return true;
        case SYM_GEN_isSubclassItem_251: out = fn_isSubclassItem(args, argc); return true;
        case SYM_GEN_isCraftedItem_1624: out = fn_isCraftedItem(args, argc); return true;
        case SYM_GEN_isGatedItem_1625: out = fn_isGatedItem(args, argc); return true;
        case SYM_GEN_isMeleeWeapon_1626: out = fn_isMeleeWeapon(args, argc); return true;
        case SYM_GEN_isRangedWeapon_1627: out = fn_isRangedWeapon(args, argc); return true;
        case SYM_GEN_isStartingWeapon_1628: out = fn_isStartingWeapon(args, argc); return true;
        case SYM_GEN_isReleased_1629: out = fn_isReleased(args, argc); return true;
        case SYM_GEN_getPrice_394: out = fn_getPrice(args, argc); return true;
        case SYM_GEN_getSellPrice_396: out = fn_getSellPrice(args, argc); return true;
        case SYM_GEN_getSalePrice_397: out = fn_getSalePrice(args, argc); return true;
        case SYM_GEN_getTranslatedName_641: out = fn_getTranslatedName(args, argc); return true;
        case SYM_GEN_fromDict_1630: out = fn_fromDict(args, argc); return true;
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
    { gd::GdVal _t470 = this->f_namedParams; gd::GdVal _t471 = lv_paramName; gd::set_index(gd_ctx, _t470, _t471, lv_paramVal); }
    gd::GdVal lv_sortedPos = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t472 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_sortedParamNames, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t473 = (_t472.kind == gd::GdVal::Kind::Arr) ? _t472.arr : nullptr;
        uint32_t _len__t474 = _t473 ? _t473->len : 0u;
        for (uint32_t _t474 = 0; _t474 < _len__t474; ++_t474) {
            gd::GdVal lv_i = _t473->data[_t474];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_sortedParamNames, lv_i), gd::SYM_begins_with, _ca, 1); })())) {
                lv_sortedPos = gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_sortedPos, lv_paramName}; return gd::call_method(gd_ctx, this->f_sortedParamNames, gd::SYM_insert, _ca, 2); })();
    { gd::GdVal _t475 = this->f_paramBases; gd::GdVal _t476 = lv_paramName; gd::set_index(gd_ctx, _t475, _t476, ([&]() { gd::GdVal _ca[] = {Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_PARAM_DELIMITER_1614), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_paramName, gd::SYM_get_slice, _ca, 2); })()); }
    { gd::GdVal _t477 = this->f_paramBases_inverted; gd::GdVal _t478 = gd::get_index(gd_ctx, this->f_paramBases, lv_paramName); gd::set_index(gd_ctx, _t477, _t478, lv_paramName); }
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
    return gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Weapon_2666), this->f_types);
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
    return gd::GdVal::from_bool(gd::gd_eq(this->f_classes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StuffedClasses_1370), SYM_GEN_Neutral_2667)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isClassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_classes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StuffedClasses_1370), SYM_GEN_Neutral_2667)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_classes, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StuffedClasses_1370), SYM_GEN_None_2668))))) : gd::GdVal::from_bool(false));
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
    return (gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Melee_2669), this->f_types)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_84, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isRangedWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Ranged_2670), this->f_types)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_84, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isStartingWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_84, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_identifier, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stone", 5u)))))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_isReleased(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_releaseState, gd::get_prop(gd_ctx, Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_ReleaseState_1631), SYM_GEN_Demo_2671))))) {
        return gd::GdVal::from_bool(true);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_releaseState, gd::get_prop(gd_ctx, Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_ReleaseState_1631), SYM_GEN_Full_2665))))) {
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
    return gd::gd_ceil(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getPrice_394, nullptr, 0), gd::GdVal::from_float(0.5)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemData::fn_getSalePrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_ceil(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getPrice_394, nullptr, 0), gd::GdVal::from_float(0.5)));
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
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_identifier_1577, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "identifier", 10u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "name", 4u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_itemIndex_1578, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "index", 5u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_minDam_1579, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "minDam", 6u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_maxDam_1580, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxDam", 6u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_staminaCost_1581, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminaCost", 11u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_block_1582, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_cd_1583, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_extraCds_1584, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "extraCds", 8u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_accuracy_1454, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "accuracy", 8u)), gd::GdVal::from_float(100.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_canActivate_93, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canActivate", 11u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1360, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_chance_1585, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance", 6u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_chance2_1586, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance2", 7u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_shopChance_1587, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "shopChance", 10u)), gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_types_1453, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "types", 5u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_tags_1588, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "tags", 4u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_physics_1589, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "physics", 7u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_rarity_1590, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "rarity", 6u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_price_1591, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "price", 5u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_classes_1592, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "classes", 7u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_randomUniquePool_1593, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randomUniquePool", 16u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1360, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_hasBattleRageEffect_1594, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hasBattleRageEffect", 19u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1360, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gatedItems_1595, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gatedItems", 10u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_startsSubclass_1596, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "startsSubclass", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gateItem_1597, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gateItem", 8u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gate_item", 9u)), gd::GdVal::null()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_originatingRecipes_1598, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "originatingRecipes", 18u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "originating_recipes", 19u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_animationScene_1599, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "animationScene", 14u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1360, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerAni_1600, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerAni", 10u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_animation", 17u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1360, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMinDist_1601, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerMinDist", 14u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_min_dist", 16u)), gd::GdVal::from_float(0.1)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMaxDist_1602, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerMaxDist", 14u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_max_dist", 16u)), gd::GdVal::from_float(3.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMinSpeed_1603, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerMinSpeed", 15u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_min_speed", 17u)), gd::GdVal::from_float(0.3)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_flickerMaxSpeed_1604, gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerMaxSpeed", 15u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flicker_max_speed", 17u)), gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_connectorReadyRoll_1605, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "connectorReadyRoll", 18u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "connector_ready_roll", 20u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1360, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gemRoll_1606, ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gemRoll", 7u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gem_roll", 8u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1360, _ca, 1); })());
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_sceneDepth_1607, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sceneDepth", 10u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "scene_depth", 11u)), gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_releaseState_1608, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "releaseState", 12u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "release_state", 13u)), gd::get_prop(gd_ctx, Gd__gd_core__CoreItemData::get_static_const_or_enum(gd_ctx, SYM_GEN_ReleaseState_1631), SYM_GEN_Full_2665)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_params_1479, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "params", 6u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })());
    gd::GdVal lv_np = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "namedParams", 11u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "named_params", 12u)), gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })();
    {
        gd::GdVal _t479 = gd::gd_iter_seq(gd_ctx.arena, lv_np);
        gd::GdArr* _t480 = (_t479.kind == gd::GdVal::Kind::Arr) ? _t479.arr : nullptr;
        uint32_t _len__t481 = _t480 ? _t480->len : 0u;
        for (uint32_t _t481 = 0; _t481 < _len__t481; ++_t481) {
            gd::GdVal lv_k = _t480->data[_t481];
            (void)([&]() { gd::GdVal _ca[] = {lv_k, gd::get_index(gd_ctx, lv_np, lv_k)}; return gd::call_method(gd_ctx, lv_o, SYM_GEN_addNamedParam_1622, _ca, 2); })();
        }
    }
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_gainedStacks_1618, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gainedStacks", 12u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_removedStacks_1619, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "removedStacks", 13u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
    gd::set_prop(gd_ctx, lv_o, SYM_GEN_usedStacks_1620, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "usedStacks", 10u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_d, gd::SYM_get, _ca, 2); })()));
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
        case SYM_GEN_damPerDebuff_1732: out = this->f_damPerDebuff; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Darksaber::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damPerDebuff_1732: this->f_damPerDebuff = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Darksaber::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDebuffsChanged_1733: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Darksaber::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDebuffsChanged_1733: out = fn_onDebuffsChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Darksaber::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Darksaber::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDebuffsChanged", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_378, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn_onDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerDebuff)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_335, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Darksaber::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damPerDebuff = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__FlyAgaric::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__FlyAgaric::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__FlyAgaric::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__FlyAgaric::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_vampirismForRegen_1808: out = this->f_vampirismForRegen; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__HungryBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_vampirismForRegen_1808: this->f_vampirismForRegen = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HungryBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HungryBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HungryBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_vampirism_changed", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onVampirismChanged", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core__HungryBlade::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Jump_2608)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMaxDamage_166, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        gd::GdVal lv_numRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_numRegen, this->f_regenNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_vampirismForRegen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HungryBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_vampirism = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    this->f_regenNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    this->f_vampirismForRegen = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
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
        case SYM_GEN_manaGained_1836: out = this->f_manaGained; return true;
        case SYM_GEN_fillingTween_1837: out = this->f_fillingTween; return true;
        case SYM_GEN_filling_1838: out = this->f_filling; return true;
        case SYM_GEN_fillingGlow_1839: out = this->f_fillingGlow; return true;
        case SYM_GEN_fillingHeight_1840: out = this->f_fillingHeight; return true;
        case SYM_GEN_fillingAnimation_1841: out = this->f_fillingAnimation; return true;
        case SYM_GEN_manaNeededForLifesteal_1842: out = this->f_manaNeededForLifesteal; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Manathirst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaGained_1836: this->f_manaGained = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fillingTween_1837: this->f_fillingTween = val; return true;
        case SYM_GEN_filling_1838: this->f_filling = val; return true;
        case SYM_GEN_fillingGlow_1839: this->f_fillingGlow = val; return true;
        case SYM_GEN_fillingHeight_1840: this->f_fillingHeight = val; return true;
        case SYM_GEN_fillingAnimation_1841: this->f_fillingAnimation = val; return true;
        case SYM_GEN_manaNeededForLifesteal_1842: this->f_manaNeededForLifesteal = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Manathirst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_tweenFilling_1843: return true;
        case SYM_GEN_onManaChanged_1834: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Manathirst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_tweenFilling_1843: out = fn_tweenFilling(args, argc); return true;
        case SYM_GEN_onManaChanged_1834: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1843, _ca, 1); })();
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
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getVampirism_1210, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_331, _ca, 3); })();
        }
        gd::GdVal lv_relHeight = gd::gd_div(gd_ctx, this->f_manaGained, this->f_manaNeededForLifesteal);
        (void)([&]() { gd::GdVal _ca[] = {lv_relHeight}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1843, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1843, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Manathirst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaNeededForLifesteal = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_affectedPotions_1870: out = this->f_affectedPotions; return true;
        case SYM_GEN_numConsumed_1871: out = this->f_numConsumed; return true;
        default: break;
    }
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__PotionBelt::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedPotions_1870: this->f_affectedPotions = val; return true;
        case SYM_GEN_numConsumed_1871: this->f_numConsumed = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PotionBelt::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPotionEmptied_1872: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__PotionBelt::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPotionEmptied_1872: out = fn_onPotionEmptied(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t482 = gd::gd_iter_seq(gd_ctx.arena, lv_affectedItems);
        gd::GdArr* _t483 = (_t482.kind == gd::GdVal::Kind::Arr) ? _t482.arr : nullptr;
        uint32_t _len__t484 = _t483 ? _t483->len : 0u;
        for (uint32_t _t484 = 0; _t484 < _len__t484; ++_t484) {
            gd::GdVal lv_item = _t483->data[_t484];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_affectedPotions, gd::SYM_push_back, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_emptied", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPotionEmptied", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
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
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
        lv_active = gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        lv_numBuffs = gd::gd_add(gd_ctx, lv_numBuffs, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })(), SYM_GEN_getP_190, _ca, 1); })()));
        lv_active = gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numBuffs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_numBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 1); })();
    }
    if (gd::gd_truth(lv_active)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PotionBelt::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PotionBelt::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_buffActive_1718: out = this->f_buffActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_unhealingTimer_1889: out = this->f_unhealingTimer; return true;
        case SYM_GEN_manaCost_1720: out = this->f_manaCost; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__StaffofUnhealing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffActive_1718: this->f_buffActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_unhealingTimer_1889: this->f_unhealingTimer = val; return true;
        case SYM_GEN_manaCost_1720: this->f_manaCost = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StaffofUnhealing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__StaffofUnhealing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StaffofUnhealing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        gd::GdVal lv_healAmount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaCost)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffActive)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveUnhealing_1162, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_unhealing", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_start_1685, _ca, 1); })();
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_reduceUnhealing_1163, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaffofUnhealing::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_unhealingTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "UnhealingTimer", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_manaCost = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__TheFool::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "revealspeed", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t485 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1737));
        gd::GdArr* _t486 = (_t485.kind == gd::GdVal::Kind::Arr) ? _t485.arr : nullptr;
        uint32_t _len__t487 = _t486 ? _t486->len : 0u;
        for (uint32_t _t487 = 0; _t487 < _len__t487; ++_t487) {
            gd::GdVal lv_card = _t486->data[_t487];
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::call_method(gd_ctx, lv_card, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__TheFool::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_preCombatStart_126: return true;
        case SYM_GEN_getNextCard_891: return true;
        case SYM_GEN_startActivation_892: return true;
        case SYM_GEN_playActivationAnimation_778: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN_trigger_145: return true;
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_notifyChainPosition_894: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_getCardDescription_895: return true;
        case SYM_GEN__readyInit_142: return true;
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
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_preCombatStart_126: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_getNextCard_891: out = fn_getNextCard(args, argc); return true;
        case SYM_GEN_startActivation_892: out = fn_startActivation(args, argc); return true;
        case SYM_GEN_playActivationAnimation_778: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_trigger_145: out = fn_trigger(args, argc); return true;
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_notifyChainPosition_894: out = fn_notifyChainPosition(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getCardDescription_895: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
        return (gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_882), this->f_chainPosition))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_882), gd::gd_neg(gd::GdVal::from_int(1LL))))))))) : gd::GdVal::from_bool(false));
    }
    else {
        return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_deck_883))))) : gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_126, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_101, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_getNextCard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_425, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_hasType_81, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
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
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_104, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_100, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1621));
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_101, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doRevealEffect_893, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_133, nullptr, 0, _out); return _out; })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_122, _ca, 3, _out); return _out; })();
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
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_COUNT", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "num", 3u)), this->f_chainPosition, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })()));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_HINT", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_2673, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Card::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Blueberries::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Blueberries::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Blueberries::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_overflow = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_capped_337, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_overflow, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Blueberries::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onAffectedAttacked_1729: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__CursedHairComb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onAffectedAttacked_1729: out = fn_onAffectedAttacked(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Vampiric_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_addHealingEfficiency_1166, _ca, 1); })();
    {
        gd::GdVal _t488 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t489 = (_t488.kind == gd::GdVal::Kind::Arr) ? _t488.arr : nullptr;
        uint32_t _len__t490 = _t489 ? _t489->len : 0u;
        for (uint32_t _t490 = 0; _t490 < _len__t490; ++_t490) {
            gd::GdVal lv_weapon = _t489->data[_t490];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAffectedAttacked", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn_onAffectedAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        gd::GdVal lv_bonusLifesteal = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal_scaling", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })());
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_div(gd_ctx, gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_bonusLifesteal)), gd::GdVal::from_float(100.0))), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedHairComb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CursedHairComb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__CursedHairComb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__CursedHairComb = {CLS_Gd__gd_core_items__CursedHairComb, "CursedHairComb", "res://gd_core_items/CursedHairComb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__CursedHairComb, &Gd__gd_core_items__CursedHairComb::get_static_prop_fn, &Gd__gd_core_items__CursedHairComb::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofAgility::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_usedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_bonusSpeed = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_refund = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofAgility::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofAgility; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_1927: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.639216), gd::GdVal::from_float(0.635294), gd::GdVal::from_float(0.215686)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_usedStacks_1620: out = this->f_usedStacks; return true;
        case SYM_GEN_bonusSpeed_1787: out = this->f_bonusSpeed; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_refund_1928: out = this->f_refund; return true;
        case SYM_GEN_amuletColor_1927: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_usedStacks_1620: this->f_usedStacks = val; return true;
        case SYM_GEN_bonusSpeed_1787: this->f_bonusSpeed = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_refund_1928: this->f_refund = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onBuffTimeout_1929: return true;
        case SYM_GEN_onBuffChanged_1911: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onBuffTimeout_1929: out = fn_onBuffTimeout(args, argc); return true;
        case SYM_GEN_onBuffChanged_1911: out = fn_onBuffChanged(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_376, _ca, 1); })();
    {
        gd::GdVal _t491 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t492 = (_t491.kind == gd::GdVal::Kind::Arr) ? _t491.arr : nullptr;
        uint32_t _len__t493 = _t492 ? _t492->len : 0u;
        for (uint32_t _t493 = 0; _t493 < _len__t493; ++_t493) {
            gd::GdVal lv_buff = _t492->data[_t493];
            { gd::GdVal _t494 = this->f_usedStacks; gd::GdVal _t495 = lv_buff; gd::set_index(gd_ctx, _t494, _t495, gd::GdVal::from_float(0.0)); }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
    {
        gd::GdVal _t496 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t497 = (_t496.kind == gd::GdVal::Kind::Arr) ? _t496.arr : nullptr;
        uint32_t _len__t498 = _t497 ? _t497->len : 0u;
        for (uint32_t _t498 = 0; _t498 < _len__t498; ++_t498) {
            gd::GdVal lv_item = _t497->data[_t498];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onBuffTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t499 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t500 = (_t499.kind == gd::GdVal::Kind::Arr) ? _t499.arr : nullptr;
        uint32_t _len__t501 = _t500 ? _t500->len : 0u;
        for (uint32_t _t501 = 0; _t501 < _len__t501; ++_t501) {
            gd::GdVal lv_item = _t500->data[_t501];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onBuffChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1484, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_used = gd::gd_neg(lv_amount);
        gd::GdVal lv_buffType = gd::call_method(gd_ctx, lv_event, SYM_GEN_getType_1481, nullptr, 0);
        { gd::GdVal _t502 = this->f_usedStacks; gd::GdVal _t503 = lv_buffType; gd::set_index(gd_ctx, _t502, _t503, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t502, _t503), gd::gd_mul(lv_used, this->f_refund))); }
        gd::GdVal lv_toRefund = gd::gd_coerce_int(gd::gd_round(gd::get_index(gd_ctx, this->f_usedStacks, lv_buffType)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_toRefund, gd::GdVal::from_int(0LL))))) {
            { gd::GdVal _t504 = this->f_usedStacks; gd::GdVal _t505 = lv_buffType; gd::set_index(gd_ctx, _t504, _t505, gd::gd_sub(gd::get_index(gd_ctx, _t504, _t505), lv_toRefund)); }
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_buffType, lv_toRefund, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffTimeout", 13u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_refund = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "refund", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofAgility(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofAgility>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofAgility = {CLS_Gd__gd_core_items__Exclusive__AmuletofAgility, "AmuletofAgility", "res://gd_core_items/Exclusive/AmuletofAgility.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofAgility, &Gd__gd_core_items__Exclusive__AmuletofAgility::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofAgility::call_static_fn};

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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__PowerPuppy::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Pet_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numFood = gd::GdVal::from_int(0LL);
    gd::GdVal lv_numPets = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t506 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t507 = (_t506.kind == gd::GdVal::Kind::Arr) ? _t506.arr : nullptr;
        uint32_t _len__t508 = _t507 ? _t507->len : 0u;
        for (uint32_t _t508 = 0; _t508 < _len__t508; ++_t508) {
            gd::GdVal lv_item = _t507->data[_t508];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_numFood = gd::gd_add(gd_ctx, lv_numFood, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Pet_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_numPets = gd::gd_add(gd_ctx, lv_numPets, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::gd_mul(lv_numPets, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)), gd::gd_mul(lv_numFood, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0))), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ArmoredPowerPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__PowerPuppy::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_damPerVampOrSpike_1977: out = this->f_damPerVampOrSpike; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damPerVampOrSpike_1977: this->f_damPerVampOrSpike = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BigBloodthorne::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Greatsword::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Greatsword::call_method(gd_ctx, SYM_GEN_onPrepare_125, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_vampirism_changed", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onVampirismChanged", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerVampOrSpike)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_damPerVampOrSpike)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0), this->f_regenNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BigBloodthorne::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Greatsword::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damPerVampOrSpike = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_luckNeeded_1779: out = this->f_luckNeeded; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_luckNeeded_1779: this->f_luckNeeded = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BroccoliGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BroccoliGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BroccoliGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_PieceColor_2054: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor);
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
        case SYM_GEN_pieceColor_2039: out = this->f_pieceColor; return true;
        case SYM_GEN_moveCells_2040: out = this->f_moveCells; return true;
        case SYM_GEN_captured_2041: out = this->f_captured; return true;
        case SYM_GEN_numCaptures_2042: out = this->f_numCaptures; return true;
        case SYM_GEN_board_2043: out = this->f_board; return true;
        case SYM_GEN_noBoardMark_2044: out = this->f_noBoardMark; return true;
        case SYM_GEN_PieceColor_2054: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__Chess__ChessPiece_PieceColor); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_pieceColor_2039: this->f_pieceColor = gd::gd_coerce_int(val); return true;
        case SYM_GEN_moveCells_2040: this->f_moveCells = val; return true;
        case SYM_GEN_captured_2041: this->f_captured = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_numCaptures_2042: this->f_numCaptures = gd::gd_coerce_int(val); return true;
        case SYM_GEN_board_2043: this->f_board = val; return true;
        case SYM_GEN_noBoardMark_2044: this->f_noBoardMark = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_affectsEmpty_257: return true;
        case SYM_GEN_setBoard_2045: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_getMoveCells_2046: return true;
        case SYM_GEN_getCaptureCells_2047: return true;
        case SYM_GEN_onPieceMoved_2048: return true;
        case SYM_GEN_onPieceCaptured_2049: return true;
        case SYM_GEN_doCapturingEffect_2050: return true;
        case SYM_GEN_onEliminatedBy_2051: return true;
        case SYM_GEN_doEliminatedEffect_2052: return true;
        case SYM_GEN_repositionPiece_2053: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN_canBeBlocked_1467: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_affectsEmpty_257: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_setBoard_2045: out = fn_setBoard(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_getMoveCells_2046: out = fn_getMoveCells(args, argc); return true;
        case SYM_GEN_getCaptureCells_2047: out = fn_getCaptureCells(args, argc); return true;
        case SYM_GEN_onPieceMoved_2048: out = fn_onPieceMoved(args, argc); return true;
        case SYM_GEN_onPieceCaptured_2049: out = fn_onPieceCaptured(args, argc); return true;
        case SYM_GEN_doCapturingEffect_2050: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_onEliminatedBy_2051: out = fn_onEliminatedBy(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2052: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_repositionPiece_2053: out = fn_repositionPiece(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN_canBeBlocked_1467: out = fn_canBeBlocked(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_ChessPiece_2674)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_pieceColor_2039), this->f_pieceColor)))) : gd::GdVal::from_bool(false));
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
    (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, this->f_occupiedCells, gd::GdVal::from_int(0LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)gd::call_method(gd_ctx, this->f_moveCells, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t509 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_tilemap_410, nullptr, 0));
        gd::GdArr* _t510 = (_t509.kind == gd::GdVal::Kind::Arr) ? _t509.arr : nullptr;
        uint32_t _len__t511 = _t510 ? _t510->len : 0u;
        for (uint32_t _t511 = 0; _t511 < _len__t511; ++_t511) {
            gd::GdVal lv_cell = _t510->data[_t511];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::gd_sub(lv_cell, gd::get_index(gd_ctx, this->f_occupiedCells, gd::GdVal::from_int(0LL))), gd::SYM_round, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_moveCells, gd::SYM_push_back, _ca, 1); })();
        }
    }
    this->f_numCaptures = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_targetCell}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onPieceCaptured(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_activateEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_numCaptures = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numCaptures, gd::GdVal::from_int(1LL)));
    gd::GdVal lv_targetCell = gd::get_index(gd_ctx, gd::get_prop(gd_ctx, lv_eliminatedPiece, SYM_GEN_occupiedCells_54), gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {lv_eliminatedPiece}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_clearItemCells_1529, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_targetCell, gd::GdVal::from_bool(false), lv_activateEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::null(), gd::GdVal::null(), gd::GdVal::null()})), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Exclusive/Chess/ChessPiece.gd:74", 32u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_pickRandomEngine_1652, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_eliminatedPiece}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCapturingEffect_2050, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_activateEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_capturingPiece}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doEliminatedEffect_2052, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_toCell}))}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_moveItem_1530, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__ChessPiece::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::GdVal::from_int(gd::gd_typeof(lv_state)), gd::GdVal::from_int(5))))) {
        gd::GdVal lv_targetCell = lv_state;
        (void)([&]() { gd::GdVal _ca[] = {lv_targetCell}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_repositionPiece_2053, _ca, 1); })();
    }
    else {
        this->f_captured = gd::gd_coerce_bool(lv_state);
        if (gd::gd_truth(this->f_captured)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_clearItemCells_1529, _ca, 1); })();
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
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "HINT_Chess", 10u)), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_2673, _ca, 2); })()));
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::gd_in(gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "White", 5u)), this->f_name))) {
        this->f_pieceColor = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, SYM_GEN_PieceColor_2054), SYM_GEN_White_2675));
    }
    else {
        this->f_pieceColor = gd::gd_coerce_int(gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, SYM_GEN_PieceColor_2054), SYM_GEN_Black_2676));
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChiliPepper::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliPepper::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliPepper::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_boosted_2101: out = this->f_boosted; return true;
        case SYM_GEN_crystalDescriptor_2102: out = this->f_crystalDescriptor; return true;
        case SYM_GEN_debuffs_2055: out = this->f_debuffs; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_darkSpeed_2103: out = this->f_darkSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2101: this->f_boosted = val; return true;
        case SYM_GEN_crystalDescriptor_2102: this->f_crystalDescriptor = val; return true;
        case SYM_GEN_debuffs_2055: this->f_debuffs = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_darkSpeed_2103: this->f_darkSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN_onItemRolled_1924: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DarkRitual::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1924: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_debuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_359, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkRitual::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numDark = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numDark, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_darkSpeed, lv_numDark)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_crystalDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Corrupted Crystal", 17u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_debuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffs", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_darkSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_hasActivated_1811: out = this->f_hasActivated; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1811: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onBattleRageStarted_1971: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonskinBoots::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1971: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeResistChance_1025, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonskinBoots::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonskinBoots::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_activated_1296: out = this->f_activated; return true;
        case SYM_GEN_battleRageDur_2158: out = this->f_battleRageDur; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1296: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_battleRageDur_2158: this->f_battleRageDur = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_preCombatStart_126: return true;
        case SYM_GEN_onBattleRageStarted_1971: return true;
        case SYM_GEN_onBattleRageEnded_1972: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ExtraAngy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preCombatStart_126: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1971: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1972: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_126, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_101, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        this->f_battleRageDur = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "duration", 8u)), gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1484, _ca, 2); })());
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_100, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dur = gd::gd_div(gd_ctx, gd::gd_mul(this->f_battleRageDur, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()), gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_dur, gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_startBattleRage_1183, _ca, 4); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraAngy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_FrogState_2182: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__FrogPrince_FrogState);
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
        case SYM_GEN_frogState_2181: out = this->f_frogState; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_blind_1816: out = this->f_blind; return true;
        case SYM_GEN_FrogState_2182: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__FrogPrince_FrogState); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_frogState_2181: this->f_frogState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        case SYM_GEN_blind_1816: this->f_blind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onGainThresholdReached_2179: return true;
        case SYM_GEN_onUseThresholdReached_2180: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Toad::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FrogPrince::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onGainThresholdReached_2179: out = fn_onGainThresholdReached(args, argc); return true;
        case SYM_GEN_onUseThresholdReached_2180: out = fn_onUseThresholdReached(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseBlind_346, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onUseThresholdReached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ticks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_frogState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2182), SYM_GEN_Inactive_2594))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2182), SYM_GEN_Active_2595), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_1", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_makeInvulnerable_1195, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Toad::call_method(gd_ctx, SYM_GEN_onPrepare_125, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2182), SYM_GEN_Inactive_2594)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2182), SYM_GEN_Used_2596), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2182), SYM_GEN_Inactive_2594)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__frogState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__frogState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2182), SYM_GEN_Inactive_2594))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__frogState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__FrogPrince::get_static_const_or_enum(gd_ctx, SYM_GEN_FrogState_2182), SYM_GEN_Active_2595))))) {
    }
    else {
    }
    this->f_frogState = gd::gd_coerce_int(lv__frogState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FrogPrince::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Toad::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FrogPrince(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FrogPrince>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FrogPrince = {CLS_Gd__gd_core_items__Exclusive__FrogPrince, "FrogPrince", "res://gd_core_items/Exclusive/FrogPrince.gd", &META_Gd__gd_core_items__Exclusive__Toad, true, _alloc_Gd__gd_core_items__Exclusive__FrogPrince, &Gd__gd_core_items__Exclusive__FrogPrince::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FrogPrince::call_static_fn};

void Gd__gd_core_items__Exclusive__HeartShield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Shield::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_regenGiven = gd::GdVal::from_int(0);
    this->f_fillAnimation = gd::GdVal::null();
    this->f_healamp = gd::GdVal::null();
    this->f_blockFactor = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_regenOnBlock = gd::GdVal::null();
    this->f_regenMax = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HeartShield::meta() const { return &META_Gd__gd_core_items__Exclusive__HeartShield; }
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HeartShield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HeartShield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1296: out = this->f_activated; return true;
        case SYM_GEN_regenGiven_2203: out = this->f_regenGiven; return true;
        case SYM_GEN_fillAnimation_1795: out = this->f_fillAnimation; return true;
        case SYM_GEN_healamp_2062: out = this->f_healamp; return true;
        case SYM_GEN_blockFactor_1882: out = this->f_blockFactor; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_regenOnBlock_2204: out = this->f_regenOnBlock; return true;
        case SYM_GEN_regenMax_2205: out = this->f_regenMax; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeartShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1296: this->f_activated = val; return true;
        case SYM_GEN_regenGiven_2203: this->f_regenGiven = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fillAnimation_1795: this->f_fillAnimation = val; return true;
        case SYM_GEN_healamp_2062: this->f_healamp = val; return true;
        case SYM_GEN_blockFactor_1882: this->f_blockFactor = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_regenOnBlock_2204: this->f_regenOnBlock = val; return true;
        case SYM_GEN_regenMax_2205: this->f_regenMax = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeartShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_afterBlock_1847: return true;
        case SYM_GEN_onRegenChanged_1796: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_preTakeDamage_1849: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeartShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1847: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_onRegenChanged_1796: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_preTakeDamage_1849: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HeartShield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_293, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canHealOrLifesteal_294, nullptr, 0))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Regeneration_2569)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_88, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t512 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t513 = (_t512.kind == gd::GdVal::Kind::Arr) ? _t512.arr : nullptr;
        uint32_t _len__t514 = _t513 ? _t513->len : 0u;
        for (uint32_t _t514 = 0; _t514 < _len__t514; ++_t514) {
            gd::GdVal lv_item = _t513->data[_t514];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), this->f_blockFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_healamp}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeHealAmp_306, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_198, _ca, 2); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    this->f_regenGiven = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_119, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_regenGiven, this->f_regenMax)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regenOnBlock, gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
        this->f_regenGiven = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_regenGiven, this->f_regenOnBlock));
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
        gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_filled = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activated, lv_filled)))) {
        return gd::GdVal::null();
    }
    this->f_activated = lv_filled;
    if (gd::gd_truth(lv_filled)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_activated)) {
        if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttackOrEffect_1471, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            this->f_blockedDamageRes = lv_damageRes;
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_beforeBlock_1846, nullptr, 0);
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN_preTakeDamage_1849, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healamp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_blockFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regenOnBlock = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regenMax = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max_regen", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HeartShield(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HeartShield>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeartShield = {CLS_Gd__gd_core_items__Exclusive__HeartShield, "HeartShield", "res://gd_core_items/Exclusive/HeartShield.gd", &META_Gd__gd_core_items__Shield, true, _alloc_Gd__gd_core_items__Exclusive__HeartShield, &Gd__gd_core_items__Exclusive__HeartShield::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HeartShield::call_static_fn};

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
        case SYM_GEN_quads_2230: out = this->f_quads; return true;
        case SYM_GEN_triplets_2231: out = this->f_triplets; return true;
        case SYM_GEN_pairs_2232: out = this->f_pairs; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_staminaReduction_1918: out = this->f_staminaReduction; return true;
        case SYM_GEN_revealsPerQuad_2233: out = this->f_revealsPerQuad; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Joker::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_quads_2230: this->f_quads = val; return true;
        case SYM_GEN_triplets_2231: this->f_triplets = val; return true;
        case SYM_GEN_pairs_2232: this->f_pairs = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_staminaReduction_1918: this->f_staminaReduction = val; return true;
        case SYM_GEN_revealsPerQuad_2233: this->f_revealsPerQuad = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Joker::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_countChain_2234: return true;
        case SYM_GEN_notifyChainPosition_894: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN_getCardDescription_895: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Joker::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_countChain_2234: out = fn_countChain(args, argc); return true;
        case SYM_GEN_notifyChainPosition_894: out = fn_notifyChainPosition(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_getCardDescription_895: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
            gd::GdVal _t515 = gd::gd_iter_seq(gd_ctx.arena, this->f_chainPosition);
            gd::GdArr* _t516 = (_t515.kind == gd::GdVal::Kind::Arr) ? _t515.arr : nullptr;
            uint32_t _len__t517 = _t516 ? _t516->len : 0u;
            for (uint32_t _t517 = 0; _t517 < _len__t517; ++_t517) {
                gd::GdVal lv_i = _t516->data[_t517];
                (void)([&]() { gd::GdVal _ca[] = {lv_counter, gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1737), lv_i), SYM_GEN_descriptor_2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_dictAdd_1694, _ca, 2); })();
            }
        }
        {
            gd::GdVal _t518 = gd::gd_iter_seq(gd_ctx.arena, lv_counter);
            gd::GdArr* _t519 = (_t518.kind == gd::GdVal::Kind::Arr) ? _t518.arr : nullptr;
            uint32_t _len__t520 = _t519 ? _t519->len : 0u;
            for (uint32_t _t520 = 0; _t520 < _len__t520; ++_t520) {
                gd::GdVal lv_cardType = _t519->data[_t520];
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countChain_2234, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_pairs, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_pairs}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_gainCritResistStacks_1159, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_triplets, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t521 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
            gd::GdArr* _t522 = (_t521.kind == gd::GdVal::Kind::Arr) ? _t521.arr : nullptr;
            uint32_t _len__t523 = _t522 ? _t522->len : 0u;
            for (uint32_t _t523 = 0; _t523 < _len__t523; ++_t523) {
                gd::GdVal lv_item = _t522->data[_t523];
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(this->f_staminaReduction), this->f_triplets)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_307, _ca, 1); })();
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_quads, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_legitCards = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t524 = gd::gd_iter_seq(gd_ctx.arena, this->f_chainPosition);
            gd::GdArr* _t525 = (_t524.kind == gd::GdVal::Kind::Arr) ? _t524.arr : nullptr;
            uint32_t _len__t526 = _t525 ? _t525->len : 0u;
            for (uint32_t _t526 = 0; _t526 < _len__t526; ++_t526) {
                gd::GdVal lv_i = _t525->data[_t526];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1737), lv_i), SYM_GEN_descriptor_2), this->f_descriptor)))) {
                    (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_deck, SYM_GEN_cards_1737), lv_i)}; return gd::call_method(gd_ctx, lv_legitCards, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
        {
            gd::GdVal _t527 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_mul(this->f_quads, this->f_revealsPerQuad));
            gd::GdArr* _t528 = (_t527.kind == gd::GdVal::Kind::Arr) ? _t527.arr : nullptr;
            uint32_t _len__t529 = _t528 ? _t528->len : 0u;
            for (uint32_t _t529 = 0; _t529 < _len__t529; ++_t529) {
                gd::GdVal lv_i = _t528->data[_t529];
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_legitCards, gd::SYM_empty, nullptr, 0))))) {
                    gd::GdVal lv_revealedCard = ([&]() { gd::GdVal _ca[] = {lv_legitCards}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
                    (void)gd::call_method(gd_ctx, lv_revealedCard, SYM_GEN_doRevealEffect_893, nullptr, 0);
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_legitCards, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL))))) {
                        (void)([&]() { gd::GdVal _ca[] = {lv_revealedCard}; return gd::call_method(gd_ctx, lv_legitCards, gd::SYM_erase, _ca, 1); })();
                    }
                }
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        gd::GdVal lv_counterText = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Joker_COUNTER", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })();
        gd::GdVal lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_pairs, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Positive_2549);
        }
        else {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Negative_2550);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pairs", 5u)), this->f_pairs, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_triplets, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Positive_2549);
        }
        else {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Negative_2550);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "triplets", 8u)), this->f_triplets, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_quads, gd::GdVal::from_int(0LL))))) {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Positive_2549);
        }
        else {
            lv_state = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Negative_2550);
        }
        lv_counterText = ([&]() { gd::GdVal _ca[] = {lv_counterText, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "quadruples", 10u)), this->f_quads, lv_state, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })();
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), lv_counterText));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_HINT", 9u)), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_2673, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Joker::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_revealsPerQuad = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cards", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_blockRemoval_1802: out = this->f_blockRemoval; return true;
        case SYM_GEN_damResistance_2257: out = this->f_damResistance; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LongSpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockRemoval_1802: this->f_blockRemoval = val; return true;
        case SYM_GEN_damResistance_2257: this->f_damResistance = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LongSpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_addToStorageBox_667: return true;
        case SYM_GEN_affectsEmpty_257: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LongSpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToStorageBox_667: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_affectsEmpty_257: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_469, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_addToStorageBox_667, _ca, 6, _out); return _out; })();
        (void)([&]() { gd::GdVal _ca[] = {lv_curDir}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_469, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirection_480, _ca, 1); })();
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
    this->f_blockRemoval = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_428, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_blockRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_207, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damResistance)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LongSpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damResistance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
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
        case SYM_GEN_stackTypes_1831: out = this->f_stackTypes; return true;
        case SYM_GEN_activated_1296: out = this->f_activated; return true;
        case SYM_GEN_sales_2261: out = this->f_sales; return true;
        case SYM_GEN_luckNeeded_1779: out = this->f_luckNeeded; return true;
        case SYM_GEN_numBuffs_1910: out = this->f_numBuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MegaClover::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1831: this->f_stackTypes = val; return true;
        case SYM_GEN_activated_1296: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_sales_2261: this->f_sales = val; return true;
        case SYM_GEN_luckNeeded_1779: this->f_luckNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_numBuffs_1910: this->f_numBuffs = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MegaClover::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN_onSaleRoll_1998: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MegaClover::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_onSaleRoll_1998: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckyChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MegaClover::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_luckNeeded)))) : gd::GdVal::from_bool(false)))) {
        this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs, lv_event, this->f_stackTypes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_sales = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sales", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckneeded", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_stackTypes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570)}; return gd::call_method(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
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
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        case SYM_GEN_fatigueMana_2323: out = this->f_fatigueMana; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        case SYM_GEN_fatigueMana_2323: this->f_fatigueMana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__OwlSpirit::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_298, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t530 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t531 = (_t530.kind == gd::GdVal::Kind::Arr) ? _t530.arr : nullptr;
        uint32_t _len__t532 = _t531 ? _t531->len : 0u;
        for (uint32_t _t532 = 0; _t532 < _len__t532; ++_t532) {
            gd::GdVal lv_item = _t531->data[_t532];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_199, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1392), SYM_GEN_hasFatigueStarted_1309, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_fatigueMana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OwlSpirit::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_fatigueMana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fatiguemana", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_numFood_2341: out = this->f_numFood; return true;
        case SYM_GEN_foodPotionSpeed_2342: out = this->f_foodPotionSpeed; return true;
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Pot::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numFood_2341: this->f_numFood = gd::gd_coerce_int(val); return true;
        case SYM_GEN_foodPotionSpeed_2342: this->f_foodPotionSpeed = val; return true;
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Pot::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onPotionTriggered_2343: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Pot::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPotionTriggered_2343: out = fn_onPotionTriggered(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numFood = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_foodPotionSpeed, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), this->f_numFood))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    {
        gd::GdVal _t533 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t534 = (_t533.kind == gd::GdVal::Kind::Arr) ? _t533.arr : nullptr;
        uint32_t _len__t535 = _t534 ? _t534->len : 0u;
        for (uint32_t _t535 = 0; _t535 < _len__t535; ++_t535) {
            gd::GdVal lv_item = _t534->data[_t535];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_triggered", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPotionTriggered", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn_onPotionTriggered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__potion = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal_food", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), this->f_numFood))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Pot::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_foodPotionSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
    {
        gd::GdVal _t536 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t537 = (_t536.kind == gd::GdVal::Kind::Arr) ? _t536.arr : nullptr;
        uint32_t _len__t538 = _t537 ? _t537->len : 0u;
        for (uint32_t _t538 = 0; _t538 < _len__t538; ++_t538) {
            gd::GdVal lv_item = _t537->data[_t538];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        case SYM_GEN_speedPerGold_2255: out = this->f_speedPerGold; return true;
        case SYM_GEN_maxGoldDif_2381: out = this->f_maxGoldDif; return true;
        case SYM_GEN_equilibriumSpeed_2382: out = this->f_equilibriumSpeed; return true;
        case SYM_GEN_leftCounter_2383: out = this->f_leftCounter; return true;
        case SYM_GEN_rightCounter_2384: out = this->f_rightCounter; return true;
        case SYM_GEN_leftCounterDefaultPos_2385: out = this->f_leftCounterDefaultPos; return true;
        case SYM_GEN_rightCounterDefaultPos_2386: out = this->f_rightCounterDefaultPos; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Scale::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        case SYM_GEN_speedPerGold_2255: this->f_speedPerGold = val; return true;
        case SYM_GEN_maxGoldDif_2381: this->f_maxGoldDif = val; return true;
        case SYM_GEN_equilibriumSpeed_2382: this->f_equilibriumSpeed = val; return true;
        case SYM_GEN_leftCounter_2383: this->f_leftCounter = val; return true;
        case SYM_GEN_rightCounter_2384: this->f_rightCounter = val; return true;
        case SYM_GEN_leftCounterDefaultPos_2385: this->f_leftCounterDefaultPos = val; return true;
        case SYM_GEN_rightCounterDefaultPos_2386: this->f_rightCounterDefaultPos = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Scale::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_ready_deferred_465: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_getCounterValue_2256: return true;
        case SYM_GEN_getCounterValue2_2387: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_updateScale_2388: return true;
        case SYM_GEN_onAffectedItemAdded_437: return true;
        case SYM_GEN_onAffectedItemRemoved_438: return true;
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_updateCounterPositions_2389: return true;
        case SYM_GEN_rotateTo_478: return true;
        case SYM_GEN_onDraggedWithParentEnd_720: return true;
        case SYM_GEN_onCalcTradeChance_1730: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Scale::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_ready_deferred_465: out = fn_ready_deferred(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_getCounterValue_2256: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_getCounterValue2_2387: out = fn_getCounterValue2(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_updateScale_2388: out = fn_updateScale(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_437: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_438: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_updateCounterPositions_2389: out = fn_updateCounterPositions(args, argc); return true;
        case SYM_GEN_rotateTo_478: out = fn_rotateTo(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_720: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1730: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Scale::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_ready_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_ready_deferred_465, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2389, nullptr, 0);
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
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t539 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
            gd::GdArr* _t540 = (_t539.kind == gd::GdVal::Kind::Arr) ? _t539.arr : nullptr;
            uint32_t _len__t541 = _t540 ? _t540->len : 0u;
            for (uint32_t _t541 = 0; _t541 < _len__t541; ++_t541) {
                gd::GdVal lv_item = _t540->data[_t541];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_394, nullptr, 0));
            }
        }
    }
    else {
        {
            gd::GdVal _t542 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_nocache_423, _ca, 1); })());
            gd::GdArr* _t543 = (_t542.kind == gd::GdVal::Kind::Arr) ? _t542.arr : nullptr;
            uint32_t _len__t544 = _t543 ? _t543->len : 0u;
            for (uint32_t _t544 = 0; _t544 < _len__t544; ++_t544) {
                gd::GdVal lv_item = _t543->data[_t544];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_394, nullptr, 0));
            }
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_getCounterValue2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2256, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_c1 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2256, nullptr, 0);
    gd::GdVal lv_c2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue2_2387, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerGold, gd::gd_min(lv_c1, lv_c2))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::gd_abs(gd::gd_sub(lv_c1, lv_c2)), this->f_maxGoldDif)))) {
        {
            gd::GdVal _t545 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
            gd::GdArr* _t546 = (_t545.kind == gd::GdVal::Kind::Arr) ? _t545.arr : nullptr;
            uint32_t _len__t547 = _t546 ? _t546->len : 0u;
            for (uint32_t _t547 = 0; _t547 < _len__t547; ++_t547) {
                gd::GdVal lv_item = _t546->data[_t547];
                (void)([&]() { gd::GdVal _ca[] = {this->f_equilibriumSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
            }
        }
        {
            gd::GdVal _t548 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
            gd::GdArr* _t549 = (_t548.kind == gd::GdVal::Kind::Arr) ? _t548.arr : nullptr;
            uint32_t _len__t550 = _t549 ? _t549->len : 0u;
            for (uint32_t _t550 = 0; _t550 < _len__t550; ++_t550) {
                gd::GdVal lv_item = _t549->data[_t550];
                (void)([&]() { gd::GdVal _ca[] = {this->f_equilibriumSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_curRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0);
    gd::GdVal lv_curMana = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curMana, lv_curRegen)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curRegen, lv_curMana)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    else {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_flip_1639, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_updateScale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_c1 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2256, nullptr, 0);
    gd::GdVal lv_c2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue2_2387, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2388, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2388, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateScale_2388, nullptr, 0);
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
    (void)([&]() { gd::GdVal _ca[] = {lv_targetRotation, lv_duration}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_rotateTo_478, _ca, 2, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2389, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentEnd_720, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCounterPositions_2389, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Scale::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_speedPerGold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxGoldDif = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_equilibriumSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_gooblingDescriptor_2403: out = this->f_gooblingDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gooblingDescriptor_2403: this->f_gooblingDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_canAffect_global_1919: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SlimeTime::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_canAffect_global_1919: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t551 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t552 = (_t551.kind == gd::GdVal::Kind::Arr) ? _t551.arr : nullptr;
        uint32_t _len__t553 = _t552 ? _t552->len : 0u;
        for (uint32_t _t553 = 0; _t553 < _len__t553; ++_t553) {
            gd::GdVal lv_item = _t552->data[_t553];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_1919, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_onItemActivated_938, _ca, 1); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_gooblingDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Goobling", 8u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
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
        case SYM_GEN_staminaAcc_2433: out = this->f_staminaAcc; return true;
        case SYM_GEN_staminaNeeded_2434: out = this->f_staminaNeeded; return true;
        case SYM_GEN_stamina_2060: out = this->f_stamina; return true;
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaAcc_2433: this->f_staminaAcc = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaNeeded_2434: this->f_staminaNeeded = val; return true;
        case SYM_GEN_stamina_2060: this->f_stamina = val; return true;
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onItemUsedStamina_2435: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpellScrollNature::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemUsedStamina_2435: out = fn_onItemUsedStamina(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canUseStamina_296, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_staminaAcc = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    {
        gd::GdVal _t554 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t555 = (_t554.kind == gd::GdVal::Kind::Arr) ? _t554.arr : nullptr;
        uint32_t _len__t556 = _t555 ? _t555->len : 0u;
        for (uint32_t _t556 = 0; _t556 < _len__t556; ++_t556) {
            gd::GdVal lv_item = _t555->data[_t556];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used_stamina", 12u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemUsedStamina", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
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
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stamina, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
            lv_activating = gd::GdVal::from_bool(true);
        }
        this->f_staminaAcc = gd::gd_coerce_float(gd::gd_sub(this->f_staminaAcc, this->f_staminaNeeded));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_staminaAcc, this->f_staminaNeeded), lv_activating}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollNature::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_staminaNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminat", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_manaNeeded = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpellScrollNature(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpellScrollNature>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollNature = {CLS_Gd__gd_core_items__Exclusive__SpellScrollNature, "SpellScrollNature", "res://gd_core_items/Exclusive/SpellScrollNature.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpellScrollNature, &Gd__gd_core_items__Exclusive__SpellScrollNature::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpellScrollNature::call_static_fn};

void Gd__gd_core_items__Exclusive__StoneGolem::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_hasStunned = gd::GdVal::from_bool(false);
    this->f_empower = gd::GdVal::null();
    this->f_regenThreshold = gd::GdVal::null();
    this->f_bagOfStonesDescriptor = gd::GdVal::null();
    this->f_activationParticles1 = gd::GdVal::null();
    this->f_activationParticles2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StoneGolem::meta() const { return &META_Gd__gd_core_items__Exclusive__StoneGolem; }
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StoneGolem::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1296: out = this->f_activated; return true;
        case SYM_GEN_hasStunned_1879: out = this->f_hasStunned; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_regenThreshold_2458: out = this->f_regenThreshold; return true;
        case SYM_GEN_bagOfStonesDescriptor_2459: out = this->f_bagOfStonesDescriptor; return true;
        case SYM_GEN_activationParticles1_2460: out = this->f_activationParticles1; return true;
        case SYM_GEN_activationParticles2_2461: out = this->f_activationParticles2; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1296: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_hasStunned_1879: this->f_hasStunned = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_regenThreshold_2458: this->f_regenThreshold = val; return true;
        case SYM_GEN_bagOfStonesDescriptor_2459: this->f_bagOfStonesDescriptor = val; return true;
        case SYM_GEN_activationParticles1_2460: this->f_activationParticles1 = val; return true;
        case SYM_GEN_activationParticles2_2461: this->f_activationParticles2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_onRegenChanged_1796: return true;
        case SYM_GEN_attack_941: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onRegenChanged_1796: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_attack_941: out = fn_attack(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneGolem::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_bagOfStonesDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonusdam", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0), this->f_regenThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenThreshold, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_bool(true), lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
            this->f_baseCooldownOverride = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0));
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBaseCooldown_112, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_attack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_hasStunned = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, _ca, 1); })();
    if (gd::gd_truth(this->f_hasStunned)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__StoneGolem::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Tackle_2655)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 4); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
            this->f_hasStunned = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    this->f_activated = gd::gd_coerce_bool(lv_active);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGolem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_regenThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_bagOfStonesDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bag of Stones", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneGolem(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StoneGolem>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneGolem = {CLS_Gd__gd_core_items__Exclusive__StoneGolem, "StoneGolem", "res://gd_core_items/Exclusive/StoneGolem.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__StoneGolem, &Gd__gd_core_items__Exclusive__StoneGolem::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StoneGolem::call_static_fn};

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
        case SYM_GEN_tickI_2498: out = this->f_tickI; return true;
        case SYM_GEN_slow_2499: out = this->f_slow; return true;
        case SYM_GEN_speedUp_2500: out = this->f_speedUp; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_tickI_2498: this->f_tickI = gd::gd_coerce_int(val); return true;
        case SYM_GEN_slow_2499: this->f_slow = val; return true;
        case SYM_GEN_speedUp_2500: this->f_speedUp = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playActivationSound_150: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TimeDilator::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playActivationSound_150: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_allItems = gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), SYM_GEN_INVENTORY_1093), SYM_GEN_getItems_1512, nullptr, 0), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_77), SYM_GEN_INVENTORY_1093), SYM_GEN_getItems_1512, nullptr, 0));
    {
        gd::GdVal _t557 = gd::gd_iter_seq(gd_ctx.arena, lv_allItems);
        gd::GdArr* _t558 = (_t557.kind == gd::GdVal::Kind::Arr) ? _t557.arr : nullptr;
        uint32_t _len__t559 = _t558 ? _t558->len : 0u;
        for (uint32_t _t559 = 0; _t559 < _len__t559; ++_t559) {
            gd::GdVal lv_item = _t558->data[_t559];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_slow}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
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
        gd::GdVal _t560 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t561 = (_t560.kind == gd::GdVal::Kind::Arr) ? _t560.arr : nullptr;
        uint32_t _len__t562 = _t561 ? _t561->len : 0u;
        for (uint32_t _t562 = 0; _t562 < _len__t562; ++_t562) {
            gd::GdVal lv_item = _t561->data[_t562];
            if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isCooldownActive_98, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                gd::GdVal lv_cd = gd::call_method(gd_ctx, lv_item, SYM_GEN_getModifiedCooldown_106, nullptr, 0);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_cd, lv_slowestCd)))) {
                    lv_slowestCd = lv_cd;
                    lv_slowestItem = lv_item;
                }
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_speedUp}; return gd::call_method(gd_ctx, lv_slowestItem, SYM_GEN_addSpeed_275, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_slow = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "slow", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speedUp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_poisonNeeded_2518: out = this->f_poisonNeeded; return true;
        case SYM_GEN_critDamage_2519: out = this->f_critDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WarScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonNeeded_2518: this->f_poisonNeeded = val; return true;
        case SYM_GEN_critDamage_2519: this->f_critDamage = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WarScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WarScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Poison_2567)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_88, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t563 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t564 = (_t563.kind == gd::GdVal::Kind::Arr) ? _t563.arr : nullptr;
        uint32_t _len__t565 = _t564 ? _t564->len : 0u;
        for (uint32_t _t565 = 0; _t565 < _len__t565; ++_t565) {
            gd::GdVal lv_item = _t564->data[_t565];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getPoison_1213, nullptr, 0), this->f_poisonNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_poisonNeeded, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_losePoison_1216, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_181, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_critDamage}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritSeverity_187, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WarScythe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poisonNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poisont", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_critDamage = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "critdam", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_healReduction_2056: out = this->f_healReduction; return true;
        case SYM_GEN_buffRemoval_2091: out = this->f_buffRemoval; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Amethyst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healReduction_2056: this->f_healReduction = val; return true;
        case SYM_GEN_buffRemoval_2091: this->f_buffRemoval = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Amethyst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_1957: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_getBaseDescription_990: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Amethyst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1957: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_getBaseDescription_990: out = fn_getBaseDescription(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Amethyst::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffRemoval, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_374, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), this->f_healReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1167, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn_getBaseDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_238, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_862), SYM_GEN_Godly_2677))))) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Perfect Amethyst_DESCR", 22u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })(), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_643, _ca, 2); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN_getBaseDescription_990, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Amethyst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healReduction = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_buffRemoval = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Amethyst(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Gems__Amethyst>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__Amethyst = {CLS_Gd__gd_core_items__Gems__Amethyst, "Amethyst", "res://gd_core_items/Gems/Amethyst.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Gems__Amethyst, &Gd__gd_core_items__Gems__Amethyst::get_static_prop_fn, &Gd__gd_core_items__Gems__Amethyst::call_static_fn};

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
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_checkStamina_1798: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__HeroicPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_checkStamina_1798: out = fn_checkStamina(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_pre_use_stamina", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStamina", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn_checkStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentStamina_1246, nullptr, 0), lv_amount)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1753, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroicPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HeroicPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HeroicPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__HeroicPotion = {CLS_Gd__gd_core_items__HeroicPotion, "HeroicPotion", "res://gd_core_items/HeroicPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__HeroicPotion, &Gd__gd_core_items__HeroicPotion::get_static_prop_fn, &Gd__gd_core_items__HeroicPotion::call_static_fn};

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
        case SYM_GEN_manaGained_1836: out = this->f_manaGained; return true;
        case SYM_GEN_fillingTween_1837: out = this->f_fillingTween; return true;
        case SYM_GEN_filling_1838: out = this->f_filling; return true;
        case SYM_GEN_fillingGlow_1839: out = this->f_fillingGlow; return true;
        case SYM_GEN_fillingHeight_1840: out = this->f_fillingHeight; return true;
        case SYM_GEN_fillingAnimation_1841: out = this->f_fillingAnimation; return true;
        case SYM_GEN_manaNeededForLifesteal_1842: out = this->f_manaNeededForLifesteal; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Manathirst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaGained_1836: this->f_manaGained = gd::gd_coerce_int(val); return true;
        case SYM_GEN_fillingTween_1837: this->f_fillingTween = val; return true;
        case SYM_GEN_filling_1838: this->f_filling = val; return true;
        case SYM_GEN_fillingGlow_1839: this->f_fillingGlow = val; return true;
        case SYM_GEN_fillingHeight_1840: this->f_fillingHeight = val; return true;
        case SYM_GEN_fillingAnimation_1841: this->f_fillingAnimation = val; return true;
        case SYM_GEN_manaNeededForLifesteal_1842: this->f_manaNeededForLifesteal = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Manathirst::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_tweenFilling_1843: return true;
        case SYM_GEN_onManaChanged_1834: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Manathirst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_tweenFilling_1843: out = fn_tweenFilling(args, argc); return true;
        case SYM_GEN_onManaChanged_1834: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1843, _ca, 1); })();
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
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getVampirism_1210, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_331, _ca, 3); })();
        }
        gd::GdVal lv_relHeight = gd::gd_div(gd_ctx, this->f_manaGained, this->f_manaNeededForLifesteal);
        (void)([&]() { gd::GdVal _ca[] = {lv_relHeight}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1843, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tweenFilling_1843, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Manathirst::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaNeededForLifesteal = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__RainbowGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RainbowGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RainbowGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    {
        gd::GdVal _t566 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t567 = (_t566.kind == gd::GdVal::Kind::Arr) ? _t566.arr : nullptr;
        uint32_t _len__t568 = _t567 ? _t567->len : 0u;
        for (uint32_t _t568 = 0; _t568 < _len__t568; ++_t568) {
            gd::GdVal lv_item = _t567->data[_t568];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RainbowGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_poisonTimer_1900: out = this->f_poisonTimer; return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::get_prop(prop, out);
}
bool Gd__gd_core_items__StrongPestilenceFlask::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poisonTimer_1900: this->f_poisonTimer = val; return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StrongPestilenceFlask::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getAffectedItems_422: return true;
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_poisonTimerTimeout_1901: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::has_own_method(m);
}
bool Gd__gd_core_items__StrongPestilenceFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getAffectedItems_422: out = fn_getAffectedItems(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_poisonTimerTimeout_1901: out = fn_poisonTimerTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StrongPestilenceFlask::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__PestilenceFlask::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_getAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    gd::GdVal lv__r = ([&]() { gd::GdVal _ca[] = {lv_color}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN_getAffectedItems_422, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__cp = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCollisionPoints_408, nullptr, 0);
        gd::GdVal lv__rc = ([&]() { gd::GdVal _ca[] = {lv__cp}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCellsForGlobalPositions_403, _ca, 1); })();
        gd::GdVal lv__cc = ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_417, _ca, 1); })();
        gd::GdVal lv__names = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
        {
            gd::GdVal _t569 = gd::gd_iter_seq(gd_ctx.arena, lv__r);
            gd::GdArr* _t570 = (_t569.kind == gd::GdVal::Kind::Arr) ? _t569.arr : nullptr;
            uint32_t _len__t571 = _t570 ? _t570->len : 0u;
            for (uint32_t _t571 = 0; _t571 < _len__t571; ++_t571) {
                gd::GdVal lv__a = _t570->data[_t571];
                lv__names = gd::gd_add(gd_ctx, lv__names, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv__a, SYM_GEN_descriptor_2), SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "@", 1u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv__a, SYM_GEN_occupiedCells_54)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, ",", 1u))));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "GRD", 3u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fd=", 3u)), ([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " cp=", 4u))), ([&]() { gd::GdVal _ca[] = {lv__cp}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " aff=", 5u))), ([&]() { gd::GdVal _ca[] = {lv__cc}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, lv__names, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n=", 2u))), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv__r, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    }
    return lv__r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1754, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_poisonTimer, SYM_GEN_start_1685, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_poisonTimerTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_poisonTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongPestilenceFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__PestilenceFlask::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poisonTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "PoisonTimer", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poisonTimerTimeout", 18u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongPestilenceFlask(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StrongPestilenceFlask>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StrongPestilenceFlask = {CLS_Gd__gd_core_items__StrongPestilenceFlask, "StrongPestilenceFlask", "res://gd_core_items/StrongPestilenceFlask.gd", &META_Gd__gd_core_items__PestilenceFlask, true, _alloc_Gd__gd_core_items__StrongPestilenceFlask, &Gd__gd_core_items__StrongPestilenceFlask::get_static_prop_fn, &Gd__gd_core_items__StrongPestilenceFlask::call_static_fn};
