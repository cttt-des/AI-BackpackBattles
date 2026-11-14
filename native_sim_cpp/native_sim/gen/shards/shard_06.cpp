#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core_items__Item.hpp"
#include "../hdrs/Gd__gd_core__Bow.hpp"
#include "../hdrs/Gd__gd_core__CoreConst.hpp"
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
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofLife.hpp"
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
#include "../hdrs/Gd__gd_core_items__Exclusive__PiggyPinata.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PuzzlebagJ.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RatChef.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SerpentStaff.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SnowStick.hpp"
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

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Owner[] = {{"Shop", 0LL}, {"PlayerInventory", 1LL}, {"PlayerStorageBox", 2LL}, {"Opponent", 3LL}, {"Title", 4LL}, {"RecipeBook", 5LL}, {"Tooltip", 6LL}, {"Socket", 7LL}, {"ItemLibrary", 8LL}, {"InfoPanelIcon", 9LL}, {"BuildViewer", 10LL}, {"BuildViewerIcon", 11LL}, {"GridStorage", 12LL}, {"Undefined", 13LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Owner = {"Owner", _ekv_Gd__gd_core_items__Item_Owner, 14u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Type[] = {{"Bag", 0LL}, {"Consumable", 1LL}, {"Food", 2LL}, {"Pet", 3LL}, {"Weapon", 4LL}, {"Shield", 5LL}, {"Armor", 6LL}, {"Gloves", 7LL}, {"Shoes", 8LL}, {"Helmet", 9LL}, {"Accessory", 10LL}, {"Potion", 11LL}, {"Card", 12LL}, {"Gem", 13LL}, {"Scroll", 14LL}, {"Book", 15LL}, {"Skill", 16LL}, {"ChessPiece", 17LL}, {"Spell", 18LL}, {"Melee", 19LL}, {"Ranged", 20LL}, {"Effect", 21LL}, {"Holy", 22LL}, {"Magic", 23LL}, {"Vampiric", 24LL}, {"Dark", 25LL}, {"Nature", 26LL}, {"Fire", 27LL}, {"Ice", 28LL}, {"Musical", 29LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Type = {"Type", _ekv_Gd__gd_core_items__Item_Type, 30u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Priority[] = {{"Lowest", -10000LL}, {"Low", -1000LL}, {"Normal", 0LL}, {"High", 1000LL}, {"Highest", 10000LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Priority = {"Priority", _ekv_Gd__gd_core_items__Item_Priority, 5u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_CraftingPriority[] = {{"Gem", 3LL}, {"Mixed", 2LL}, {"NonGem", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_CraftingPriority = {"CraftingPriority", _ekv_Gd__gd_core_items__Item_CraftingPriority, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Tag[] = {{"None", 0LL}, {"Lifesteal", 1LL}, {"Stone", 2LL}, {"Scroll", 8LL}, {"Dragon", 16LL}, {"Staff", 32LL}, {"BattleRage", 64LL}, {"Singular", 128LL}, {"Transient", 256LL}, {"Bow", 512LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Tag = {"Tag", _ekv_Gd__gd_core_items__Item_Tag, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Stack[] = {{"None", 0LL}, {"Block", 1LL}, {"Lucky", 2LL}, {"Regeneration", 4LL}, {"Vampirism", 8LL}, {"Spikes", 16LL}, {"Mana", 32LL}, {"Empower", 64LL}, {"Heat", 128LL}, {"Poison", 256LL}, {"Blind", 512LL}, {"Cold", 1024LL}, {"Buff", 254LL}, {"Debuff", 1792LL}, {"BuffNoLuck", 252LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Stack = {"Stack", _ekv_Gd__gd_core_items__Item_Stack, 15u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Mat[] = {{"Default", 0LL}, {"Wood", 1LL}, {"Metal", 2LL}, {"Leather", 3LL}, {"Glass", 4LL}, {"Stone", 5LL}, {"Squishy", 6LL}, {"Jewelry", 7LL}, {"Sand", 8LL}, {"Paper", 9LL}, {"Slime", 10LL}, {"Ice", 11LL}, {"Fire", 12LL}, {"Dragon", 13LL}, {"Bird", 14LL}, {"Leaf", 15LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Mat = {"Mat", _ekv_Gd__gd_core_items__Item_Mat, 16u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Physics[] = {{"Default", 0LL}, {"Light", 1LL}, {"Slime", 2LL}, {"Dense", 3LL}, {"VeryDense", 4LL}, {"Floaty", 5LL}, {"Sand", 6LL}, {"Plush", 7LL}, {"BouncyDense", 8LL}, {"Ice", 9LL}, {"Ghost", 10LL}, {"BlackHole", 11LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Physics = {"Physics", _ekv_Gd__gd_core_items__Item_Physics, 12u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Rarity[] = {{"Common", 0LL}, {"Rare", 1LL}, {"Epic", 2LL}, {"Legendary", 3LL}, {"Godly", 4LL}, {"Unique", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Rarity = {"Rarity", _ekv_Gd__gd_core_items__Item_Rarity, 6u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_FaceDirection[] = {{"UP", 0LL}, {"RIGHT", 1LL}, {"DOWN", 2LL}, {"LEFT", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_FaceDirection = {"FaceDirection", _ekv_Gd__gd_core_items__Item_FaceDirection, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_StatModified[] = {{"No", 0LL}, {"Positive", 1LL}, {"Negative", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_StatModified = {"StatModified", _ekv_Gd__gd_core_items__Item_StatModified, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_DropResult[] = {{"AddedToInventory", 0LL}, {"Hotswap", 1LL}, {"InventoryCollision", 2LL}, {"OutsideInventory", 3LL}, {"AddedToStorageBox", 4LL}, {"Sold", 5LL}, {"Socketed", 6LL}, {"SocketHotswap", 7LL}, {"Failed", 8LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_DropResult = {"DropResult", _ekv_Gd__gd_core_items__Item_DropResult, 9u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_PickupType[] = {{"Grabbed", 0LL}, {"Hotswap", 1LL}, {"MultiSelect", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_PickupType = {"PickupType", _ekv_Gd__gd_core_items__Item_PickupType, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Affected[] = {{"Primary", 0LL}, {"Secondary", 2LL}, {"Tertiary", 4LL}, {"Lightning", 7LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Affected = {"Affected", _ekv_Gd__gd_core_items__Item_Affected, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Tiles[] = {{"Extension", 2LL}, {"Collision", 3LL}, {"Affected", 4LL}, {"AffectedDynamic", 5LL}, {"AffectedSecondary", 6LL}, {"AffectedSecondaryDynamic", 7LL}, {"AffectedExtension", 8LL}, {"AffectedTertiary", 10LL}, {"AffectedLightning", 11LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Tiles = {"Tiles", _ekv_Gd__gd_core_items__Item_Tiles, 9u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_ActivationAni[] = {{"Scale", 0LL}, {"Jump", 1LL}, {"SquishyJump", 2LL}, {"VerySquishyJump", 3LL}, {"Slash", 4LL}, {"Stab", 5LL}, {"Bonk", 6LL}, {"ReverseBonk", 7LL}, {"Chop", 8LL}, {"Squish", 9LL}, {"Block", 10LL}, {"Wave", 11LL}, {"Potion", 12LL}, {"Sweep", 13LL}, {"Spin", 14LL}, {"Throw", 15LL}, {"Shoot", 16LL}, {"Struggle", 17LL}, {"ReverseStab", 18LL}, {"Hiss", 19LL}, {"Tackle", 20LL}, {"DoubleSlash", 21LL}, {"Flash", 22LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_ActivationAni = {"ActivationAni", _ekv_Gd__gd_core_items__Item_ActivationAni, 23u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_Stat[] = {{"MinDamage", 0LL}, {"MaxDamage", 1LL}, {"StaminaCost", 2LL}, {"Speed", 3LL}, {"BaseCooldown", 4LL}, {"Accuracy", 5LL}, {"CritChance", 6LL}, {"Chance", 7LL}, {"Chance2", 8LL}, {"Cooldown", 9LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_Stat = {"Stat", _ekv_Gd__gd_core_items__Item_Stat, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Item_StackChangeType[] = {{"Added_Player", 0LL}, {"Added_Opponent", 1LL}, {"Removed_Player", 2LL}, {"Removed_Opponent", 3LL}, {"Used_Player", 4LL}, {"Used_Opponent", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Item_StackChangeType = {"StackChangeType", _ekv_Gd__gd_core_items__Item_StackChangeType, 6u};
void Gd__gd_core_items__Item::init_fields(gd::BattleCtx& gd_ctx) {
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
    this->f_crafted_instance = gd::gd_neg(gd::GdVal::from_int(1LL));
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
    this->f_shadowOffset = Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_525);
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
const gd::GdClassMeta* Gd__gd_core_items__Item::meta() const { return &META_Gd__gd_core_items__Item; }
gd::GdVal Gd__gd_core_items__Item::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_Owner_854: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Owner);
        case SYM_GEN_Type_855: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Type);
        case SYM_GEN_Priority_856: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Priority);
        case SYM_GEN_CraftingPriority_857: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_CraftingPriority);
        case SYM_GEN_Tag_858: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Tag);
        case SYM_GEN_Stack_859: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Stack);
        case SYM_GEN_Mat_860: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Mat);
        case SYM_GEN_Physics_861: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Physics);
        case SYM_GEN_Rarity_862: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Rarity);
        case SYM_GEN_FaceDirection_863: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_FaceDirection);
        case SYM_GEN_StatModified_864: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_StatModified);
        case SYM_GEN_DropResult_865: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_DropResult);
        case SYM_GEN_PickupType_866: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_PickupType);
        case SYM_GEN_Affected_867: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Affected);
        case SYM_GEN_Tiles_868: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Tiles);
        case SYM_GEN_ActivationAni_869: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_ActivationAni);
        case SYM_GEN_Stat_870: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Stat);
        case SYM_GEN_StackChangeType_871: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_StackChangeType);
        case SYM_GEN_affectedColorToTileId_509: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581), gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_868), SYM_GEN_Affected_867)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583), gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_868), SYM_GEN_AffectedSecondary_2611)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Tertiary_2584), gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_868), SYM_GEN_AffectedTertiary_2612)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Lightning_2613), gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_868), SYM_GEN_AffectedLightning_2614)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_rarityColors_511: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.460205), gd::GdVal::from_float(0.874887), gd::GdVal::from_float(0.90625)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.0737), gd::GdVal::from_float(0.337874), gd::GdVal::from_float(0.898438)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.828125), gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.609375), gd::GdVal::from_int(0LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.980469), gd::GdVal::from_float(0.946239), gd::GdVal::from_float(0.582153)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.094223), gd::GdVal::from_float(0.964844), gd::GdVal::from_float(0.250663)}; return gd::make_color_from_args(_ca, 3); })()}));
        case SYM_GEN_offset_516: return gd::GdVal::from_int(40LL);
        case SYM_GEN_impulse_517: return gd::GdVal::from_int(50LL);
        case SYM_GEN_momentumFactor_518: return gd::GdVal::from_float(20.0);
        case SYM_GEN_affectedSoundsVolume_521: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581), gd::gd_neg(gd::GdVal::from_int(8LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Tertiary_2584), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Lightning_2613), gd::gd_neg(gd::GdVal::from_int(1LL))); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_cellSize_522: return gd::GdVal::from_vec2((gd::GdVal::from_int(80LL)).as_float(), (gd::GdVal::from_int(80LL)).as_float());
        case SYM_GEN_halfCellSize_523: return gd::gd_mul(gd::GdVal::from_float(0.5), Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522));
        case SYM_GEN_shadowOffset_shop_524: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        case SYM_GEN_shadowOffset_dropped_525: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(5LL)).as_float());
        case SYM_GEN_shadowOffset_dragged_526: return gd::GdVal::from_vec2((gd::GdVal::from_int(15LL)).as_float(), (gd::GdVal::from_int(15LL)).as_float());
        case SYM_GEN_DRAG_PRIORITY_527: return gd::GdVal::from_int(2LL);
        case SYM_GEN_correction_583: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_x))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_x))).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_y))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_y))).as_float())}));
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
        case SYM_GEN_SignalConnection_877: return gd::GdVal::from_cls(&META_Gd__gd_core_items__Item__INNER__SignalConnection);
        default: break;
    }
    return Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Item::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Item::get_prop(gd::SymId prop, gd::GdVal& out) const {
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
        case SYM_GEN_crafted_instance_902: out = this->f_crafted_instance; return true;
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
        case SYM_GEN_Owner_854: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Owner); return true;
        case SYM_GEN_Type_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Type); return true;
        case SYM_GEN_Priority_856: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Priority); return true;
        case SYM_GEN_CraftingPriority_857: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_CraftingPriority); return true;
        case SYM_GEN_Tag_858: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Tag); return true;
        case SYM_GEN_Stack_859: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Stack); return true;
        case SYM_GEN_Mat_860: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Mat); return true;
        case SYM_GEN_Physics_861: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Physics); return true;
        case SYM_GEN_Rarity_862: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Rarity); return true;
        case SYM_GEN_FaceDirection_863: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_FaceDirection); return true;
        case SYM_GEN_StatModified_864: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_StatModified); return true;
        case SYM_GEN_DropResult_865: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_DropResult); return true;
        case SYM_GEN_PickupType_866: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_PickupType); return true;
        case SYM_GEN_Affected_867: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Affected); return true;
        case SYM_GEN_Tiles_868: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Tiles); return true;
        case SYM_GEN_ActivationAni_869: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_ActivationAni); return true;
        case SYM_GEN_Stat_870: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Stat); return true;
        case SYM_GEN_StackChangeType_871: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_StackChangeType); return true;
        case SYM_GEN_SignalConnection_877: out = gd::GdVal::from_cls(&META_Gd__gd_core_items__Item__INNER__SignalConnection); return true;
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
bool Gd__gd_core_items__Item::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
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
        case SYM_GEN_crafted_instance_902: this->f_crafted_instance = val; return true;
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
bool Gd__gd_core_items__Item::has_own_method(gd::SymId m) const {
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
bool Gd__gd_core_items__Item::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
bool Gd__gd_core_items__Item::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
gd::GdVal Gd__gd_core_items__Item::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__CoreItem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_hasPreDealDamageEarlyEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_early", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasPreDealDamageLateEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_late", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasDealtDamageEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDealtDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeReceivedEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeReceived", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeLeftEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeLeft", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_getNumTooltipStats(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_getNumStackChangeTypes(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_preset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initPhysicsMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getShadowOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Shop_2579))))) {
        return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_shop_524);
    }
    else {
        return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_525);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initRecipeBook(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initItemLibrary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setSpotlight(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_initTitle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initBuildViewer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initBuildViewerIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initInfoPanelIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initGridStorageIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initBuildViewerIcon_635, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_persistDataInShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTranslatedName(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_getDescription(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_insertParameters(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_wrapInColor = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_154, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(lv_wrapInColor)) : gd::GdVal::from_bool(false)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$dam", 4u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_fixed_2623, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    {
        gd::GdVal _t995 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_extraCds_1584), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
        gd::GdArr* _t996 = (_t995.kind == gd::GdVal::Kind::Arr) ? _t995.arr : nullptr;
        uint32_t _len__t997 = _t996 ? _t996->len : 0u;
        for (uint32_t _t997 = 0; _t997 < _len__t997; ++_t997) {
            gd::GdVal lv_i = _t996->data[_t997];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })(), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldownIndex_107, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_280, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_106, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_280, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance2", 7u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance2Modified_283, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance", 6u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance1Modified_282, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "shopchance", 10u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getShopChance_239, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_114, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStaminaModified_115, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    {
        gd::GdVal _t998 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_params_1479), gd::SYM_size, nullptr, 0));
        gd::GdArr* _t999 = (_t998.kind == gd::GdVal::Kind::Arr) ? _t998.arr : nullptr;
        uint32_t _len__t1000 = _t999 ? _t999->len : 0u;
        for (uint32_t _t1000 = 0; _t1000 < _len__t1000; ++_t1000) {
            gd::GdVal lv_i = _t999->data[_t1000];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p", 1u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))))), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    {
        gd::GdVal _t1001 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_sortedParamNames_1615));
        gd::GdArr* _t1002 = (_t1001.kind == gd::GdVal::Kind::Arr) ? _t1001.arr : nullptr;
        uint32_t _len__t1003 = _t1002 ? _t1002->len : 0u;
        for (uint32_t _t1003 = 0; _t1003 < _len__t1003; ++_t1003) {
            gd::GdVal lv_paramName = _t1002->data[_t1003];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_", 2u)), lv_paramName), ([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    if (gd::gd_truth(lv_wrapInColor)) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$block", 6u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0))), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_fixed_2623, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_insertParameter(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_getModeDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_text = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_colors = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_center = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    lv_center = gd::gd_coerce_bool(lv_center);
    gd::GdVal lv_wrapInColor = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(true));
    lv_wrapInColor = gd::gd_coerce_bool(lv_wrapInColor);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getFlavorText(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getFlavorText_646, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_disablePicking(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_enablePicking(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_enableTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_disableTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_disableFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_focus)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseFocus_703, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_enableFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setEditMode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_active = gd::gd_coerce_bool(lv_active);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setShadowAlpha(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_alpha = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_alpha = gd::gd_coerce_float(lv_alpha);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTopLeftGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getBottomRightGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getBottomCenter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        return this->f_inventory;
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_wasAddedToInventory(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToInventory_2626)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_Hotswap_2627))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_wasBought(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Item::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2599))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_Socketed_2628))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_SocketHotswap_2629))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_wasHotSwap(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_Hotswap_2627)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_SocketHotswap_2629))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_removeFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playAffectedPlacedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newItemIsAffected = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_sum = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1004 = gd::gd_iter_seq(gd_ctx.arena, lv_newItemIsAffected);
        gd::GdArr* _t1005 = (_t1004.kind == gd::GdVal::Kind::Arr) ? _t1004.arr : nullptr;
        uint32_t _len__t1006 = _t1005 ? _t1005->len : 0u;
        for (uint32_t _t1006 = 0; _t1006 < _len__t1006; ++_t1006) {
            gd::GdVal lv_color = _t1005->data[_t1006];
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
gd::GdVal Gd__gd_core_items__Item::fn_clearCanAffectVisuals(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_liesInStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerStorageBox_2580)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_dragged)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_pushToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetPos = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_addToStorageBox(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_removeFromStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killMovebackTween_727, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStorageLeft_669, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onStorageLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isInGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getGridStorageProxy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onAddedToGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onRemovedFromGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_makeGrabbable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_extended = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_extended = gd::gd_coerce_bool(lv_extended);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_moveToFreeSpaceInStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetPos = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_addImpulse = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_speed = (_argc > 2) ? _args[2] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_secondCheck = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_tweenBouncyness = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_checkIfOutofStorageBounds(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkIfOutofStorageBounds2", 26u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_callNextFrame_1702, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_checkIfOutofStorageBounds2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkIfOutofStorageBounds3", 26u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_callNextFrame_1702, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_checkIfOutofStorageBounds3(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_findFreeSpace(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_startPos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_unclip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onAddedToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn__process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn__integrate_forces(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_state, SYM_GEN_get_contact_count_2630, nullptr, 0), gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_updateShadow(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_lerpAngle_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_interpolationPoint = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_from = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_to = (_argc > 2) ? _args[2] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateInsideRotationNode_686, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_updateInsideRotationNode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_insideRotationNode, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_spawnRotationSparks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotateRight = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_highlight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_unhighlight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_743, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setBright(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_resetBright(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getHoverPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
        return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_527);
    }
    else {
        return gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canGainFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_gainFocus(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_respondToHover(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canShowBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_canShowSubBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_showBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(5LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(150LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getRecipeDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_descriptor;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_hideBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_buildIntoRecipesTooltip, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_loseFocus(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_respondToHoverEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_activateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1007 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t1008 = (_t1007.kind == gd::GdVal::Kind::Arr) ? _t1007.arr : nullptr;
        uint32_t _len__t1009 = _t1008 ? _t1008->len : 0u;
        for (uint32_t _t1009 = 0; _t1009 < _len__t1009; ++_t1009) {
            gd::GdVal lv_specificParticles = _t1008->data[_t1009];
            (void)gd::call_method(gd_ctx, lv_specificParticles, SYM_GEN_activate_152, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_deactivateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1010 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t1011 = (_t1010.kind == gd::GdVal::Kind::Arr) ? _t1010.arr : nullptr;
        uint32_t _len__t1012 = _t1011 ? _t1011->len : 0u;
        for (uint32_t _t1012 = 0; _t1012 < _len__t1012; ++_t1012) {
            gd::GdVal lv_specificParticles = _t1011->data[_t1012];
            (void)gd::call_method(gd_ctx, lv_specificParticles, SYM_GEN_deactivate_2633, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_updateTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_queueTooltipUpdate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_clearTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hideBuildIntoRecipesTooltip_702, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearCanAffectVisuals_664, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_mouseEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_hover(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_mouseExited(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_hoverEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isHovered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_hovered) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_dragged)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getScaleProp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_hasSquishySprite)) {
        return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "baseScale", 9u));
    }
    else {
        return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "scale", 5u));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setSpriteScale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newScale = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasSquishySprite)) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_pickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_866), SYM_GEN_Grabbed_2634));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onDraggedWithParentStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_parentItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_719, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_finishMoveback(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canSnap(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::call_method(gd_ctx, this->f_draggedInsideItems, gd::SYM_empty, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_draggingParent, gd::GdVal::null())))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_result = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_drop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_showClickArea(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_cancelDrag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_emptyTweenCallback(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_killMovebackTween(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showClickArea_724, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setSpriteGlobalPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_dropIntoInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hotswap = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_finishInsideItemsRotation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_pushDraggedItemsToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1013 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t1014 = (_t1013.kind == gd::GdVal::Kind::Arr) ? _t1013.arr : nullptr;
        uint32_t _len__t1015 = _t1014 ? _t1014->len : 0u;
        for (uint32_t _t1015 = 0; _t1015 < _len__t1015; ++_t1015) {
            gd::GdVal lv_item = _t1014->data[_t1015];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_pushToStorage_666, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_481, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_733, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_reparentItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1016 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t1017 = (_t1016.kind == gd::GdVal::Kind::Arr) ? _t1016.arr : nullptr;
        uint32_t _len__t1018 = _t1017 ? _t1017->len : 0u;
        for (uint32_t _t1018 = 0; _t1018 < _len__t1018; ++_t1018) {
            gd::GdVal lv_item = _t1017->data[_t1018];
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_481, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_733, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_clearDraggedInsideItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1019 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t1020 = (_t1019.kind == gd::GdVal::Kind::Arr) ? _t1019.arr : nullptr;
        uint32_t _len__t1021 = _t1020 ? _t1020->len : 0u;
        for (uint32_t _t1021 = 0; _t1021 < _len__t1021; ++_t1021) {
            gd::GdVal lv_item = _t1020->data[_t1021];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_onDraggedWithParentEnd_720, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_showSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_hideSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canBeSold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerStorageBox_2580))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Socket_2590))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isPickingPossible(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canBePicked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(this->f_focus) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isPickingPossible_738, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1384), this->f_dropFrame)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canBeDraggedWithBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canBeDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_dragged) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1384), this->f_pickupFrame)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn__input(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_resetSprite(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_combatToShop(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_shopEntered(const gd::GdVal* _args, int _argc) {
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
        gd::GdVal _t1022 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffPowers);
        gd::GdArr* _t1023 = (_t1022.kind == gd::GdVal::Kind::Arr) ? _t1022.arr : nullptr;
        uint32_t _len__t1024 = _t1023 ? _t1023->len : 0u;
        for (uint32_t _t1024 = 0; _t1024 < _len__t1024; ++_t1024) {
            gd::GdVal lv_buff = _t1023->data[_t1024];
            { gd::GdVal _t1025 = this->f_buffPowers; gd::GdVal _t1026 = lv_buff; gd::set_index(gd_ctx, _t1025, _t1026, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t1027 = this->f_buffAmplificationChances; gd::GdVal _t1028 = lv_buff; gd::set_index(gd_ctx, _t1027, _t1028, gd::GdVal::from_float(0.0)); }
        }
    }
    this->f_critChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critSeverity = gd::gd_coerce_float(Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_BASE_CRIT_SEVERITY_0));
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
        gd::GdVal _t1029 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t1030 = (_t1029.kind == gd::GdVal::Kind::Arr) ? _t1029.arr : nullptr;
        uint32_t _len__t1031 = _t1030 ? _t1030->len : 0u;
        for (uint32_t _t1031 = 0; _t1031 < _len__t1031; ++_t1031) {
            gd::GdVal lv_gem = _t1030->data[_t1031];
            (void)([&]() { gd::GdVal _ca[] = {lv_craft}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN_shopEntered_745, _ca, 1); })();
        }
    }
    if (gd::gd_truth(lv_craft)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addToCraftingQueue_749, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onShopEntered_746, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_startFusing_inShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_COG_604)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFusing_752, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getCraftingPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isGem_86, nullptr, 0))) {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_Gem_2635);
    }
    {
        gd::GdVal _t1032 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
        gd::GdArr* _t1033 = (_t1032.kind == gd::GdVal::Kind::Arr) ? _t1032.arr : nullptr;
        uint32_t _len__t1034 = _t1033 ? _t1033->len : 0u;
        for (uint32_t _t1034 = 0; _t1034 < _len__t1034; ++_t1034) {
            gd::GdVal lv_bonded = _t1033->data[_t1034];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_bonded, SYM_GEN_isGem_86, nullptr, 0))) {
                return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_Mixed_2636);
            }
        }
    }
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_NonGem_2637);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_addToCraftingQueue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_combatToTitle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_253, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_650, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_curRecipe) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2638, _ca, 1); })(), gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_startFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delay = (_argc > 0) ? _args[0] : (Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_603));
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_readyToFuse_751, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fuse", 4u)), lv_delay}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_callDelayed_1420, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disablePicking_647, nullptr, 0);
        {
            gd::GdVal _t1035 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
            gd::GdArr* _t1036 = (_t1035.kind == gd::GdVal::Kind::Arr) ? _t1035.arr : nullptr;
            uint32_t _len__t1037 = _t1036 ? _t1036->len : 0u;
            for (uint32_t _t1037 = 0; _t1037 < _len__t1037; ++_t1037) {
                gd::GdVal lv_bonded = _t1036->data[_t1037];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_curRecipe, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_bonded}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2639, _ca, 1); })()))))))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bonded, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "disablePicking", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
                    gd::set_prop(gd_ctx, lv_bonded, SYM_GEN_willBeConsumed_608, gd::GdVal::from_bool(true));
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_readyToTransform(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_giveGold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTranslatedTypeName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedTypeName_755, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTypeDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TYPE_", 5u)), gd::get_index(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), gd::SYM_keys, nullptr, 0), lv_type)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_DESCR", 6u)))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTranslatedRarity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_238, nullptr, 0)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Item::call_static_fn(gd_ctx, SYM_GEN_getRarityName_758, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_getRarityName(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__rarity = gd::gd_coerce_int(lv__rarity);
    return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_logCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getCombatDisplayAccuracy(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_getDisplayCritChance(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_getSalesMultiplier(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_float(1.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_prepareDiscard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_popIn(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_withParticles = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_withParticles = gd::gd_coerce_bool(lv_withParticles);
    gd::GdVal lv_speed = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_jump = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_disappear(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_appearInLibrary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_createParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_scene = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_baseScale = (_argc > 1) ? _args[1] : (gd::GdVal::from_vec2(1.0, 1.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_deactivateParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_makeRigidBody(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_dropImpulse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_direction = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_tweenBouncyness = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_makeNonRigidBody(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_rollShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_shopChance = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_shopChance_1587));
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn__physics_process(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_playActivationAnimation_Scale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxScale = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playActivationAnimation_Jump(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_height = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(1.0));
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playActivationAnimation_JumpSquash(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1621));
    gd::GdVal lv_consume = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_consume = gd::gd_coerce_bool(lv_consume);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_743, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Jump_2608))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_SquishyJump_2640))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.1)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_777, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_VerySquishyJump_2641))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.2)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_777, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Slash_2642))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Stab_2643))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_ReverseStab_2644))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Bonk_2645))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_ReverseBonk_2646))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Sweep_2647))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Block_2564))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL), gd::GdVal::from_float(1.3)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Chop_2648))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Wave_2649))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Throw_2609))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Scale_2650))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Scale_775, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Squish_2651))))) {
        if (gd::gd_truth(this->f_hasSquishySprite)) {
        }
        else {
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Potion_2652))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Hiss_2653))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Spin_2654))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Tackle_2655))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_DoubleSlash_2656))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Struggle_2657))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Shoot_2658))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Flash_2659))))) {
    }
    if (gd::gd_truth(lv_consume)) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(6LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playDropSound_151, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_clearSpriteMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_giveProgressMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTextureSize(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_scaleToFit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxSize = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getSpriteOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getGlobalCenter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTextureSize_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_scaleToFit_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxSize = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getSpriteOffset_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newTex = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initSpriteMaterial_790, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_updateShadowTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_initSpriteMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_updateShaderRotation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_allowCancelShaderTween(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_showCooldownSmooth(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_showCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_progress = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_createAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hit = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_hit = gd::gd_coerce_bool(lv_hit);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1599))))) {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_hasInventoryDuration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1487, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_reveal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setRevealed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reveal_798, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isCrafted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_crafted_instance, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(gd::gd_eq(this->f_crafted_instance, gd::GdVal::from_int(1LL)));
    }
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isCraftedItem_1624, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isMovingBack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn__notification(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_what = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_what = gd::gd_coerce_int(lv_what);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getAllInInventoryOfType(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_countAllInInventoryOfType(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_isTypeInInventory(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_isRecipeFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2638, _ca, 1); })(), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canStartNewRecipe(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBaseItem_260, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isAvailableForCrafting_495, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getRecipes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_checkClassAvailability = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_recipes = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1038 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_recipes_2660));
        gd::GdArr* _t1039 = (_t1038.kind == gd::GdVal::Kind::Arr) ? _t1038.arr : nullptr;
        uint32_t _len__t1040 = _t1039 ? _t1039->len : 0u;
        for (uint32_t _t1040 = 0; _t1040 < _len__t1040; ++_t1040) {
            gd::GdVal lv_recipe = _t1039->data[_t1040];
            (void)([&]() { gd::GdVal _ca[] = {lv_recipe}; return gd::call_method(gd_ctx, lv_recipes, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return lv_recipes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_breakBondVisual(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_bondIndex = ([&]() { gd::GdVal _ca[] = {lv_toItem}; return gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_find, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_bondIndex, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_removeBondedBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_removeBondedIngredient(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_removeAllIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_837, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_considerAsBond(const gd::GdVal* _args, int _argc) {
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
            gd::GdVal _t1041 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRecipes_808, nullptr, 0));
            gd::GdArr* _t1042 = (_t1041.kind == gd::GdVal::Kind::Arr) ? _t1041.arr : nullptr;
            uint32_t _len__t1043 = _t1042 ? _t1042->len : 0u;
            for (uint32_t _t1043 = 0; _t1043 < _len__t1043; ++_t1043) {
                gd::GdVal lv_r = _t1042->data[_t1043];
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
gd::GdVal Gd__gd_core_items__Item::fn_addBondedIngredient(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_addToBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_816, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playBondAnimation(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_playBondFailedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isCatalystBond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bondedItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_curRecipe, gd::GdVal::null())))) {
        return gd::GdVal::from_bool(false);
    }
    return ([&]() { gd::GdVal _ca[] = {lv_bondedItem}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2639, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_locked;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canLockBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canBeLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setLocked(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_unlockCombining(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playAni = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_playAni = gd::gd_coerce_bool(lv_playAni);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_lockCombining(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_showLabel = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_showLockLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getLockPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setBoundAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__bound = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__bound = gd::gd_coerce_bool(lv__bound);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canPreviewFusions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getCraftingPreviewPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_previewFusions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_previewRecipeIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_previewFusionToItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hoveredIngredient = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_hasShopItemCraftCandidates(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_typeInIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_candidate = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_ingredients = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1044 = gd::gd_iter_seq(gd_ctx.arena, lv_ingredients);
        gd::GdArr* _t1045 = (_t1044.kind == gd::GdVal::Kind::Arr) ? _t1044.arr : nullptr;
        uint32_t _len__t1046 = _t1045 ? _t1045->len : 0u;
        for (uint32_t _t1046 = 0; _t1046 < _len__t1046; ++_t1046) {
            gd::GdVal lv_ingredient = _t1045->data[_t1046];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_ingredient}; return gd::call_method(gd_ctx, lv_candidate, SYM_GEN_hasType_81, _ca, 1); })())) {
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTextEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_textEffect_2276);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getFusionItemName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_fusedItem_2664), SYM_GEN_getTranslatedName_641, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_showProgressLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onCraftingLabelReturned(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_createBondVisual(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bondNeighbor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_updateBondVisuals(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_fuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onFusingAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onFusingAsCatalystFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearSpriteMaterial_779, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_createCraftedShockwave(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fusedItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_finishFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_allowGeneratingFusionItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_catalystFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_validBonds = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onCraftedFrom(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_ingredients = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playCraftedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_originPosition = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onRestoreSnapshot(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_719, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Normal_2541);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Item(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Item>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Item = {CLS_Gd__gd_core_items__Item, "Item", "res://gd_core_items/Item.gd", &META_Gd__gd_core__CoreItem, true, _alloc_Gd__gd_core_items__Item, &Gd__gd_core_items__Item::get_static_prop_fn, &Gd__gd_core_items__Item::call_static_fn};

void Gd__gd_core__Bow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_affectedWeapon = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Bow::meta() const { return &META_Gd__gd_core__Bow; }
gd::GdVal Gd__gd_core__Bow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Bow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Bow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedWeapon_948: out = this->f_affectedWeapon; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Bow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedWeapon_948: this->f_affectedWeapon = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Bow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Bow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Bow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Bow::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bow::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedWeapon = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_430, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_affectedWeapon, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_affectedWeapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bow::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_combatEnd_133, nullptr, 0, _out); return _out; })();
    this->f_affectedWeapon = gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Bow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Bow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Bow = {CLS_Gd__gd_core__Bow, "Bow", "res://gd_core/Bow.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Bow, &Gd__gd_core__Bow::get_static_prop_fn, &Gd__gd_core__Bow::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_EventType[] = {{"Activation", 0LL}, {"DealDamage", 1LL}, {"CriticalDamage", 2LL}, {"MissedAttack", 3LL}, {"TakeDamage", 4LL}, {"LoseHealth", 5LL}, {"AttackSpeed", 6LL}, {"InvulnerableStart", 7LL}, {"InvulnerableEnd", 8LL}, {"Stun", 9LL}, {"StunResisted", 10LL}, {"CriticalResisted", 11LL}, {"Health", 12LL}, {"Stamina", 13LL}, {"DrainStamina", 14LL}, {"OutofStamina", 15LL}, {"DamageBuff", 16LL}, {"DamReduction", 17LL}, {"DamIncrease", 18LL}, {"TemporaryMaxHealth", 19LL}, {"TemporaryMaxStamina", 20LL}, {"BattleRageStart", 21LL}, {"BattleRageEnd", 22LL}, {"Reincarnate", 23LL}, {"CooldownAdvance", 24LL}, {"Unhealing", 98LL}, {"Fatigue", 99LL}, {"Block", 100LL}, {"Lucky", 101LL}, {"Regeneration", 102LL}, {"Vampirism", 103LL}, {"Spikes", 104LL}, {"Mana", 105LL}, {"Empower", 106LL}, {"Heat", 107LL}, {"Poison", 108LL}, {"Blind", 109LL}, {"Cold", 110LL}, {"Win", 111LL}, {"Loss", 112LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_EventType = {"EventType", _ekv_Gd__gd_core__CoreConst_EventType, 40u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_ItemMetrics[] = {{"Damage", 0LL}, {"Heal", 1LL}, {"Overheal", 2LL}, {"Misses", 3LL}, {"Activations", 4LL}, {"DamageBlocked", 5LL}, {"MaxHealth", 6LL}, {"OutOfStamina", 7LL}, {"Stamina", 8LL}, {"Block", 9LL}, {"Lucky", 10LL}, {"Regeneration", 11LL}, {"Vampirism", 12LL}, {"Spikes", 13LL}, {"Mana", 14LL}, {"Empower", 15LL}, {"Heat", 16LL}, {"Poison", 17LL}, {"Blind", 18LL}, {"Cold", 19LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_ItemMetrics = {"ItemMetrics", _ekv_Gd__gd_core__CoreConst_ItemMetrics, 20u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_CharID[] = {{"PLAYER", 0LL}, {"OPPONENT", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_CharID = {"CharID", _ekv_Gd__gd_core__CoreConst_CharID, 2u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_StaminaResult[] = {{"Sufficient", 0LL}, {"Insufficient", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_StaminaResult = {"StaminaResult", _ekv_Gd__gd_core__CoreConst_StaminaResult, 2u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_ItemStat[] = {{"MinDamage", 0LL}, {"MaxDamage", 1LL}, {"StaminaCost", 2LL}, {"Speed", 3LL}, {"BaseCooldown", 4LL}, {"Accuracy", 5LL}, {"CritChance", 6LL}, {"Chance", 7LL}, {"Chance2", 8LL}, {"Cooldown", 9LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_ItemStat = {"ItemStat", _ekv_Gd__gd_core__CoreConst_ItemStat, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Rarity[] = {{"Common", 0LL}, {"Rare", 1LL}, {"Epic", 2LL}, {"Legendary", 3LL}, {"Godly", 4LL}, {"Unique", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Rarity = {"Rarity", _ekv_Gd__gd_core__CoreConst_Rarity, 6u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_StuffedClasses[] = {{"Undefined", -1LL}, {"None", 0LL}, {"Ranger", 1LL}, {"Reaper", 2LL}, {"Berserker", 4LL}, {"Pyromancer", 8LL}, {"Mage", 16LL}, {"Adventurer", 32LL}, {"Engineer", 64LL}, {"Neutral", 127LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_StuffedClasses = {"StuffedClasses", _ekv_Gd__gd_core__CoreConst_StuffedClasses, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Owner[] = {{"Shop", 0LL}, {"PlayerInventory", 1LL}, {"PlayerStorageBox", 2LL}, {"Opponent", 3LL}, {"Title", 4LL}, {"RecipeBook", 5LL}, {"Tooltip", 6LL}, {"Socket", 7LL}, {"ItemLibrary", 8LL}, {"InfoPanelIcon", 9LL}, {"BuildViewer", 10LL}, {"BuildViewerIcon", 11LL}, {"GridStorage", 12LL}, {"Undefined", 13LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Owner = {"Owner", _ekv_Gd__gd_core__CoreConst_Owner, 14u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_GameMode[] = {{"Ranked", 0LL}, {"Unranked", 1LL}, {"Lobbies", 2LL}, {"Unselected", 3LL}, {"History", 4LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_GameMode = {"GameMode", _ekv_Gd__gd_core__CoreConst_GameMode, 5u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Affected[] = {{"Primary", 0LL}, {"Secondary", 1LL}, {"Tertiary", 2LL}, {"Lightning", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Affected = {"Affected", _ekv_Gd__gd_core__CoreConst_Affected, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Stack[] = {{"None", 0LL}, {"Block", 1LL}, {"Lucky", 2LL}, {"Regeneration", 4LL}, {"Vampirism", 8LL}, {"Spikes", 16LL}, {"Mana", 32LL}, {"Empower", 64LL}, {"Heat", 128LL}, {"Poison", 256LL}, {"Blind", 512LL}, {"Cold", 1024LL}, {"Buff", 254LL}, {"Debuff", 1792LL}, {"BuffNoLuck", 252LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Stack = {"Stack", _ekv_Gd__gd_core__CoreConst_Stack, 15u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Tag[] = {{"None", 0LL}, {"Lifesteal", 1LL}, {"Stone", 2LL}, {"Scroll", 8LL}, {"Dragon", 16LL}, {"Staff", 32LL}, {"BattleRage", 64LL}, {"Singular", 128LL}, {"Transient", 256LL}, {"Bow", 512LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Tag = {"Tag", _ekv_Gd__gd_core__CoreConst_Tag, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Priority[] = {{"Lowest", -10000LL}, {"Low", -1000LL}, {"Normal", 0LL}, {"High", 1000LL}, {"Highest", 10000LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Priority = {"Priority", _ekv_Gd__gd_core__CoreConst_Priority, 5u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_StackChangeType[] = {{"Added_Player", 0LL}, {"Added_Opponent", 1LL}, {"Removed_Player", 2LL}, {"Removed_Opponent", 3LL}, {"Used_Player", 4LL}, {"Used_Opponent", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_StackChangeType = {"StackChangeType", _ekv_Gd__gd_core__CoreConst_StackChangeType, 6u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_StatModified[] = {{"No", 0LL}, {"Positive", 1LL}, {"Negative", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_StatModified = {"StatModified", _ekv_Gd__gd_core__CoreConst_StatModified, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_FaceDirection[] = {{"UP", 0LL}, {"RIGHT", 1LL}, {"DOWN", 2LL}, {"LEFT", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_FaceDirection = {"FaceDirection", _ekv_Gd__gd_core__CoreConst_FaceDirection, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Classes[] = {{"Ranger", 0LL}, {"Reaper", 1LL}, {"Berserker", 2LL}, {"Pyromancer", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Classes = {"Classes", _ekv_Gd__gd_core__CoreConst_Classes, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Classes_Full[] = {{"Ranger", 0LL}, {"Reaper", 1LL}, {"Berserker", 2LL}, {"Pyromancer", 3LL}, {"Mage", 4LL}, {"Adventurer", 5LL}, {"Engineer", 6LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Classes_Full = {"Classes_Full", _ekv_Gd__gd_core__CoreConst_Classes_Full, 7u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreConst_Type[] = {{"Bag", 0LL}, {"Consumable", 1LL}, {"Food", 2LL}, {"Pet", 3LL}, {"Weapon", 4LL}, {"Shield", 5LL}, {"Armor", 6LL}, {"Gloves", 7LL}, {"Shoes", 8LL}, {"Helmet", 9LL}, {"Accessory", 10LL}, {"Potion", 11LL}, {"Card", 12LL}, {"Gem", 13LL}, {"Scroll", 14LL}, {"Book", 15LL}, {"Skill", 16LL}, {"ChessPiece", 17LL}, {"Spell", 18LL}, {"Melee", 19LL}, {"Ranged", 20LL}, {"Effect", 21LL}, {"Holy", 22LL}, {"Magic", 23LL}, {"Vampiric", 24LL}, {"Dark", 25LL}, {"Nature", 26LL}, {"Fire", 27LL}, {"Ice", 28LL}, {"Musical", 29LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreConst_Type = {"Type", _ekv_Gd__gd_core__CoreConst_Type, 30u};
void Gd__gd_core__CoreConst::init_fields(gd::BattleCtx& gd_ctx) {
}
const gd::GdClassMeta* Gd__gd_core__CoreConst::meta() const { return &META_Gd__gd_core__CoreConst; }
gd::GdVal Gd__gd_core__CoreConst::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_EventType_1366: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_EventType);
        case SYM_GEN_ItemMetrics_1367: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_ItemMetrics);
        case SYM_GEN_CharID_1368: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_CharID);
        case SYM_GEN_StaminaResult_1280: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StaminaResult);
        case SYM_GEN_ItemStat_1369: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_ItemStat);
        case SYM_GEN_Rarity_862: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Rarity);
        case SYM_GEN_StuffedClasses_1370: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StuffedClasses);
        case SYM_GEN_Owner_854: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Owner);
        case SYM_GEN_GameMode_1371: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_GameMode);
        case SYM_GEN_Affected_867: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Affected);
        case SYM_GEN_Stack_859: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Stack);
        case SYM_GEN_Tag_858: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Tag);
        case SYM_GEN_Priority_856: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Priority);
        case SYM_GEN_StackChangeType_871: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StackChangeType);
        case SYM_GEN_StatModified_864: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StatModified);
        case SYM_GEN_FaceDirection_863: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_FaceDirection);
        case SYM_GEN_Classes_1372: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Classes);
        case SYM_GEN_Classes_Full_1373: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Classes_Full);
        case SYM_GEN_Type_855: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Type);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreConst::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreConst::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_EventType_1366: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_EventType); return true;
        case SYM_GEN_ItemMetrics_1367: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_ItemMetrics); return true;
        case SYM_GEN_CharID_1368: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_CharID); return true;
        case SYM_GEN_StaminaResult_1280: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StaminaResult); return true;
        case SYM_GEN_ItemStat_1369: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_ItemStat); return true;
        case SYM_GEN_Rarity_862: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Rarity); return true;
        case SYM_GEN_StuffedClasses_1370: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StuffedClasses); return true;
        case SYM_GEN_Owner_854: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Owner); return true;
        case SYM_GEN_GameMode_1371: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_GameMode); return true;
        case SYM_GEN_Affected_867: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Affected); return true;
        case SYM_GEN_Stack_859: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Stack); return true;
        case SYM_GEN_Tag_858: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Tag); return true;
        case SYM_GEN_Priority_856: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Priority); return true;
        case SYM_GEN_StackChangeType_871: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StackChangeType); return true;
        case SYM_GEN_StatModified_864: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StatModified); return true;
        case SYM_GEN_FaceDirection_863: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_FaceDirection); return true;
        case SYM_GEN_Classes_1372: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Classes); return true;
        case SYM_GEN_Classes_Full_1373: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Classes_Full); return true;
        case SYM_GEN_Type_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Type); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreConst::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return false;
}
bool Gd__gd_core__CoreConst::has_own_method(gd::SymId m) const {
    return false;
}
bool Gd__gd_core__CoreConst::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_truth_1360: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_getStacks_1022: out = sf_getStacks(gd_ctx, args, argc); return true;
        case SYM_GEN_getBuffs_1361: out = sf_getBuffs(gd_ctx, args, argc); return true;
        case SYM_GEN_getDebuffs_1362: out = sf_getDebuffs(gd_ctx, args, argc); return true;
        case SYM_GEN_isBuff_1006: out = sf_isBuff(gd_ctx, args, argc); return true;
        case SYM_GEN_isDebuff_1363: out = sf_isDebuff(gd_ctx, args, argc); return true;
        case SYM_GEN_isStack_1364: out = sf_isStack(gd_ctx, args, argc); return true;
        case SYM_GEN_numStackTypes_1365: out = sf_numStackTypes(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreConst::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_truth_1360: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_getStacks_1022: out = sf_getStacks(gd_ctx, args, argc); return true;
        case SYM_GEN_getBuffs_1361: out = sf_getBuffs(gd_ctx, args, argc); return true;
        case SYM_GEN_getDebuffs_1362: out = sf_getDebuffs(gd_ctx, args, argc); return true;
        case SYM_GEN_isBuff_1006: out = sf_isBuff(gd_ctx, args, argc); return true;
        case SYM_GEN_isDebuff_1363: out = sf_isDebuff(gd_ctx, args, argc); return true;
        case SYM_GEN_isStack_1364: out = sf_isStack(gd_ctx, args, argc); return true;
        case SYM_GEN_numStackTypes_1365: out = sf_numStackTypes(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreConst::sf_truth(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_v = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_v)) {
        return gd::GdVal::from_bool(true);
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_getStacks(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Block_2564)})), ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreConst::call_static_fn(gd_ctx, SYM_GEN_getBuffs_1361, nullptr, 0, _out); return _out; })()), ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreConst::call_static_fn(gd_ctx, SYM_GEN_getDebuffs_1362, nullptr, 0, _out); return _out; })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_getBuffs(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570), gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Heat_2573), gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_getDebuffs(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_isBuff(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Block_2564)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Heat_2573))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_isDebuff(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Poison_2567)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Cold_2574))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_isStack(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Block_2564)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1366), SYM_GEN_Cold_2574))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_numStackTypes(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreConst::call_static_fn(gd_ctx, SYM_GEN_getStacks_1022, nullptr, 0, _out); return _out; })(), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreConst(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreConst>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreConst = {CLS_Gd__gd_core__CoreConst, "CoreConst", "res://gd_core/CoreConst.gd", nullptr, false, _alloc_Gd__gd_core__CoreConst, &Gd__gd_core__CoreConst::get_static_prop_fn, &Gd__gd_core__CoreConst::call_static_fn};

void Gd__gd_core__CoreUtil::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_rng = gd::GdVal::null();
    this->f__ctx = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreUtil::meta() const { return &META_Gd__gd_core__CoreUtil; }
gd::GdVal Gd__gd_core__CoreUtil::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_DictSorter_1713: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil__INNER__DictSorter);
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
        case SYM_GEN_rng_1377: out = this->f_rng; return true;
        case SYM_GEN__ctx_1325: out = this->f__ctx; return true;
        case SYM_GEN_DictSorter_1713: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil__INNER__DictSorter); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rng_1377: this->f_rng = val; return true;
        case SYM_GEN__ctx_1325: this->f__ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_roll_1638: return true;
        case SYM_GEN_flip_1639: return true;
        case SYM_GEN_flipPercent_1640: return true;
        case SYM_GEN_flipRound_1641: return true;
        case SYM_GEN_flipWeighted_1642: return true;
        case SYM_GEN_pickRandomElement_1650: return true;
        case SYM_GEN_getArrayElement_1700: return true;
        case SYM_GEN_callNextFrame_1702: return true;
        case SYM_GEN_callDelayed_1420: return true;
        case SYM_GEN_callDelayed_process_1703: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_truth_1360: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_tile_data_1692: out = sf_vec2_tile_data(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_less_yx_1693: out = sf_vec2_less_yx(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAdd_1694: out = sf_dictAdd(gd_ctx, args, argc); return true;
        case SYM_GEN_dictSub_1695: out = sf_dictSub(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAddDict_1696: out = sf_dictAddDict(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAppend_1697: out = sf_dictAppend(gd_ctx, args, argc); return true;
        case SYM_GEN_dictErase_1698: out = sf_dictErase(gd_ctx, args, argc); return true;
        case SYM_GEN_sortDict_1699: out = sf_sortDict(gd_ctx, args, argc); return true;
        case SYM_GEN_roll_1638: out = fn_roll(args, argc); return true;
        case SYM_GEN_flip_1639: out = fn_flip(args, argc); return true;
        case SYM_GEN_flipPercent_1640: out = fn_flipPercent(args, argc); return true;
        case SYM_GEN_flipRound_1641: out = fn_flipRound(args, argc); return true;
        case SYM_GEN_flipWeighted_1642: out = fn_flipWeighted(args, argc); return true;
        case SYM_GEN_pickRandomElement_1650: out = fn_pickRandomElement(args, argc); return true;
        case SYM_GEN_getArrayElement_1700: out = fn_getArrayElement(args, argc); return true;
        case SYM_GEN_changeTimer_1701: out = sf_changeTimer(gd_ctx, args, argc); return true;
        case SYM_GEN_callNextFrame_1702: out = fn_callNextFrame(args, argc); return true;
        case SYM_GEN_callDelayed_1420: out = fn_callDelayed(args, argc); return true;
        case SYM_GEN_callDelayed_process_1703: out = fn_callDelayed_process(args, argc); return true;
        case SYM_GEN_arrayAsIndexDict_1704: out = sf_arrayAsIndexDict(gd_ctx, args, argc); return true;
        case SYM_GEN_invertDictionary_1705: out = sf_invertDictionary(gd_ctx, args, argc); return true;
        case SYM_GEN_filterDuplicates_1706: out = sf_filterDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_countDuplicates_1707: out = sf_countDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_flatten_1708: out = sf_flatten(gd_ctx, args, argc); return true;
        case SYM_GEN_rotDif_1709: out = sf_rotDif(gd_ctx, args, argc); return true;
        case SYM_GEN_isItemDescriptor_1710: out = sf_isItemDescriptor(gd_ctx, args, argc); return true;
        case SYM_GEN_eassert_1711: out = sf_eassert(gd_ctx, args, argc); return true;
        case SYM_GEN_eprint_1712: out = sf_eprint(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_truth_1360: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_tile_data_1692: out = sf_vec2_tile_data(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_less_yx_1693: out = sf_vec2_less_yx(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAdd_1694: out = sf_dictAdd(gd_ctx, args, argc); return true;
        case SYM_GEN_dictSub_1695: out = sf_dictSub(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAddDict_1696: out = sf_dictAddDict(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAppend_1697: out = sf_dictAppend(gd_ctx, args, argc); return true;
        case SYM_GEN_dictErase_1698: out = sf_dictErase(gd_ctx, args, argc); return true;
        case SYM_GEN_sortDict_1699: out = sf_sortDict(gd_ctx, args, argc); return true;
        case SYM_GEN_changeTimer_1701: out = sf_changeTimer(gd_ctx, args, argc); return true;
        case SYM_GEN_arrayAsIndexDict_1704: out = sf_arrayAsIndexDict(gd_ctx, args, argc); return true;
        case SYM_GEN_invertDictionary_1705: out = sf_invertDictionary(gd_ctx, args, argc); return true;
        case SYM_GEN_filterDuplicates_1706: out = sf_filterDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_countDuplicates_1707: out = sf_countDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_flatten_1708: out = sf_flatten(gd_ctx, args, argc); return true;
        case SYM_GEN_rotDif_1709: out = sf_rotDif(gd_ctx, args, argc); return true;
        case SYM_GEN_isItemDescriptor_1710: out = sf_isItemDescriptor(gd_ctx, args, argc); return true;
        case SYM_GEN_eassert_1711: out = sf_eassert(gd_ctx, args, argc); return true;
        case SYM_GEN_eprint_1712: out = sf_eprint(gd_ctx, args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {lv_v}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1360, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_vec2_tile_data(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_a = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_b = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_a, gd::SYM_x), gd::get_prop(gd_ctx, lv_b, gd::SYM_x))))) {
        return gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_a, gd::SYM_y), gd::get_prop(gd_ctx, lv_b, gd::SYM_y)));
    }
    return gd::GdVal::from_bool(gd::gd_lt(gd::get_prop(gd_ctx, lv_a, gd::SYM_x), gd::get_prop(gd_ctx, lv_b, gd::SYM_x)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_vec2_less_yx(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_a = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_b = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_a, gd::SYM_y), gd::get_prop(gd_ctx, lv_b, gd::SYM_y))))) {
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
    gd::GdVal lv_newVal = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_key, lv_base}; return gd::call_method(gd_ctx, lv_dict, gd::SYM_get, _ca, 2); })(), lv_val);
    { gd::GdVal _t1047 = lv_dict; gd::GdVal _t1048 = lv_key; gd::set_index(gd_ctx, _t1047, _t1048, lv_newVal); }
    return lv_newVal;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictSub(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_val = (_argc > 2) ? _args[2] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_val2 = gd::gd_sub(([&]() { gd::GdVal _ca[] = {lv_key, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_dict, gd::SYM_get, _ca, 2); })(), lv_val);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_val2, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_key}; return gd::call_method(gd_ctx, lv_dict, gd::SYM_erase, _ca, 1); })();
    }
    else {
        { gd::GdVal _t1049 = lv_dict; gd::GdVal _t1050 = lv_key; gd::set_index(gd_ctx, _t1049, _t1050, lv_val2); }
    }
    return lv_val2;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictAddDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_dict2 = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1051 = gd::gd_iter_seq(gd_ctx.arena, lv_dict2);
        gd::GdArr* _t1052 = (_t1051.kind == gd::GdVal::Kind::Arr) ? _t1051.arr : nullptr;
        uint32_t _len__t1053 = _t1052 ? _t1052->len : 0u;
        for (uint32_t _t1053 = 0; _t1053 < _len__t1053; ++_t1053) {
            gd::GdVal lv_key = _t1052->data[_t1053];
            (void)([&]() { gd::GdVal _ca[] = {lv_dict1, lv_key, gd::get_index(gd_ctx, lv_dict2, lv_key)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreUtil::call_static_fn(gd_ctx, SYM_GEN_dictAdd_1694, _ca, 3, _out); return _out; })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictAppend(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 2) ? _args[2] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_key, lv_dict))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_dict, lv_key), gd::SYM_append, _ca, 1); })();
    }
    else {
        { gd::GdVal _t1054 = lv_dict; gd::GdVal _t1055 = lv_key; gd::set_index(gd_ctx, _t1054, _t1055, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_value}))); }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictErase(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_valueToErase = (_argc > 2) ? _args[2] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_key, lv_dict))) {
        gd::GdVal lv_arr = gd::get_index(gd_ctx, lv_dict, lv_key);
        (void)([&]() { gd::GdVal _ca[] = {lv_valueToErase}; return gd::call_method(gd_ctx, lv_arr, gd::SYM_erase, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_arr, gd::SYM_empty, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_key}; return gd::call_method(gd_ctx, lv_dict, gd::SYM_erase, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_sortDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_rng = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_shuffleBeforeSort = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_sorted = gd::call_method(gd_ctx, lv_dict, gd::SYM_keys, nullptr, 0);
    if (gd::gd_truth(lv_shuffleBeforeSort)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_sorted}; return gd::call_method(gd_ctx, lv_rng, gd::SYM_shuffle, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_dict}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil__INNER__DictSorter), gd::SYM_new, _ca, 1); })(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sort", 4u))}; return gd::call_method(gd_ctx, lv_sorted, gd::SYM_sort_custom, _ca, 2); })();
    return lv_sorted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_roll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maximum = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(100.0));
    return ([&]() { gd::GdVal _ca[] = {lv_maximum}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_roll_1638, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(0.5));
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_flip_1639, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipPercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_flipPercent_1640, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipRound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_flipRound_1641, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipWeighted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_weights = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_weights}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_flipWeighted_1642, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_pickRandomElement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_array}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_pickRandomElement_1650, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_getArrayElement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_index = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_index = gd::gd_coerce_int(lv_index);
    gd::GdVal lv_default = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_index, gd::gd_sub(gd::call_method(gd_ctx, lv_array, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)))))) {
        return lv_default;
    }
    else {
        return gd::get_index(gd_ctx, lv_array, lv_index);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_changeTimer(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_timer = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_t = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_t = gd::gd_coerce_float(lv_t);
    gd::GdVal lv_timeLeft = gd::call_method(gd_ctx, lv_timer, SYM_GEN_get_time_left_1684, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_t, lv_timeLeft)}; return gd::call_method(gd_ctx, lv_timer, SYM_GEN_start_1685, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callNextFrame(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_arguments}; return gd::call_method(gd_ctx, this->f__ctx, SYM_GEN_defer_1422, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callDelayed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_delay, lv_binds}; return gd::call_method(gd_ctx, this->f__ctx, SYM_GEN_callDelayed_1420, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callDelayed_process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_delay, lv_binds}; return gd::call_method(gd_ctx, this->f__ctx, SYM_GEN_callDelayed_1420, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_arrayAsIndexDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_invertedDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1056 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, lv_array, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t1057 = (_t1056.kind == gd::GdVal::Kind::Arr) ? _t1056.arr : nullptr;
        uint32_t _len__t1058 = _t1057 ? _t1057->len : 0u;
        for (uint32_t _t1058 = 0; _t1058 < _len__t1058; ++_t1058) {
            gd::GdVal lv_i = _t1057->data[_t1058];
            { gd::GdVal _t1059 = lv_invertedDict; gd::GdVal _t1060 = gd::get_index(gd_ctx, lv_array, lv_i); gd::set_index(gd_ctx, _t1059, _t1060, lv_i); }
        }
    }
    return lv_invertedDict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_invertDictionary(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_invertedDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1061 = gd::gd_iter_seq(gd_ctx.arena, lv_dict);
        gd::GdArr* _t1062 = (_t1061.kind == gd::GdVal::Kind::Arr) ? _t1061.arr : nullptr;
        uint32_t _len__t1063 = _t1062 ? _t1062->len : 0u;
        for (uint32_t _t1063 = 0; _t1063 < _len__t1063; ++_t1063) {
            gd::GdVal lv_key = _t1062->data[_t1063];
            { gd::GdVal _t1064 = lv_invertedDict; gd::GdVal _t1065 = gd::get_index(gd_ctx, lv_dict, lv_key); gd::set_index(gd_ctx, _t1064, _t1065, lv_key); }
        }
    }
    return lv_invertedDict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_filterDuplicates(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_dict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1066 = gd::gd_iter_seq(gd_ctx.arena, lv_arr);
        gd::GdArr* _t1067 = (_t1066.kind == gd::GdVal::Kind::Arr) ? _t1066.arr : nullptr;
        uint32_t _len__t1068 = _t1067 ? _t1067->len : 0u;
        for (uint32_t _t1068 = 0; _t1068 < _len__t1068; ++_t1068) {
            gd::GdVal lv_a = _t1067->data[_t1068];
            { gd::GdVal _t1069 = lv_dict; gd::GdVal _t1070 = lv_a; gd::set_index(gd_ctx, _t1069, _t1070, gd::GdVal::from_bool(true)); }
        }
    }
    return gd::call_method(gd_ctx, lv_dict, gd::SYM_keys, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_countDuplicates(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_before = gd::call_method(gd_ctx, lv_arr, gd::SYM_size, nullptr, 0);
    gd::GdVal lv_filtered = ([&]() { gd::GdVal _ca[] = {lv_arr}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreUtil::call_static_fn(gd_ctx, SYM_GEN_filterDuplicates_1706, _ca, 1, _out); return _out; })();
    return gd::gd_sub(lv_before, gd::call_method(gd_ctx, lv_filtered, gd::SYM_size, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_flatten(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_flattened = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1071 = gd::gd_iter_seq(gd_ctx.arena, lv_arr);
        gd::GdArr* _t1072 = (_t1071.kind == gd::GdVal::Kind::Arr) ? _t1071.arr : nullptr;
        uint32_t _len__t1073 = _t1072 ? _t1072->len : 0u;
        for (uint32_t _t1073 = 0; _t1073 < _len__t1073; ++_t1073) {
            gd::GdVal lv_inner = _t1072->data[_t1073];
            (void)([&]() { gd::GdVal _ca[] = {lv_inner}; return gd::call_method(gd_ctx, lv_flattened, gd::SYM_append_array, _ca, 1); })();
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_object, gd::GdVal::null())))) {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_object, gd::SYM_get_script, nullptr, 0), gd::load_resource(((gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "res://gd_core/CoreItemData.gd", 29u))).kind == gd::GdVal::Kind::Str && (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "res://gd_core/CoreItemData.gd", 29u))).str) ? std::string_view((gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "res://gd_core/CoreItemData.gd", 29u))).str->data, (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "res://gd_core/CoreItemData.gd", 29u))).str->len) : std::string_view(""))));
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
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_arg3, gd::GdVal::null())))) {
            (void)gd::GdVal::null();
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_arg2, gd::GdVal::null())))) {
            (void)gd::GdVal::null();
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_arg1, gd::GdVal::null())))) {
            (void)gd::GdVal::null();
        }
        else {
            (void)gd::GdVal::null();
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreUtil(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreUtil>(&ctx); }
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
        case SYM_GEN_numIngredients_1761: return gd::GdVal::from_float(5.0);
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
        case SYM_GEN_activated_1296: out = this->f_activated; return true;
        case SYM_GEN_affectedWeapon_948: out = this->f_affectedWeapon; return true;
        case SYM_GEN_stacksNeeded_1762: out = this->f_stacksNeeded; return true;
        case SYM_GEN_healthNeeded_1763: out = this->f_healthNeeded; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_numIngredients_1761: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__DjinnLamp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1296: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_affectedWeapon_948: this->f_affectedWeapon = val; return true;
        case SYM_GEN_stacksNeeded_1762: this->f_stacksNeeded = val; return true;
        case SYM_GEN_healthNeeded_1763: this->f_healthNeeded = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DjinnLamp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_checkStacks_1764: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__DjinnLamp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_checkStacks_1764: out = fn_checkStacks(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_affectedWeapon = gd::GdVal::null();
    gd::GdVal lv_affectedItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        this->f_affectedWeapon = gd::get_index(gd_ctx, lv_affectedItems, gd::GdVal::from_int(0LL));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_block_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_healed", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
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
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getBlock_206, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getSpikes_1207, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::gd_sub(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentHealth_1138, nullptr, 0), gd::GdVal::from_int(1LL)), this->f_healthNeeded), gd::gd_coerce_float(this->f_healthNeeded)));
    lv_progress = gd::gd_div(gd_ctx, lv_progress, Gd__gd_core__DjinnLamp::get_static_const_or_enum(gd_ctx, SYM_GEN_numIngredients_1761));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_changeAmount, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_progress, gd::GdVal::from_float(0.9999))))) {
            this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useBlock_209, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_339, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_352, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_healthNeeded, gd::GdVal::from_obj(this), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseHealth_1141, _ca, 3); })();
            gd::GdVal lv_bonusDamage = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusDamage}; return gd::call_method(gd_ctx, this->f_affectedWeapon, SYM_GEN_addBonusDamage_163, _ca, 1); })();
            gd::GdVal lv_dmgBuffEvent = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), this->f_affectedWeapon, lv_bonusDamage, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_playerId_1046), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_DamageBuff_1345, _ca, 5); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_dmgBuffEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numLucky = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0);
    gd::GdVal lv_numSpikes = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getSpikes_1207, nullptr, 0);
    gd::GdVal lv_numMana = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numLucky, lv_numSpikes)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numLucky, lv_numMana)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
        }
    }
    else {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numSpikes, lv_numMana)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_stacksNeeded = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    this->f_healthNeeded = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DjinnLamp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__DjinnLamp>(&ctx); }
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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Hammer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: out = fn_onFusingAsCatalystFinished(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Hammer::fn_onFusingAsCatalystFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_onFusingAsCatalystFinished_843, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_778, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Hammer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Hammer(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Hammer>(&ctx); }
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
        case SYM_GEN_buffsActive_1777: out = this->f_buffsActive; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_damReduction_1778: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__LeatherHelm::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffsActive_1777: this->f_buffsActive = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_damReduction_1778: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LeatherHelm::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1812: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_getBuffDur_1813: return true;
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
bool Gd__gd_core__LeatherHelm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1812: out = fn_getStunProtectChance(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_getBuffDur_1813: out = fn_getBuffDur(args, argc); return true;
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
bool Gd__gd_core__LeatherHelm::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_getStunProtectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeCritResistance_1157, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStunProtectChance_1812, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeStunResistance_1160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    this->f_buffsActive = gd::gd_add(gd_ctx, this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBuffDur_1813, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_getBuffDur(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    this->f_buffsActive = gd::gd_sub(this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_damReduction = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LeatherHelm(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__LeatherHelm>(&ctx); }
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onFoodActivated_1861: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Pandamonium::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onFoodActivated_1861: out = fn_onFoodActivated(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1074 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1075 = (_t1074.kind == gd::GdVal::Kind::Arr) ? _t1074.arr : nullptr;
        uint32_t _len__t1076 = _t1075 ? _t1075->len : 0u;
        for (uint32_t _t1076 = 0; _t1076 < _len__t1076; ++_t1076) {
            gd::GdVal lv_item = _t1075->data[_t1076];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onFoodActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1267, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_onFoodActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1077 = lv_forDirection;
        if (gd::gd_eq(_t1077, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        }
        else if (gd::gd_eq(_t1077, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1077, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1077, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Pandamonium(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Pandamonium>(&ctx); }
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__RainbowGoobertRanger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RainbowGoobertRanger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RainbowGoobertRanger::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
    {
        gd::GdVal _t1078 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1079 = (_t1078.kind == gd::GdVal::Kind::Arr) ? _t1078.arr : nullptr;
        uint32_t _len__t1080 = _t1079 ? _t1079->len : 0u;
        for (uint32_t _t1080 = 0; _t1080 < _len__t1080; ++_t1080) {
            gd::GdVal lv_item = _t1079->data[_t1080];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_270, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RainbowGoobertRanger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__RainbowGoobertRanger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__RainbowGoobertRanger>(&ctx); }
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
        case SYM_GEN_getStunProtectChance_1812: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core__StoneHelm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1812: out = fn_getStunProtectChance(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StoneHelm::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherHelm::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StoneHelm::fn_getStunProtectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneHelm::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onCombatStart_934, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneHelm::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StoneHelm(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__StoneHelm>(&ctx); }
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__VampiricArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__VampiricArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__VampiricArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_330, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_330, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__VampiricArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__VampiricArmor>(&ctx); }
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_preHit_907: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::has_own_method(m);
}
bool Gd__gd_core_items__ArtifactStoneHeat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_preHit_907: out = fn_preHit(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_heat_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHeatChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    this->f_dmgBonusActive = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_dmgBonusActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))))) {
            this->f_dmgBonusActive = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            {
                gd::GdVal _t1081 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
                gd::GdArr* _t1082 = (_t1081.kind == gd::GdVal::Kind::Arr) ? _t1081.arr : nullptr;
                uint32_t _len__t1083 = _t1082 ? _t1082->len : 0u;
                for (uint32_t _t1083 = 0; _t1083 < _len__t1083; ++_t1083) {
                    gd::GdVal lv_weapon = _t1082->data[_t1083];
                    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, lv_weapon, SYM_GEN_addBonusDamage_163, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Stone::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ArtifactStoneHeat(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ArtifactStoneHeat>(&ctx); }
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
bool Gd__gd_core_items__BurningCoal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_deal_damage_early", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preAttack", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), gd::gd_round(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0)))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeResistStacks_1026, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BurningCoal(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__BurningCoal>(&ctx); }
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
        case SYM_GEN_critBonusActive_1734: out = this->f_critBonusActive; return true;
        case SYM_GEN_poisonThreshold_1735: out = this->f_poisonThreshold; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__DeathScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_critBonusActive_1734: this->f_critBonusActive = val; return true;
        case SYM_GEN_poisonThreshold_1735: this->f_poisonThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DeathScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onOpponentPoisonChanged_1736: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__DeathScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1736: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Poison_2567)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_88, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_poison_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentPoisonChanged", 23u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    {
        gd::GdVal _t1084 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1085 = (_t1084.kind == gd::GdVal::Kind::Arr) ? _t1084.arr : nullptr;
        uint32_t _len__t1086 = _t1085 ? _t1085->len : 0u;
        for (uint32_t _t1086 = 0; _t1086 < _len__t1086; ++_t1086) {
            gd::GdVal lv_item = _t1085->data[_t1086];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getPoison_1213, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_critBonusActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, this->f_poisonThreshold)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCritChancePercent_183, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poisonThreshold = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DeathScythe(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__DeathScythe>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__DeathScythe = {CLS_Gd__gd_core_items__DeathScythe, "DeathScythe", "res://gd_core_items/DeathScythe.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__DeathScythe, &Gd__gd_core_items__DeathScythe::get_static_prop_fn, &Gd__gd_core_items__DeathScythe::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofLife::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofLife::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofLife; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLife::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_1927: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.980469), gd::GdVal::from_float(0.214478), gd::GdVal::from_float(0.214478)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofLife::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofLife::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_amuletColor_1927: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofLife::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofLife::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofLife::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofLife::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLife::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_addHealingEfficiency_1166, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLife::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLife::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofLife(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofLife>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofLife = {CLS_Gd__gd_core_items__Exclusive__AmuletofLife, "AmuletofLife", "res://gd_core_items/Exclusive/AmuletofLife.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofLife, &Gd__gd_core_items__Exclusive__AmuletofLife::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofLife::call_static_fn};

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
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Axe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Axe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Axe(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Axe>(&ctx); }
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
        case SYM_GEN_damFactor_1800: out = this->f_damFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Bomb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_damFactor_1800: this->f_damFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Bomb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Bomb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Bomb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Bomb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
        gd::GdVal lv_removedBuffs = gd::GdVal::from_int(0LL);
        {
            gd::GdVal _t1087 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
            gd::GdArr* _t1088 = (_t1087.kind == gd::GdVal::Kind::Arr) ? _t1087.arr : nullptr;
            uint32_t _len__t1089 = _t1088 ? _t1088->len : 0u;
            for (uint32_t _t1089 = 0; _t1089 < _len__t1089; ++_t1089) {
                gd::GdVal lv_buff = _t1088->data[_t1089];
                gd::GdVal lv_numStacks = ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getStacks_1022, _ca, 1); })();
                lv_removedBuffs = gd::gd_add(gd_ctx, lv_removedBuffs, lv_numStacks);
                (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_numStacks, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 3); })();
            }
        }
        (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(this->f_damFactor), lv_removedBuffs)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
        gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579);
        gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_223, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bomb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damFactor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Bomb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Bomb>(&ctx); }
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
        case SYM_GEN_spikesAcc_2013: out = this->f_spikesAcc; return true;
        case SYM_GEN_affectedItemsDict_2014: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        case SYM_GEN_spikesNeeded_2015: out = this->f_spikesNeeded; return true;
        case SYM_GEN_heatForSpikes_2016: out = this->f_heatForSpikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesAcc_2013: this->f_spikesAcc = val; return true;
        case SYM_GEN_affectedItemsDict_2014: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        case SYM_GEN_spikesNeeded_2015: this->f_spikesNeeded = val; return true;
        case SYM_GEN_heatForSpikes_2016: this->f_heatForSpikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Spikes_2565)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_88, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_spikesAcc = gd::GdVal::from_int(0LL);
    this->f_affectedItemsDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_arrayAsIndexDict_1704, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1455), this->f_affectedItemsDict))) : gd::GdVal::from_bool(false)))) {
        this->f_spikesAcc = gd::gd_add(gd_ctx, this->f_spikesAcc, lv_amount);
        gd::GdVal lv_numProccs = gd::gd_div(gd_ctx, this->f_spikesAcc, this->f_spikesNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_heatForSpikes, lv_numProccs)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
            this->f_spikesAcc = gd::gd_mod(gd_ctx, this->f_spikesAcc, this->f_spikesNeeded);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_spikesNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikest", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_heatForSpikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BurningSpikes(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BurningSpikes>(&ctx); }
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
        case SYM_GEN_doCapturingEffect_2050: return true;
        case SYM_GEN_doEliminatedEffect_2052: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2052: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCaptures, gd::GdVal::from_int(1LL))))) {
        return ([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_375, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_375, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackQueen::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackQueen::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__BlackQueen(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__BlackQueen>(&ctx); }
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
        case SYM_GEN_chargeCells1_2037: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(3LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float())}));
        case SYM_GEN_chargeCells2_2038: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(2LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float())}));
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
        case SYM_GEN_hasActivated_1811: out = this->f_hasActivated; return true;
        case SYM_GEN_speedMalus_2085: out = this->f_speedMalus; return true;
        case SYM_GEN_cdAdvanceBase_2086: out = this->f_cdAdvanceBase; return true;
        case SYM_GEN_cdAdvanceBonus_2087: out = this->f_cdAdvanceBonus; return true;
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        case SYM_GEN_chargeCells1_2037: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_chargeCells2_2038: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1811: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_speedMalus_2085: this->f_speedMalus = val; return true;
        case SYM_GEN_cdAdvanceBase_2086: this->f_cdAdvanceBase = val; return true;
        case SYM_GEN_cdAdvanceBonus_2087: this->f_cdAdvanceBonus = val; return true;
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_lightning_291: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case SYM_GEN_emitCharge_1963: return true;
        case SYM_GEN_onChargeEnteredCell_1964: return true;
        case SYM_GEN_chargedItemStatChange_1965: return true;
        case SYM_GEN_getTextureSize_781: return true;
        case SYM_GEN_getSpriteOffset_783: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_lightning_291: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_emitCharge_1963: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_1964: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_1965: out = fn_chargedItemStatChange(args, argc); return true;
        case SYM_GEN_getTextureSize_781: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN_getSpriteOffset_783: out = fn_getSpriteOffset(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_298, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_reactsToCharges_301, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    gd::GdVal lv_item = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_430, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_speedMalus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_1963, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charge_emitted", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
        gd::GdVal lv_item = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_430, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
            gd::GdVal lv_cdAdvance = this->f_cdAdvanceBase;
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0))))) {
                lv_cdAdvance = gd::gd_add(gd_ctx, lv_cdAdvance, this->f_cdAdvanceBonus);
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_cdAdvance}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_advanceCooldownSeconds_149, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), Gd__gd_core_items__Exclusive__ConTrapTron::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells1_2037), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_322, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), Gd__gd_core_items__Exclusive__ConTrapTron::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells2_2038), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_322, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_328, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_199, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedMalus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_cdAdvanceBase = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdadvance_base", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_cdAdvanceBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdadvance_bonus", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healtht", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ConTrapTron(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ConTrapTron>(&ctx); }
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
        case SYM_GEN_debuffsNeeded_2111: out = this->f_debuffsNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_debuffsNeeded_2111: this->f_debuffsNeeded = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_debuffsChanged_2112: return true;
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_debuffsChanged_2112: out = fn_debuffsChanged(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffsChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterDebuffs_377, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_debuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getDebuffStacks_1200, nullptr, 0), this->f_debuffsNeeded)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1753, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_debuffsNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DivinePotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DivinePotion>(&ctx); }
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
        case SYM_GEN_stunReadyTime_2143: out = this->f_stunReadyTime; return true;
        case SYM_GEN_debuffResistChance_2144: out = this->f_debuffResistChance; return true;
        case SYM_GEN_debuffResistTimer_2145: out = this->f_debuffResistTimer; return true;
        case SYM_GEN_stunCd_2146: out = this->f_stunCd; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stunReadyTime_2143: this->f_stunReadyTime = val; return true;
        case SYM_GEN_debuffResistChance_2144: this->f_debuffResistChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_debuffResistTimer_2145: this->f_debuffResistTimer = val; return true;
        case SYM_GEN_stunCd_2146: this->f_stunCd = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_1957: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_combatStartArmor_986: return true;
        case SYM_GEN_removeDebuffResistance_2147: return true;
        case SYM_GEN_combatEndArmor_989: return true;
        case SYM_GEN_hasCooldown_97: return true;
        case SYM_GEN_combatStartInventory_984: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN_hasInventoryDuration_797: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1957: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_combatStartArmor_986: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_removeDebuffResistance_2147: out = fn_removeDebuffResistance(args, argc); return true;
        case SYM_GEN_combatEndArmor_989: out = fn_combatEndArmor(args, argc); return true;
        case SYM_GEN_hasCooldown_97: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_combatStartInventory_984: out = fn_combatStartInventory(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN_hasInventoryDuration_797: out = fn_hasInventoryDuration(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), this->f_stunReadyTime)))) {
            this->f_stunReadyTime = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), this->f_stunCd);
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_debuffResistChance = gd::gd_coerce_float(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {this->f_debuffResistChance}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDebuffResistChances_1204, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_resist", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_debuffResistTimer, SYM_GEN_start_1685, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_removeDebuffResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_debuffResistChance)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDebuffResistChances_1204, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatEndArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_debuffResistTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatStartInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_debuffResistTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "DebuffResistTimer", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "removeDebuffResistance", 22u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_stunCd = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldown_102, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ElephantRune(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ElephantRune>(&ctx); }
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
        case SYM_GEN_cleanses_1803: out = this->f_cleanses; return true;
        case SYM_GEN_potionSpeed_2165: out = this->f_potionSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Shelly::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cleanses_1803: this->f_cleanses = val; return true;
        case SYM_GEN_potionSpeed_2165: this->f_potionSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Shelly::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onPrepare_125: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Shelly::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cleanses}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDebuffProtectionChance_1271, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_potionSpeed, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_cleanses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffs", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_potionSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Shelly(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Shelly>(&ctx); }
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
        case SYM_GEN_active_2129: out = this->f_active; return true;
        case SYM_GEN_blockAmp_2190: out = this->f_blockAmp; return true;
        case SYM_GEN_damReduction_1778: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_2129: this->f_active = val; return true;
        case SYM_GEN_blockAmp_2190: this->f_blockAmp = val; return true;
        case SYM_GEN_damReduction_1778: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemAdded_439: return true;
        case SYM_GEN_onItemRemoved_440: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_checkItems_2128: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_preTakeDamage_1849: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemAdded_439: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_440: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_checkItems_2128: out = fn_checkItems(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preTakeDamage_1849: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_439, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2128, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_440, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2128, nullptr, 0);
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
        gd::GdVal _t1090 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t1091 = (_t1090.kind == gd::GdVal::Kind::Arr) ? _t1090.arr : nullptr;
        uint32_t _len__t1092 = _t1091 ? _t1091->len : 0u;
        for (uint32_t _t1092 = 0; _t1092 < _len__t1092; ++_t1092) {
            gd::GdVal lv_item = _t1091->data[_t1092];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Armor_2751)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_numArmor = gd::gd_add(gd_ctx, lv_numArmor, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Helmet_2752)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_numHelmets = gd::gd_add(gd_ctx, lv_numHelmets, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Shoes_2753)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_numShoes = gd::gd_add(gd_ctx, lv_numShoes, gd::GdVal::from_int(1LL));
            }
        }
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_numArmor, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_numHelmets, gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_numShoes, gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false)))) {
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_293, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1093 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1094 = (_t1093.kind == gd::GdVal::Kind::Arr) ? _t1093.arr : nullptr;
        uint32_t _len__t1095 = _t1094 ? _t1094->len : 0u;
        for (uint32_t _t1095 = 0; _t1095 < _len__t1095; ++_t1095) {
            gd::GdVal lv_item = _t1094->data[_t1095];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), this->f_blockAmp}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
        }
    }
    if (gd::gd_truth(this->f_active)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preTakeDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttackOrEffect_1471, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_applyDamageReduction_1435, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_blockAmp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damreduction", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FullBodyProtection(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FullBodyProtection>(&ctx); }
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
        case SYM_GEN_flatDam_2212: out = this->f_flatDam; return true;
        case SYM_GEN_damFactor_1800: out = this->f_damFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeroShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flatDam_2212: this->f_flatDam = val; return true;
        case SYM_GEN_damFactor_1800: this->f_damFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeroShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeroShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeroShield::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1096 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1097 = (_t1096.kind == gd::GdVal::Kind::Arr) ? _t1096.arr : nullptr;
        uint32_t _len__t1098 = _t1097 ? _t1097->len : 0u;
        for (uint32_t _t1098 = 0; _t1098 < _len__t1098; ++_t1098) {
            gd::GdVal lv_item = _t1097->data[_t1098];
            (void)([&]() { gd::GdVal _ca[] = {this->f_flatDam}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_damFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_308, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeroShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__WoodenBuckler::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_flatDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_damFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damfactor", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HeroShield(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HeroShield>(&ctx); }
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
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Crown::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__KingCrown::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Crown::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__KingCrown::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Crown::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gemPower = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gempower", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t1099 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t1100 = (_t1099.kind == gd::GdVal::Kind::Arr) ? _t1099.arr : nullptr;
        uint32_t _len__t1101 = _t1100 ? _t1100->len : 0u;
        for (uint32_t _t1101 = 0; _t1101 < _len__t1101; ++_t1101) {
            gd::GdVal lv_gem = _t1100->data[_t1101];
            (void)([&]() { gd::GdVal _ca[] = {lv_gemPower}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN_changeGemPower_974, _ca, 1); })();
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Crown::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeBuffProtectStacks_1171, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Normal_2541), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Crown::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__KingCrown(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__KingCrown>(&ctx); }
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
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Mana_2571)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_88, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1102 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1103 = (_t1102.kind == gd::GdVal::Kind::Arr) ? _t1102.arr : nullptr;
        uint32_t _len__t1104 = _t1103 ? _t1103->len : 0u;
        for (uint32_t _t1104 = 0; _t1104 < _len__t1104; ++_t1104) {
            gd::GdVal lv_item = _t1103->data[_t1104];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_198, _ca, 2); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_mana = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MagicBadge(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MagicBadge>(&ctx); }
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
        case SYM_GEN_totalBlockRemoval_1886: out = this->f_totalBlockRemoval; return true;
        case SYM_GEN_blockRemoval_1802: out = this->f_blockRemoval; return true;
        case SYM_GEN_missDamage_2312: out = this->f_missDamage; return true;
        case SYM_GEN_heatNeeded_1785: out = this->f_heatNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_totalBlockRemoval_1886: this->f_totalBlockRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockRemoval_1802: this->f_blockRemoval = val; return true;
        case SYM_GEN_missDamage_2312: this->f_missDamage = val; return true;
        case SYM_GEN_heatNeeded_1785: this->f_heatNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_affectsEmpty_257: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_affectsEmpty_257: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_totalBlockRemoval = gd::gd_coerce_int(gd::gd_mul(this->f_blockRemoval, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_431, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_428, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), this->f_heatNeeded)))) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), this->f_missDamage));
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1429, gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_356, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_totalBlockRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_207, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_blockRemoval = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blockremoval", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_missDamage = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "missdam", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_heatNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MoltenSpear(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MoltenSpear>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenSpear = {CLS_Gd__gd_core_items__Exclusive__MoltenSpear, "MoltenSpear", "res://gd_core_items/Exclusive/MoltenSpear.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__MoltenSpear, &Gd__gd_core_items__Exclusive__MoltenSpear::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MoltenSpear::call_static_fn};

void Gd__gd_core_items__Exclusive__PiggyPinata::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_piggybankDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PiggyPinata::meta() const { return &META_Gd__gd_core_items__Exclusive__PiggyPinata; }
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_piggybankDescriptor_2330: out = this->f_piggybankDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_piggybankDescriptor_2330: this->f_piggybankDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_canAffect_global_1919: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_canAffect_global_1919: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1105 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1106 = (_t1105.kind == gd::GdVal::Kind::Arr) ? _t1105.arr : nullptr;
        uint32_t _len__t1107 = _t1106 ? _t1106->len : 0u;
        for (uint32_t _t1107 = 0; _t1107 < _len__t1107; ++_t1107) {
            gd::GdVal lv_item = _t1106->data[_t1107];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_piggybankDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_piggybankDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Piggybank", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PiggyPinata(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PiggyPinata>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PiggyPinata = {CLS_Gd__gd_core_items__Exclusive__PiggyPinata, "PiggyPinata", "res://gd_core_items/Exclusive/PiggyPinata.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PiggyPinata, &Gd__gd_core_items__Exclusive__PiggyPinata::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PiggyPinata::call_static_fn};

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
        case SYM_GEN_bonusdur_2355: out = this->f_bonusdur; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusdur_2355: this->f_bonusdur = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_125: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getBagEffect_482: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getBagEffect_482: out = fn_getBagEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasInventoryDuration_797, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1108 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1109 = (_t1108.kind == gd::GdVal::Kind::Arr) ? _t1108.arr : nullptr;
        uint32_t _len__t1110 = _t1109 ? _t1109->len : 0u;
        for (uint32_t _t1110 = 0; _t1110 < _len__t1110; ++_t1110) {
            gd::GdVal lv_item = _t1109->data[_t1110];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u)), this->f_bonusdur}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_modifyParam_193, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_getBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_number = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getName_236, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_BAGEFFECT", 10u)))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_bonusdur", 10u)), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonusdur", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), lv_number)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_bonusdur = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonusdur", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PuzzlebagJ(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PuzzlebagJ>(&ctx); }
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
        case SYM_GEN_stamina_2060: out = this->f_stamina; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RatChef::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stamina_2060: this->f_stamina = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RatChef::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_initRat_2371: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RatChef::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_initRat_2371: out = fn_initRat(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t1111 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1112 = (_t1111.kind == gd::GdVal::Kind::Arr) ? _t1111.arr : nullptr;
        uint32_t _len__t1113 = _t1112 ? _t1112->len : 0u;
        for (uint32_t _t1113 = 0; _t1113 < _len__t1113; ++_t1113) {
            gd::GdVal lv_item = _t1112->data[_t1113];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_numAffectedFood = gd::gd_add(gd_ctx, lv_numAffectedFood, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_numAffectedFood}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1114 = lv_forDirection;
        if (gd::gd_eq(_t1114, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1114, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1114, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        }
        else if (gd::gd_eq(_t1114, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Rat::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RatChef(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RatChef>(&ctx); }
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
        case SYM_GEN_damageAcc_1865: out = this->f_damageAcc; return true;
        case SYM_GEN_manaUseEvents_2391: out = this->f_manaUseEvents; return true;
        case SYM_GEN_manaCost_1720: out = this->f_manaCost; return true;
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        case SYM_GEN_poison_1867: out = this->f_poison; return true;
        case SYM_GEN_damageForPoison_2392: out = this->f_damageForPoison; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1865: this->f_damageAcc = val; return true;
        case SYM_GEN_manaUseEvents_2391: this->f_manaUseEvents = val; return true;
        case SYM_GEN_manaCost_1720: this->f_manaCost = val; return true;
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        case SYM_GEN_poison_1867: this->f_poison = val; return true;
        case SYM_GEN_damageForPoison_2392: this->f_damageForPoison = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_manaUseEvents, gd::SYM_clear, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeResistChance_1025, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_manaUseEvent = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_335, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_manaUseEvent, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_manaUseEvent}; return gd::call_method(gd_ctx, this->f_manaUseEvents, gd::SYM_push_back, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_manaUseEvents, gd::SYM_empty, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        this->f_damageAcc = gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427));
        gd::GdVal lv_curPoison = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damageForPoison);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_curPoison, gd::GdVal::from_int(0LL))))) {
            this->f_damageAcc = gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damageForPoison);
            (void)([&]() { gd::GdVal _ca[] = {lv_curPoison, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 2); })();
        }
        (void)gd::call_method(gd_ctx, this->f_manaUseEvents, gd::SYM_pop_back, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_permDamBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_poison = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_damageForPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damforpoison", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SerpentStaff(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SerpentStaff>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SerpentStaff = {CLS_Gd__gd_core_items__Exclusive__SerpentStaff, "SerpentStaff", "res://gd_core_items/Exclusive/SerpentStaff.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SerpentStaff, &Gd__gd_core_items__Exclusive__SerpentStaff::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SerpentStaff::call_static_fn};

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
        case SYM_GEN_cold_1950: out = this->f_cold; return true;
        case SYM_GEN_selfCold_2418: out = this->f_selfCold; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SnowStick::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_1950: this->f_cold = val; return true;
        case SYM_GEN_selfCold_2418: this->f_selfCold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SnowStick::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SnowStick::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), this->f_selfCold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SnowStick::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_selfCold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SnowStick(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SnowStick>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SnowStick = {CLS_Gd__gd_core_items__Exclusive__SnowStick, "SnowStick", "res://gd_core_items/Exclusive/SnowStick.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SnowStick, &Gd__gd_core_items__Exclusive__SnowStick::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SnowStick::call_static_fn};

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
        case SYM_GEN_colors_2443: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.489231), gd::GdVal::from_float(0.301961)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.301961), gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.41682)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.301961), gd::GdVal::from_float(0.513726)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.320312), gd::GdVal::from_float(0.466339), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })()); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_neutralColor_2444: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.364706)}; return gd::make_color_from_args(_ca, 4); })();
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
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        case SYM_GEN_frame_2445: out = this->f_frame; return true;
        case SYM_GEN_skillLight_2446: out = this->f_skillLight; return true;
        case SYM_GEN_colors_2443: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_neutralColor_2444: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        case SYM_GEN_frame_2445: this->f_frame = val; return true;
        case SYM_GEN_skillLight_2446: this->f_skillLight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_ready_deferred_465: return true;
        case SYM_GEN_updateColor_2447: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_gainsStack_88: return true;
        case SYM_GEN_rotateTo_478: return true;
        case SYM_GEN_setFaceDirectionInstant_469: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_ready_deferred_465: out = fn_ready_deferred(args, argc); return true;
        case SYM_GEN_updateColor_2447: out = fn_updateColor(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_gainsStack_88: out = fn_gainsStack(args, argc); return true;
        case SYM_GEN_rotateTo_478: out = fn_rotateTo(args, argc); return true;
        case SYM_GEN_setFaceDirectionInstant_469: out = fn_setFaceDirectionInstant(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_ready_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_ready_deferred_465, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2447, nullptr, 0);
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
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_inactiveColor_2731)}));
    gd::GdVal lv_gold = gd::GdVal::from_int(0);
    if (gd::gd_truth(this->f_placed)) {
        { gd::GdVal _t1115 = lv_colors; gd::GdVal _t1116 = this->f_faceDirection; gd::set_index(gd_ctx, _t1115, _t1116, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_modifiedColor_2724)); }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(false), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_645, _ca, 4); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1117 = this->f_faceDirection;
        if (gd::gd_eq(_t1117, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
        }
        else if (gd::gd_eq(_t1117, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
        }
        else if (gd::gd_eq(_t1117, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
        }
        else if (gd::gd_eq(_t1117, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_gainsStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1118 = this->f_faceDirection;
        if (gd::gd_eq(_t1118, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_bool(gd::gd_eq(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Heat_2573)));
        }
        else if (gd::gd_eq(_t1118, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_bool(gd::gd_eq(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Lucky_2570)));
        }
        else if (gd::gd_eq(_t1118, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_bool(gd::gd_eq(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Regeneration_2569)));
        }
        else if (gd::gd_eq(_t1118, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_bool(gd::gd_eq(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Mana_2571)));
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_rotateTo(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetRotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.15));
    (void)([&]() { gd::GdVal _ca[] = {lv_targetRotation, lv_duration}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_rotateTo_478, _ca, 2, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2447, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_setFaceDirectionInstant(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv__faceDirection}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_setFaceDirectionInstant_469, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2447, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpintoWin(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpintoWin>(&ctx); }
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
        case SYM_GEN_curLifesteal_2470: out = this->f_curLifesteal; return true;
        case SYM_GEN_lifestealGiven_2471: out = this->f_lifestealGiven; return true;
        case SYM_GEN_lifestealTimer_2472: out = this->f_lifestealTimer; return true;
        case SYM_GEN_lifestealPerTrigger_2473: out = this->f_lifestealPerTrigger; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_curLifesteal_2470: this->f_curLifesteal = gd::gd_coerce_float(val); return true;
        case SYM_GEN_lifestealGiven_2471: this->f_lifestealGiven = val; return true;
        case SYM_GEN_lifestealTimer_2472: this->f_lifestealTimer = val; return true;
        case SYM_GEN_lifestealPerTrigger_2473: this->f_lifestealPerTrigger = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_onOpponentDamaged_1897: return true;
        case SYM_GEN_onLifestealTimeout_2474: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1897: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_onLifestealTimeout_2474: out = fn_onLifestealTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__VampiricPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, SYM_GEN_onPrepare_125, nullptr, 0, _out); return _out; })();
    this->f_curLifesteal = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)gd::call_method(gd_ctx, this->f_lifestealGiven, gd::SYM_clear, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_attacked", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDamaged", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_amount = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_curLifesteal = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curLifesteal, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, this->f_lifestealGiven, gd::SYM_push_back, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_lifestealTimer, SYM_GEN_start_1685, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_curLifesteal, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_canApplyLifesteal_1472, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), this->f_curLifesteal)), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onLifestealTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_curLifesteal = gd::gd_coerce_float(gd::gd_sub(this->f_curLifesteal, gd::call_method(gd_ctx, this->f_lifestealGiven, gd::SYM_pop_front, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_lifestealTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_lifestealTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "LifestealTimer", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLifestealTimeout", 18u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_lifestealPerTrigger = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StrongVampiricPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StrongVampiricPotion>(&ctx); }
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
        case SYM_GEN_extraDamBlock_2501: out = this->f_extraDamBlock; return true;
        case SYM_GEN_maxHealthBlock_2502: out = this->f_maxHealthBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Turtle::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraDamBlock_2501: this->f_extraDamBlock = val; return true;
        case SYM_GEN_maxHealthBlock_2502: this->f_maxHealthBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Turtle::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Turtle::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Shield_2754)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1119 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1120 = (_t1119.kind == gd::GdVal::Kind::Arr) ? _t1119.arr : nullptr;
        uint32_t _len__t1121 = _t1120 ? _t1120->len : 0u;
        for (uint32_t _t1121 = 0; _t1121 < _len__t1121; ++_t1121) {
            gd::GdVal lv_item = _t1120->data[_t1121];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damblock", 8u)), this->f_extraDamBlock}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_modifyParam_193, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onPreCombatStart_127, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_buffEnded_1722, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_blockAmount = gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::gd_mul(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMaxHealth_1144, nullptr, 0), this->f_maxHealthBlock));
    (void)([&]() { gd::GdVal _ca[] = {lv_blockAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_extraDamBlock = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonus_damblock", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxHealthBlock = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Turtle(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Turtle>(&ctx); }
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
        case SYM_GEN_damageAcc_1865: out = this->f_damageAcc; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_natureSpeed_2528: out = this->f_natureSpeed; return true;
        case SYM_GEN_damageForSpikes_2529: out = this->f_damageForSpikes; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Wisp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1865: this->f_damageAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_natureSpeed_2528: this->f_natureSpeed = val; return true;
        case SYM_GEN_damageForSpikes_2529: this->f_damageForSpikes = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Wisp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasCooldown_97: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_prepareInventory_981: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_1957: return true;
        case SYM_GEN_combatStart_129: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Wisp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasCooldown_97: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepareInventory_981: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1957: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_combatStart_129: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Wisp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2751))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_prepareInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), this->f_natureSpeed)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        this->f_damageAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427)));
        gd::GdVal lv_numProccs = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damageForSpikes);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            this->f_damageAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damageForSpikes));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_spikes, lv_numProccs)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1122 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::gd_eq(_t1122, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755))) {
            this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })());
        }
        else if (gd::gd_eq(_t1122, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2751))) {
            this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })());
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN_combatStart_129, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1123 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::gd_eq(_t1123, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
        }
        else if (gd::gd_eq(_t1123, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2751))) {
            gd::GdVal lv_bonusHealth = gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentHealth_1138, nullptr, 0));
            lv_bonusHealth = gd::gd_mul(lv_bonusHealth, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0));
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusHealth}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, _ca, 1); })();
            this->f_consumed = gd::GdVal::from_bool(true);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_natureSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageForSpikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Wisp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Wisp>(&ctx); }
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
        case SYM_GEN_manaCounter_2537: out = this->f_manaCounter; return true;
        case SYM_GEN_spectral_2538: out = this->f_spectral; return true;
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Sapphire::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaCounter_2537: this->f_manaCounter = val; return true;
        case SYM_GEN_spectral_2538: this->f_spectral = val; return true;
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Sapphire::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_preAttack_996: return true;
        case SYM_GEN_onAttack_1957: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_onManaChanged_1834: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Sapphire::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_preAttack_996: out = fn_preAttack(args, argc); return true;
        case SYM_GEN_onAttack_1957: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onManaChanged_1834: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Sapphire::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_spectral = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_deal_damage_late", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preAttack", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_spectral = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0);
    if (gd::gd_truth(this->f_spectral)) {
        (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_makeSpectral_1473, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(this->f_spectral) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaCounter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_manaCounter = gd::gd_add(gd_ctx, this->f_manaCounter, lv_amount);
        gd::GdVal lv_relMana = gd::gd_div(gd_ctx, this->f_manaCounter, this->f_manaNeeded);
        gd::GdVal lv_block = gd::gd_mul(lv_relMana, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
        this->f_manaCounter = gd::gd_mod(gd_ctx, this->f_manaCounter, this->f_manaNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_block, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), lv_block), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_relMana, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_relMana, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Sapphire(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Gems__Sapphire>(&ctx); }
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
        case SYM_GEN_emitter_1558: out = this->f_emitter; return true;
        case SYM_GEN_signalName_1013: out = this->f_signalName; return true;
        case SYM_GEN_receiver_1559: out = this->f_receiver; return true;
        case SYM_GEN_methodName_1560: out = this->f_methodName; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_emitter_1558: this->f_emitter = val; return true;
        case SYM_GEN_signalName_1013: this->f_signalName = val; return true;
        case SYM_GEN_receiver_1559: this->f_receiver = val; return true;
        case SYM_GEN_methodName_1560: this->f_methodName = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_destroy_1561: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_destroy_1561: out = fn_destroy(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_signalName, this->f_receiver, this->f_methodName, lv_binds}; return gd::call_method(gd_ctx, this->f_emitter, gd::SYM_connect, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item__INNER__SignalConnection::fn_destroy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Item__INNER__SignalConnection(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Item__INNER__SignalConnection>(&ctx); }
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
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Pineapple::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Pineapple::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Pineapple::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pineapple::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Pineapple(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Pineapple>(&ctx); }
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
        case SYM_GEN_blockFactor_1882: out = this->f_blockFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::get_prop(prop, out);
}
bool Gd__gd_core_items__ShieldofValor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockFactor_1882: this->f_blockFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ShieldofValor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_afterBlock_1847: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::has_own_method(m);
}
bool Gd__gd_core_items__ShieldofValor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1847: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_293, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1124 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1125 = (_t1124.kind == gd::GdVal::Kind::Arr) ? _t1124.arr : nullptr;
        uint32_t _len__t1126 = _t1125 ? _t1125->len : 0u;
        for (uint32_t _t1126 = 0; _t1126 < _len__t1126; ++_t1126) {
            gd::GdVal lv_item = _t1125->data[_t1126];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), this->f_blockFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_119, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_blockFactor = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ShieldofValor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ShieldofValor>(&ctx); }
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
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__ThornWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ThornWhip::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ThornWhip(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ThornWhip>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__ThornWhip = {CLS_Gd__gd_core_items__ThornWhip, "ThornWhip", "res://gd_core_items/ThornWhip.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__ThornWhip, &Gd__gd_core_items__ThornWhip::get_static_prop_fn, &Gd__gd_core_items__ThornWhip::call_static_fn};
