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
    this->f_shadowOffset = Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_521);
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
const gd::GdClassMeta* Gd__gd_core_items__Item::meta() const { return &META_Gd__gd_core_items__Item; }
gd::GdVal Gd__gd_core_items__Item::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_Owner_850: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Owner);
        case SYM_GEN_Type_851: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Type);
        case SYM_GEN_Priority_852: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Priority);
        case SYM_GEN_CraftingPriority_853: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_CraftingPriority);
        case SYM_GEN_Tag_854: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Tag);
        case SYM_GEN_Stack_855: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Stack);
        case SYM_GEN_Mat_856: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Mat);
        case SYM_GEN_Physics_857: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Physics);
        case SYM_GEN_Rarity_858: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Rarity);
        case SYM_GEN_FaceDirection_859: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_FaceDirection);
        case SYM_GEN_StatModified_860: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_StatModified);
        case SYM_GEN_DropResult_861: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_DropResult);
        case SYM_GEN_PickupType_862: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_PickupType);
        case SYM_GEN_Affected_863: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Affected);
        case SYM_GEN_Tiles_864: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Tiles);
        case SYM_GEN_ActivationAni_865: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_ActivationAni);
        case SYM_GEN_Stat_866: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Stat);
        case SYM_GEN_StackChangeType_867: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_StackChangeType);
        case SYM_GEN_affectedColorToTileId_505: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580), gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_864), SYM_GEN_Affected_863)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582), gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_864), SYM_GEN_AffectedSecondary_2609)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Tertiary_2583), gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_864), SYM_GEN_AffectedTertiary_2610)); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611), gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_Tiles_864), SYM_GEN_AffectedLightning_2612)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_rarityColors_507: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.460205), gd::GdVal::from_float(0.874887), gd::GdVal::from_float(0.90625)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.0737), gd::GdVal::from_float(0.337874), gd::GdVal::from_float(0.898438)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.828125), gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.609375), gd::GdVal::from_int(0LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.980469), gd::GdVal::from_float(0.946239), gd::GdVal::from_float(0.582153)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.094223), gd::GdVal::from_float(0.964844), gd::GdVal::from_float(0.250663)}; return gd::make_color_from_args(_ca, 3); })()}));
        case SYM_GEN_offset_512: return gd::GdVal::from_int(40LL);
        case SYM_GEN_impulse_513: return gd::GdVal::from_int(50LL);
        case SYM_GEN_momentumFactor_514: return gd::GdVal::from_float(20.0);
        case SYM_GEN_affectedSoundsVolume_517: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580), gd::gd_neg(gd::GdVal::from_int(8LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Tertiary_2583), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Lightning_2611), gd::gd_neg(gd::GdVal::from_int(1LL))); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_cellSize_518: return gd::GdVal::from_vec2((gd::GdVal::from_int(80LL)).as_float(), (gd::GdVal::from_int(80LL)).as_float());
        case SYM_GEN_halfCellSize_519: return gd::gd_mul(gd::GdVal::from_float(0.5), Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518));
        case SYM_GEN_shadowOffset_shop_520: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        case SYM_GEN_shadowOffset_dropped_521: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(5LL)).as_float());
        case SYM_GEN_shadowOffset_dragged_522: return gd::GdVal::from_vec2((gd::GdVal::from_int(15LL)).as_float(), (gd::GdVal::from_int(15LL)).as_float());
        case SYM_GEN_DRAG_PRIORITY_523: return gd::GdVal::from_int(2LL);
        case SYM_GEN_correction_579: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518), gd::SYM_x))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518), gd::SYM_x))).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518), gd::SYM_y))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_518), gd::SYM_y))).as_float())}));
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
        case SYM_GEN_SignalConnection_873: return gd::GdVal::from_cls(&META_Gd__gd_core_items__Item__INNER__SignalConnection);
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
        case SYM_GEN_crafted_instance_898: out = this->f_crafted_instance; return true;
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
        case SYM_GEN_Owner_850: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Owner); return true;
        case SYM_GEN_Type_851: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Type); return true;
        case SYM_GEN_Priority_852: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Priority); return true;
        case SYM_GEN_CraftingPriority_853: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_CraftingPriority); return true;
        case SYM_GEN_Tag_854: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Tag); return true;
        case SYM_GEN_Stack_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Stack); return true;
        case SYM_GEN_Mat_856: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Mat); return true;
        case SYM_GEN_Physics_857: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Physics); return true;
        case SYM_GEN_Rarity_858: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Rarity); return true;
        case SYM_GEN_FaceDirection_859: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_FaceDirection); return true;
        case SYM_GEN_StatModified_860: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_StatModified); return true;
        case SYM_GEN_DropResult_861: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_DropResult); return true;
        case SYM_GEN_PickupType_862: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_PickupType); return true;
        case SYM_GEN_Affected_863: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Affected); return true;
        case SYM_GEN_Tiles_864: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Tiles); return true;
        case SYM_GEN_ActivationAni_865: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_ActivationAni); return true;
        case SYM_GEN_Stat_866: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_Stat); return true;
        case SYM_GEN_StackChangeType_867: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Item_StackChangeType); return true;
        case SYM_GEN_SignalConnection_873: out = gd::GdVal::from_cls(&META_Gd__gd_core_items__Item__INNER__SignalConnection); return true;
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
bool Gd__gd_core_items__Item::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
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
        case SYM_GEN_crafted_instance_898: this->f_crafted_instance = val; return true;
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
bool Gd__gd_core_items__Item::has_own_method(gd::SymId m) const {
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
bool Gd__gd_core_items__Item::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
bool Gd__gd_core_items__Item::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
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
gd::GdVal Gd__gd_core_items__Item::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__CoreItem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_hasPreDealDamageEarlyEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_early", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasPreDealDamageLateEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_late", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasDealtDamageEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDealtDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeReceivedEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeReceived", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeLeftEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeLeft", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_getNumTooltipStats(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_getNumStackChangeTypes(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_867), gd::SYM_size, nullptr, 0);
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Shop_2578))))) {
        return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_shop_520);
    }
    else {
        return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_521);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hoverEnd_709, nullptr, 0);
    if (gd::gd_truth(this->f_spotlight)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHover_691, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHoverEnd_700, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initBuildViewerIcon_631, nullptr, 0);
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
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n", 1u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedName_637, nullptr, 0), gd::SYM_replace, _ca, 2); })();
    }
    else {
        return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedName_637, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getDescription(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_insertParameters(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_wrapInColor = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_150, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(lv_wrapInColor)) : gd::GdVal::from_bool(false)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$dam", 4u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1577)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_paramColor_2620)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_wrapInColor_fixed_2621, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    {
        gd::GdVal _t991 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_extraCds_1582), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
        gd::GdArr* _t992 = (_t991.kind == gd::GdVal::Kind::Arr) ? _t991.arr : nullptr;
        uint32_t _len__t993 = _t992 ? _t992->len : 0u;
        for (uint32_t _t993 = 0; _t993 < _len__t993; ++_t993) {
            gd::GdVal lv_i = _t992->data[_t993];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })(), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldownIndex_103, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_276, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cd", 2u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_102, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_276, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance2", 7u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance2Modified_279, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance", 6u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance1Modified_278, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "shopchance", 10u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getShopChance_235, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_110, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStaminaModified_111, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
    {
        gd::GdVal _t994 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_params_1477), gd::SYM_size, nullptr, 0));
        gd::GdArr* _t995 = (_t994.kind == gd::GdVal::Kind::Arr) ? _t994.arr : nullptr;
        uint32_t _len__t996 = _t995 ? _t995->len : 0u;
        for (uint32_t _t996 = 0; _t996 < _len__t996; ++_t996) {
            gd::GdVal lv_i = _t995->data[_t996];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p", 1u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))))), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
        }
    }
    {
        gd::GdVal _t997 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_sortedParamNames_1613));
        gd::GdArr* _t998 = (_t997.kind == gd::GdVal::Kind::Arr) ? _t997.arr : nullptr;
        uint32_t _len__t999 = _t998 ? _t998->len : 0u;
        for (uint32_t _t999 = 0; _t999 < _len__t999; ++_t999) {
            gd::GdVal lv_paramName = _t998->data[_t999];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_", 2u)), lv_paramName), ([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
        }
    }
    if (gd::gd_truth(lv_wrapInColor)) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$block", 6u)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0))), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_paramColor_2620)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_wrapInColor_fixed_2621, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_insertParameter(const gd::GdVal* _args, int _argc) {
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
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getFlavorText_642, nullptr, 0);
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
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseFocus_699, nullptr, 0);
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
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_AddedToInventory_2624)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_Hotswap_2625))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_wasBought(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Item::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_655, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_AddedToStorageBox_2626))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_Socketed_2627))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_SocketHotswap_2628))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::sf_wasHotSwap(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_Hotswap_2625)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_SocketHotswap_2628))))));
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
        gd::GdVal _t1000 = gd::gd_iter_seq(gd_ctx.arena, lv_newItemIsAffected);
        gd::GdArr* _t1001 = (_t1000.kind == gd::GdVal::Kind::Arr) ? _t1000.arr : nullptr;
        uint32_t _len__t1002 = _t1001 ? _t1001->len : 0u;
        for (uint32_t _t1002 = 0; _t1002 < _len__t1002; ++_t1002) {
            gd::GdVal lv_color = _t1001->data[_t1002];
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
gd::GdVal Gd__gd_core_items__Item::fn_clearCanAffectVisuals(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_liesInStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerStorageBox_2579)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_dragged)))) : gd::GdVal::from_bool(false));
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killMovebackTween_723, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStorageLeft_665, nullptr, 0);
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkIfOutofStorageBounds2", 26u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callNextFrame_1701, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_checkIfOutofStorageBounds2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkIfOutofStorageBounds3", 26u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callNextFrame_1701, _ca, 2); })();
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_state, SYM_GEN_get_contact_count_2629, nullptr, 0), gd::GdVal::from_int(0LL))))) {
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateInsideRotationNode_682, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_680, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_739, nullptr, 0);
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
        return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_523);
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
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canGainFocus_689, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerInventory_2554)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Socket_2589))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Opponent_2544)))))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_highlightItem_2630, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHover_691, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHoverEnd_700, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_respondToHoverEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_activateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1003 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t1004 = (_t1003.kind == gd::GdVal::Kind::Arr) ? _t1003.arr : nullptr;
        uint32_t _len__t1005 = _t1004 ? _t1004->len : 0u;
        for (uint32_t _t1005 = 0; _t1005 < _len__t1005; ++_t1005) {
            gd::GdVal lv_specificParticles = _t1004->data[_t1005];
            (void)gd::call_method(gd_ctx, lv_specificParticles, SYM_GEN_activate_148, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_deactivateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1006 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t1007 = (_t1006.kind == gd::GdVal::Kind::Arr) ? _t1006.arr : nullptr;
        uint32_t _len__t1008 = _t1007 ? _t1007->len : 0u;
        for (uint32_t _t1008 = 0; _t1008 < _len__t1008; ++_t1008) {
            gd::GdVal lv_specificParticles = _t1007->data[_t1008];
            (void)gd::call_method(gd_ctx, lv_specificParticles, SYM_GEN_deactivate_2632, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hideBuildIntoRecipesTooltip_698, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearCanAffectVisuals_660, nullptr, 0);
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
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_862), SYM_GEN_Grabbed_2633));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onDraggedWithParentStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_parentItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_715, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showClickArea_720, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setSpriteGlobalPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_680, nullptr, 0);
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
        gd::GdVal _t1009 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t1010 = (_t1009.kind == gd::GdVal::Kind::Arr) ? _t1009.arr : nullptr;
        uint32_t _len__t1011 = _t1010 ? _t1010->len : 0u;
        for (uint32_t _t1011 = 0; _t1011 < _len__t1011; ++_t1011) {
            gd::GdVal lv_item = _t1010->data[_t1011];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_pushToStorage_662, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_477, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_729, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_reparentItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1012 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t1013 = (_t1012.kind == gd::GdVal::Kind::Arr) ? _t1012.arr : nullptr;
        uint32_t _len__t1014 = _t1013 ? _t1013->len : 0u;
        for (uint32_t _t1014 = 0; _t1014 < _len__t1014; ++_t1014) {
            gd::GdVal lv_item = _t1013->data[_t1014];
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_477, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_729, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_clearDraggedInsideItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1015 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t1016 = (_t1015.kind == gd::GdVal::Kind::Arr) ? _t1015.arr : nullptr;
        uint32_t _len__t1017 = _t1016 ? _t1016->len : 0u;
        for (uint32_t _t1017 = 0; _t1017 < _len__t1017; ++_t1017) {
            gd::GdVal lv_item = _t1016->data[_t1017];
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_onDraggedWithParentEnd_716, nullptr, 0);
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
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerInventory_2554)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerStorageBox_2579))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_Socket_2589))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isPickingPossible(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canBePicked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(this->f_focus) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isPickingPossible_734, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1380), this->f_dropFrame)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canBeDraggedWithBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canBeDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_dragged) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1380), this->f_pickupFrame)))) : gd::GdVal::from_bool(false));
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
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_249, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_646, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_739, nullptr, 0);
        (void)gd::call_method(gd_ctx, this->f_cachedAffectedItems, gd::SYM_clear, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_shopEntered(const gd::GdVal* _args, int _argc) {
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
        gd::GdVal _t1018 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffPowers);
        gd::GdArr* _t1019 = (_t1018.kind == gd::GdVal::Kind::Arr) ? _t1018.arr : nullptr;
        uint32_t _len__t1020 = _t1019 ? _t1019->len : 0u;
        for (uint32_t _t1020 = 0; _t1020 < _len__t1020; ++_t1020) {
            gd::GdVal lv_buff = _t1019->data[_t1020];
            { gd::GdVal _t1021 = this->f_buffPowers; gd::GdVal _t1022 = lv_buff; gd::set_index(gd_ctx, _t1021, _t1022, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t1023 = this->f_buffAmplificationChances; gd::GdVal _t1024 = lv_buff; gd::set_index(gd_ctx, _t1023, _t1024, gd::GdVal::from_float(0.0)); }
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_enablePicking_644, nullptr, 0);
    {
        gd::GdVal _t1025 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_495, nullptr, 0));
        gd::GdArr* _t1026 = (_t1025.kind == gd::GdVal::Kind::Arr) ? _t1025.arr : nullptr;
        uint32_t _len__t1027 = _t1026 ? _t1026->len : 0u;
        for (uint32_t _t1027 = 0; _t1027 < _len__t1027; ++_t1027) {
            gd::GdVal lv_gem = _t1026->data[_t1027];
            (void)([&]() { gd::GdVal _ca[] = {lv_craft}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN_shopEntered_741, _ca, 1); })();
        }
    }
    if (gd::gd_truth(lv_craft)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addToCraftingQueue_745, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onShopEntered_742, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_startFusing_inShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_COG_600)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFusing_748, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getCraftingPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isGem_82, nullptr, 0))) {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_853), SYM_GEN_Gem_2634);
    }
    {
        gd::GdVal _t1028 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
        gd::GdArr* _t1029 = (_t1028.kind == gd::GdVal::Kind::Arr) ? _t1028.arr : nullptr;
        uint32_t _len__t1030 = _t1029 ? _t1029->len : 0u;
        for (uint32_t _t1030 = 0; _t1030 < _len__t1030; ++_t1030) {
            gd::GdVal lv_bonded = _t1029->data[_t1030];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_bonded, SYM_GEN_isGem_82, nullptr, 0))) {
                return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_853), SYM_GEN_Mixed_2635);
            }
        }
    }
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_853), SYM_GEN_NonGem_2636);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_addToCraftingQueue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_combatToTitle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_249, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_646, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_curRecipe) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2637, _ca, 1); })(), gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_startFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delay = (_argc > 0) ? _args[0] : (Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_599));
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_readyToFuse_747, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fuse", 4u)), lv_delay}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callDelayed_1416, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disablePicking_643, nullptr, 0);
        {
            gd::GdVal _t1031 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
            gd::GdArr* _t1032 = (_t1031.kind == gd::GdVal::Kind::Arr) ? _t1031.arr : nullptr;
            uint32_t _len__t1033 = _t1032 ? _t1032->len : 0u;
            for (uint32_t _t1033 = 0; _t1033 < _len__t1033; ++_t1033) {
                gd::GdVal lv_bonded = _t1032->data[_t1033];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_curRecipe, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_bonded}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2638, _ca, 1); })()))))))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bonded, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "disablePicking", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1418, _ca, 3); })();
                    gd::set_prop(gd_ctx, lv_bonded, SYM_GEN_willBeConsumed_604, gd::GdVal::from_bool(true));
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
    return ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedTypeName_751, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTypeDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TYPE_", 5u)), gd::get_index(gd_ctx, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), gd::SYM_keys, nullptr, 0), lv_type)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_DESCR", 6u)))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTranslatedRarity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_234, nullptr, 0)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Item::call_static_fn(gd_ctx, SYM_GEN_getRarityName_754, _ca, 1, _out); return _out; })();
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
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getCombatDisplayAccuracy(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_getDisplayCritChance(const gd::GdVal* _args, int _argc) {
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
    gd::GdVal lv_shopChance = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_shopChance_1585));
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn__physics_process(const gd::GdVal* _args, int _argc) {
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
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN)))))))) {
        lv_scaling = gd::GdVal::from_vec2((lv_shortScale).as_float(), (lv_longScale).as_float());
    }
    else {
        lv_scaling = gd::GdVal::from_vec2((lv_longScale).as_float(), (lv_shortScale).as_float());
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1619));
    gd::GdVal lv_consume = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_consume = gd::gd_coerce_bool(lv_consume);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_739, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Jump_2639))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_772, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_SquishyJump_2640))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.1)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_773, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_VerySquishyJump_2641))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.2)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_773, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Slash_2642))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Stab_2643))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_ReverseStab_2644))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Bonk_2645))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_ReverseBonk_2646))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Sweep_2647))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Block_2563))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL), gd::GdVal::from_float(1.3)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_772, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Chop_2648))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Wave_2649))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Throw_2607))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Scale_2650))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Scale_771, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Squish_2651))))) {
        if (gd::gd_truth(this->f_hasSquishySprite)) {
        }
        else {
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Potion_2652))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Hiss_2653))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Spin_2654))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Tackle_2655))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_DoubleSlash_2656))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Struggle_2657))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_772, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Shoot_2658))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_aniType, gd::get_prop(gd_ctx, Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_865), SYM_GEN_Flash_2659))))) {
    }
    if (gd::gd_truth(lv_consume)) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(6LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playDropSound_147, _ca, 1); })();
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initSpriteMaterial_786, nullptr, 0);
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
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1597))))) {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_hasInventoryDuration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1485, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_reveal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_setRevealed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reveal_794, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_isCrafted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_crafted_instance, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(gd::gd_eq(this->f_crafted_instance, gd::GdVal::from_int(1LL)));
    }
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isCraftedItem_1622, nullptr, 0);
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
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_249, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getItemsInInventoryOfType_opponent_1569, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getItemsInInventoryOfType_1568, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_countAllInInventoryOfType(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_isTypeInInventory(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_isRecipeFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2637, _ca, 1); })(), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_canStartNewRecipe(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBaseItem_256, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isAvailableForCrafting_491, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getRecipes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_checkClassAvailability = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_recipes = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1034 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_recipes_2660));
        gd::GdArr* _t1035 = (_t1034.kind == gd::GdVal::Kind::Arr) ? _t1034.arr : nullptr;
        uint32_t _len__t1036 = _t1035 ? _t1035->len : 0u;
        for (uint32_t _t1036 = 0; _t1036 < _len__t1036; ++_t1036) {
            gd::GdVal lv_recipe = _t1035->data[_t1036];
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_823, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_removeBondedIngredient(const gd::GdVal* _args, int _argc) {
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
gd::GdVal Gd__gd_core_items__Item::fn_removeAllIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_833, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_considerAsBond(const gd::GdVal* _args, int _argc) {
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
            gd::GdVal _t1037 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRecipes_804, nullptr, 0));
            gd::GdArr* _t1038 = (_t1037.kind == gd::GdVal::Kind::Arr) ? _t1037.arr : nullptr;
            uint32_t _len__t1039 = _t1038 ? _t1038->len : 0u;
            for (uint32_t _t1039 = 0; _t1039 < _len__t1039; ++_t1039) {
                gd::GdVal lv_r = _t1038->data[_t1039];
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
    (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createBondVisual_835, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_836, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_812, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, lv_neighbor, SYM_GEN_placedByPlayer_48)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_placedByPlayer))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_833, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_addToBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_823, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_812, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_playBondAnimation(const gd::GdVal* _args, int _argc) {
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
    return ([&]() { gd::GdVal _ca[] = {lv_bondedItem}; return gd::call_method(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2638, _ca, 1); })();
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
        (void)([&]() { gd::GdVal _ca[] = {lv_showLabel}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_lockCombining_820, _ca, 1); })();
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_unlockCombining_819, nullptr, 0);
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
        gd::GdVal _t1040 = gd::gd_iter_seq(gd_ctx.arena, lv_ingredients);
        gd::GdArr* _t1041 = (_t1040.kind == gd::GdVal::Kind::Arr) ? _t1040.arr : nullptr;
        uint32_t _len__t1042 = _t1041 ? _t1041->len : 0u;
        for (uint32_t _t1042 = 0; _t1042 < _len__t1042; ++_t1042) {
            gd::GdVal lv_ingredient = _t1041->data[_t1042];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_ingredient}; return gd::call_method(gd_ctx, lv_candidate, SYM_GEN_hasType_77, _ca, 1); })())) {
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getTextEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_textEffect_2275);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getFusionItemName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_fusedItem_2664), SYM_GEN_getTranslatedName_637, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearSpriteMaterial_775, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_823, _ca, 1); })();
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_715, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Item::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_Normal_2540);
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
        case SYM_GEN_affectedWeapon_944: out = this->f_affectedWeapon; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_light_945: out = this->f_light; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Bow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedWeapon_944: this->f_affectedWeapon = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_light_945: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Bow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_onWeaponAttacked_946: return true;
        case SYM_GEN_combatEnd_129: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Bow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_946: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_combatEnd_129: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_80, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bow::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedWeapon = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_426, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_affectedWeapon, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_affectedWeapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bow::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_combatEnd_129, nullptr, 0, _out); return _out; })();
    this->f_affectedWeapon = gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_EventType_1362: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_EventType);
        case SYM_GEN_ItemMetrics_1363: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_ItemMetrics);
        case SYM_GEN_CharID_1364: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_CharID);
        case SYM_GEN_StaminaResult_1276: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StaminaResult);
        case SYM_GEN_ItemStat_1365: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_ItemStat);
        case SYM_GEN_Rarity_858: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Rarity);
        case SYM_GEN_StuffedClasses_1366: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StuffedClasses);
        case SYM_GEN_Owner_850: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Owner);
        case SYM_GEN_GameMode_1367: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_GameMode);
        case SYM_GEN_Affected_863: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Affected);
        case SYM_GEN_Stack_855: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Stack);
        case SYM_GEN_Tag_854: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Tag);
        case SYM_GEN_Priority_852: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Priority);
        case SYM_GEN_StackChangeType_867: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StackChangeType);
        case SYM_GEN_StatModified_860: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StatModified);
        case SYM_GEN_FaceDirection_859: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_FaceDirection);
        case SYM_GEN_Classes_1368: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Classes);
        case SYM_GEN_Classes_Full_1369: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Classes_Full);
        case SYM_GEN_Type_851: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Type);
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
        case SYM_GEN_EventType_1362: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_EventType); return true;
        case SYM_GEN_ItemMetrics_1363: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_ItemMetrics); return true;
        case SYM_GEN_CharID_1364: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_CharID); return true;
        case SYM_GEN_StaminaResult_1276: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StaminaResult); return true;
        case SYM_GEN_ItemStat_1365: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_ItemStat); return true;
        case SYM_GEN_Rarity_858: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Rarity); return true;
        case SYM_GEN_StuffedClasses_1366: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StuffedClasses); return true;
        case SYM_GEN_Owner_850: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Owner); return true;
        case SYM_GEN_GameMode_1367: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_GameMode); return true;
        case SYM_GEN_Affected_863: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Affected); return true;
        case SYM_GEN_Stack_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Stack); return true;
        case SYM_GEN_Tag_854: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Tag); return true;
        case SYM_GEN_Priority_852: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Priority); return true;
        case SYM_GEN_StackChangeType_867: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StackChangeType); return true;
        case SYM_GEN_StatModified_860: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_StatModified); return true;
        case SYM_GEN_FaceDirection_859: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_FaceDirection); return true;
        case SYM_GEN_Classes_1368: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Classes); return true;
        case SYM_GEN_Classes_Full_1369: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Classes_Full); return true;
        case SYM_GEN_Type_851: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreConst_Type); return true;
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
        case SYM_GEN_truth_1356: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_getStacks_1018: out = sf_getStacks(gd_ctx, args, argc); return true;
        case SYM_GEN_getBuffs_1357: out = sf_getBuffs(gd_ctx, args, argc); return true;
        case SYM_GEN_getDebuffs_1358: out = sf_getDebuffs(gd_ctx, args, argc); return true;
        case SYM_GEN_isBuff_1002: out = sf_isBuff(gd_ctx, args, argc); return true;
        case SYM_GEN_isDebuff_1359: out = sf_isDebuff(gd_ctx, args, argc); return true;
        case SYM_GEN_isStack_1360: out = sf_isStack(gd_ctx, args, argc); return true;
        case SYM_GEN_numStackTypes_1361: out = sf_numStackTypes(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreConst::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_truth_1356: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_getStacks_1018: out = sf_getStacks(gd_ctx, args, argc); return true;
        case SYM_GEN_getBuffs_1357: out = sf_getBuffs(gd_ctx, args, argc); return true;
        case SYM_GEN_getDebuffs_1358: out = sf_getDebuffs(gd_ctx, args, argc); return true;
        case SYM_GEN_isBuff_1002: out = sf_isBuff(gd_ctx, args, argc); return true;
        case SYM_GEN_isDebuff_1359: out = sf_isDebuff(gd_ctx, args, argc); return true;
        case SYM_GEN_isStack_1360: out = sf_isStack(gd_ctx, args, argc); return true;
        case SYM_GEN_numStackTypes_1361: out = sf_numStackTypes(gd_ctx, args, argc); return true;
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
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Block_2563)})), ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreConst::call_static_fn(gd_ctx, SYM_GEN_getBuffs_1357, nullptr, 0, _out); return _out; })()), ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreConst::call_static_fn(gd_ctx, SYM_GEN_getDebuffs_1358, nullptr, 0, _out); return _out; })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_getBuffs(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Lucky_2569), gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Heat_2572), gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_getDebuffs(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Poison_2566), gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Cold_2573), gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_isBuff(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Block_2563)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Heat_2572))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_isDebuff(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Poison_2566)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Cold_2573))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_isStack(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Block_2563)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv__type, gd::get_prop(gd_ctx, Gd__gd_core__CoreConst::get_static_const_or_enum(gd_ctx, SYM_GEN_EventType_1362), SYM_GEN_Cold_2573))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreConst::sf_numStackTypes(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::call_method(gd_ctx, ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreConst::call_static_fn(gd_ctx, SYM_GEN_getStacks_1018, nullptr, 0, _out); return _out; })(), gd::SYM_size, nullptr, 0);
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
        case SYM_GEN_DictSorter_1712: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil__INNER__DictSorter);
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
        case SYM_GEN_rng_1373: out = this->f_rng; return true;
        case SYM_GEN__ctx_1321: out = this->f__ctx; return true;
        case SYM_GEN_DictSorter_1712: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil__INNER__DictSorter); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rng_1373: this->f_rng = val; return true;
        case SYM_GEN__ctx_1321: this->f__ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_roll_1636: return true;
        case SYM_GEN_flip_1637: return true;
        case SYM_GEN_flipPercent_1638: return true;
        case SYM_GEN_flipRound_1639: return true;
        case SYM_GEN_flipWeighted_1640: return true;
        case SYM_GEN_pickRandomElement_1648: return true;
        case SYM_GEN_getArrayElement_1699: return true;
        case SYM_GEN_callNextFrame_1701: return true;
        case SYM_GEN_callDelayed_1416: return true;
        case SYM_GEN_callDelayed_process_1702: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_truth_1356: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_tile_data_1691: out = sf_vec2_tile_data(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_less_yx_1692: out = sf_vec2_less_yx(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAdd_1693: out = sf_dictAdd(gd_ctx, args, argc); return true;
        case SYM_GEN_dictSub_1694: out = sf_dictSub(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAddDict_1695: out = sf_dictAddDict(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAppend_1696: out = sf_dictAppend(gd_ctx, args, argc); return true;
        case SYM_GEN_dictErase_1697: out = sf_dictErase(gd_ctx, args, argc); return true;
        case SYM_GEN_sortDict_1698: out = sf_sortDict(gd_ctx, args, argc); return true;
        case SYM_GEN_roll_1636: out = fn_roll(args, argc); return true;
        case SYM_GEN_flip_1637: out = fn_flip(args, argc); return true;
        case SYM_GEN_flipPercent_1638: out = fn_flipPercent(args, argc); return true;
        case SYM_GEN_flipRound_1639: out = fn_flipRound(args, argc); return true;
        case SYM_GEN_flipWeighted_1640: out = fn_flipWeighted(args, argc); return true;
        case SYM_GEN_pickRandomElement_1648: out = fn_pickRandomElement(args, argc); return true;
        case SYM_GEN_getArrayElement_1699: out = fn_getArrayElement(args, argc); return true;
        case SYM_GEN_changeTimer_1700: out = sf_changeTimer(gd_ctx, args, argc); return true;
        case SYM_GEN_callNextFrame_1701: out = fn_callNextFrame(args, argc); return true;
        case SYM_GEN_callDelayed_1416: out = fn_callDelayed(args, argc); return true;
        case SYM_GEN_callDelayed_process_1702: out = fn_callDelayed_process(args, argc); return true;
        case SYM_GEN_arrayAsIndexDict_1703: out = sf_arrayAsIndexDict(gd_ctx, args, argc); return true;
        case SYM_GEN_invertDictionary_1704: out = sf_invertDictionary(gd_ctx, args, argc); return true;
        case SYM_GEN_filterDuplicates_1705: out = sf_filterDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_countDuplicates_1706: out = sf_countDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_flatten_1707: out = sf_flatten(gd_ctx, args, argc); return true;
        case SYM_GEN_rotDif_1708: out = sf_rotDif(gd_ctx, args, argc); return true;
        case SYM_GEN_isItemDescriptor_1709: out = sf_isItemDescriptor(gd_ctx, args, argc); return true;
        case SYM_GEN_eassert_1710: out = sf_eassert(gd_ctx, args, argc); return true;
        case SYM_GEN_eprint_1711: out = sf_eprint(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_truth_1356: out = sf_truth(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_tile_data_1691: out = sf_vec2_tile_data(gd_ctx, args, argc); return true;
        case SYM_GEN_vec2_less_yx_1692: out = sf_vec2_less_yx(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAdd_1693: out = sf_dictAdd(gd_ctx, args, argc); return true;
        case SYM_GEN_dictSub_1694: out = sf_dictSub(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAddDict_1695: out = sf_dictAddDict(gd_ctx, args, argc); return true;
        case SYM_GEN_dictAppend_1696: out = sf_dictAppend(gd_ctx, args, argc); return true;
        case SYM_GEN_dictErase_1697: out = sf_dictErase(gd_ctx, args, argc); return true;
        case SYM_GEN_sortDict_1698: out = sf_sortDict(gd_ctx, args, argc); return true;
        case SYM_GEN_changeTimer_1700: out = sf_changeTimer(gd_ctx, args, argc); return true;
        case SYM_GEN_arrayAsIndexDict_1703: out = sf_arrayAsIndexDict(gd_ctx, args, argc); return true;
        case SYM_GEN_invertDictionary_1704: out = sf_invertDictionary(gd_ctx, args, argc); return true;
        case SYM_GEN_filterDuplicates_1705: out = sf_filterDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_countDuplicates_1706: out = sf_countDuplicates(gd_ctx, args, argc); return true;
        case SYM_GEN_flatten_1707: out = sf_flatten(gd_ctx, args, argc); return true;
        case SYM_GEN_rotDif_1708: out = sf_rotDif(gd_ctx, args, argc); return true;
        case SYM_GEN_isItemDescriptor_1709: out = sf_isItemDescriptor(gd_ctx, args, argc); return true;
        case SYM_GEN_eassert_1710: out = sf_eassert(gd_ctx, args, argc); return true;
        case SYM_GEN_eprint_1711: out = sf_eprint(gd_ctx, args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {lv_v}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_truth_1356, _ca, 1); })();
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
    { gd::GdVal _t1043 = lv_dict; gd::GdVal _t1044 = lv_key; gd::set_index(gd_ctx, _t1043, _t1044, lv_newVal); }
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
        { gd::GdVal _t1045 = lv_dict; gd::GdVal _t1046 = lv_key; gd::set_index(gd_ctx, _t1045, _t1046, lv_val2); }
    }
    return lv_val2;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_dictAddDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_dict2 = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1047 = gd::gd_iter_seq(gd_ctx.arena, lv_dict2);
        gd::GdArr* _t1048 = (_t1047.kind == gd::GdVal::Kind::Arr) ? _t1047.arr : nullptr;
        uint32_t _len__t1049 = _t1048 ? _t1048->len : 0u;
        for (uint32_t _t1049 = 0; _t1049 < _len__t1049; ++_t1049) {
            gd::GdVal lv_key = _t1048->data[_t1049];
            (void)([&]() { gd::GdVal _ca[] = {lv_dict1, lv_key, gd::get_index(gd_ctx, lv_dict2, lv_key)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreUtil::call_static_fn(gd_ctx, SYM_GEN_dictAdd_1693, _ca, 3, _out); return _out; })();
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
        { gd::GdVal _t1050 = lv_dict; gd::GdVal _t1051 = lv_key; gd::set_index(gd_ctx, _t1050, _t1051, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_value}))); }
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
    return ([&]() { gd::GdVal _ca[] = {lv_maximum}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_roll_1636, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(0.5));
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_flip_1637, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipPercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_flipPercent_1638, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipRound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_flipRound_1639, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_flipWeighted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_weights = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_weights}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_flipWeighted_1640, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_pickRandomElement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_array}; return gd::call_method(gd_ctx, this->f_rng, SYM_GEN_pickRandomElement_1648, _ca, 1); })();
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
    gd::GdVal lv_timeLeft = gd::call_method(gd_ctx, lv_timer, SYM_GEN_get_time_left_1682, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_t, lv_timeLeft)}; return gd::call_method(gd_ctx, lv_timer, SYM_GEN_start_1683, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callNextFrame(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_arguments}; return gd::call_method(gd_ctx, this->f__ctx, SYM_GEN_connectIdleFrameOnce_1421, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callDelayed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_delay, lv_binds}; return gd::call_method(gd_ctx, this->f__ctx, SYM_GEN_callDelayed_1416, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::fn_callDelayed_process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_methodName, lv_delay, lv_binds}; return gd::call_method(gd_ctx, this->f__ctx, SYM_GEN_callDelayed_1416, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_arrayAsIndexDict(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_invertedDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1052 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, lv_array, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t1053 = (_t1052.kind == gd::GdVal::Kind::Arr) ? _t1052.arr : nullptr;
        uint32_t _len__t1054 = _t1053 ? _t1053->len : 0u;
        for (uint32_t _t1054 = 0; _t1054 < _len__t1054; ++_t1054) {
            gd::GdVal lv_i = _t1053->data[_t1054];
            { gd::GdVal _t1055 = lv_invertedDict; gd::GdVal _t1056 = gd::get_index(gd_ctx, lv_array, lv_i); gd::set_index(gd_ctx, _t1055, _t1056, lv_i); }
        }
    }
    return lv_invertedDict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_invertDictionary(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_invertedDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1057 = gd::gd_iter_seq(gd_ctx.arena, lv_dict);
        gd::GdArr* _t1058 = (_t1057.kind == gd::GdVal::Kind::Arr) ? _t1057.arr : nullptr;
        uint32_t _len__t1059 = _t1058 ? _t1058->len : 0u;
        for (uint32_t _t1059 = 0; _t1059 < _len__t1059; ++_t1059) {
            gd::GdVal lv_key = _t1058->data[_t1059];
            { gd::GdVal _t1060 = lv_invertedDict; gd::GdVal _t1061 = gd::get_index(gd_ctx, lv_dict, lv_key); gd::set_index(gd_ctx, _t1060, _t1061, lv_key); }
        }
    }
    return lv_invertedDict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_filterDuplicates(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_dict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t1062 = gd::gd_iter_seq(gd_ctx.arena, lv_arr);
        gd::GdArr* _t1063 = (_t1062.kind == gd::GdVal::Kind::Arr) ? _t1062.arr : nullptr;
        uint32_t _len__t1064 = _t1063 ? _t1063->len : 0u;
        for (uint32_t _t1064 = 0; _t1064 < _len__t1064; ++_t1064) {
            gd::GdVal lv_a = _t1063->data[_t1064];
            { gd::GdVal _t1065 = lv_dict; gd::GdVal _t1066 = lv_a; gd::set_index(gd_ctx, _t1065, _t1066, gd::GdVal::from_bool(true)); }
        }
    }
    return gd::call_method(gd_ctx, lv_dict, gd::SYM_keys, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_countDuplicates(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_before = gd::call_method(gd_ctx, lv_arr, gd::SYM_size, nullptr, 0);
    gd::GdVal lv_filtered = ([&]() { gd::GdVal _ca[] = {lv_arr}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreUtil::call_static_fn(gd_ctx, SYM_GEN_filterDuplicates_1705, _ca, 1, _out); return _out; })();
    return gd::gd_sub(lv_before, gd::call_method(gd_ctx, lv_filtered, gd::SYM_size, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil::sf_flatten(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_arr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_flattened = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1067 = gd::gd_iter_seq(gd_ctx.arena, lv_arr);
        gd::GdArr* _t1068 = (_t1067.kind == gd::GdVal::Kind::Arr) ? _t1067.arr : nullptr;
        uint32_t _len__t1069 = _t1068 ? _t1068->len : 0u;
        for (uint32_t _t1069 = 0; _t1069 < _len__t1069; ++_t1069) {
            gd::GdVal lv_inner = _t1068->data[_t1069];
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
        case SYM_GEN_numIngredients_1760: return gd::GdVal::from_float(5.0);
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
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_affectedWeapon_944: out = this->f_affectedWeapon; return true;
        case SYM_GEN_stacksNeeded_1761: out = this->f_stacksNeeded; return true;
        case SYM_GEN_healthNeeded_1762: out = this->f_healthNeeded; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_numIngredients_1760: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__DjinnLamp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1292: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_affectedWeapon_944: this->f_affectedWeapon = val; return true;
        case SYM_GEN_stacksNeeded_1761: this->f_stacksNeeded = val; return true;
        case SYM_GEN_healthNeeded_1762: this->f_healthNeeded = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DjinnLamp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_checkStacks_1763: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__DjinnLamp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_checkStacks_1763: out = fn_checkStacks(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_affectedWeapon = gd::GdVal::null();
    gd::GdVal lv_affectedItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        this->f_affectedWeapon = gd::get_index(gd_ctx, lv_affectedItems, gd::GdVal::from_int(0LL));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_block_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_healed", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkStacks", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
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
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getBlock_202, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getSpikes_1203, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::gd_sub(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getCurrentHealth_1134, nullptr, 0), gd::GdVal::from_int(1LL)), this->f_healthNeeded), gd::gd_coerce_float(this->f_healthNeeded)));
    lv_progress = gd::gd_div(gd_ctx, lv_progress, Gd__gd_core__DjinnLamp::get_static_const_or_enum(gd_ctx, SYM_GEN_numIngredients_1760));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_changeAmount, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_progress, gd::GdVal::from_float(0.9999))))) {
            this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_LoggingMode_1506), SYM_GEN_Delayed_2588)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_setLoggingMode_1495, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useBlock_205, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_335, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_348, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_healthNeeded, gd::GdVal::from_obj(this), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_loseHealth_1137, _ca, 3); })();
            gd::GdVal lv_bonusDamage = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusDamage}; return gd::call_method(gd_ctx, this->f_affectedWeapon, SYM_GEN_addBonusDamage_159, _ca, 1); })();
            gd::GdVal lv_dmgBuffEvent = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), this->f_affectedWeapon, lv_bonusDamage, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_playerId_1042), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_createEvent_DamageBuff_1341, _ca, 5); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_dmgBuffEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_logEvent_1324, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_flushLoggingQueue_1498, nullptr, 0);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numLucky = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0);
    gd::GdVal lv_numSpikes = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getSpikes_1203, nullptr, 0);
    gd::GdVal lv_numMana = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numLucky, lv_numSpikes)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numLucky, lv_numMana)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
        }
    }
    else {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numSpikes, lv_numMana)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DjinnLamp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_stacksNeeded = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
    this->f_healthNeeded = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0);
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
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN_onFusingAsCatalystFinished_839: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Hammer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onFusingAsCatalystFinished_839: out = fn_onFusingAsCatalystFinished(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_328, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Hammer::fn_onFusingAsCatalystFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN_onFusingAsCatalystFinished_839, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_774, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Hammer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_buffsActive_1776: out = this->f_buffsActive; return true;
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_damReduction_1777: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__LeatherHelm::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffsActive_1776: this->f_buffsActive = val; return true;
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_damReduction_1777: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LeatherHelm::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1811: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreCombatStart_123: return true;
        case SYM_GEN_getBuffDur_1812: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__LeatherHelm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1811: out = fn_getStunProtectChance(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_123: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_getBuffDur_1812: out = fn_getBuffDur(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LeatherHelm::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_getStunProtectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeCritResistance_1153, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStunProtectChance_1811, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeStunResistance_1156, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    this->f_buffsActive = gd::gd_add(gd_ctx, this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBuffDur_1812, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_getBuffDur(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    this->f_buffsActive = gd::gd_sub(this->f_buffsActive, gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LeatherHelm::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffsActive = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffsActive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_damReduction = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onFoodActivated_1860: return true;
        case SYM_GEN_getCraftingOffset_846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Pandamonium::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onFoodActivated_1860: out = fn_onFoodActivated(args, argc); return true;
        case SYM_GEN_getCraftingOffset_846: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1070 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1071 = (_t1070.kind == gd::GdVal::Kind::Arr) ? _t1070.arr : nullptr;
        uint32_t _len__t1072 = _t1071 ? _t1071->len : 0u;
        for (uint32_t _t1072 = 0; _t1072 < _len__t1072; ++_t1072) {
            gd::GdVal lv_item = _t1071->data[_t1072];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onFoodActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_onFoodActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1073 = lv_forDirection;
        if (gd::gd_eq(_t1073, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        }
        else if (gd::gd_eq(_t1073, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1073, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1073, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pandamonium::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__RainbowGoobertRanger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RainbowGoobertRanger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RainbowGoobertRanger::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 1); })();
    {
        gd::GdVal _t1074 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1075 = (_t1074.kind == gd::GdVal::Kind::Arr) ? _t1074.arr : nullptr;
        uint32_t _len__t1076 = _t1075 ? _t1075->len : 0u;
        for (uint32_t _t1076 = 0; _t1076 < _len__t1076; ++_t1076) {
            gd::GdVal lv_item = _t1075->data[_t1076];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_266, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RainbowGoobertRanger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_getStunProtectChance_1811: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core__StoneHelm::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getStunProtectChance_1811: out = fn_getStunProtectChance(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StoneHelm::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherHelm::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StoneHelm::fn_getStunProtectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneHelm::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onCombatStart_930, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneHelm::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__VampiricArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__VampiricArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__VampiricArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_326, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_326, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_dmgBonusActive_907: out = this->f_dmgBonusActive; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::get_prop(prop, out);
}
bool Gd__gd_core_items__ArtifactStoneHeat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dmgBonusActive_907: this->f_dmgBonusActive = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ArtifactStoneHeat::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onHeatChanged_909: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_preHit_903: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Stone::has_own_method(m);
}
bool Gd__gd_core_items__ArtifactStoneHeat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_909: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_preHit_903: out = fn_preHit(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_heat_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHeatChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    this->f_dmgBonusActive = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_dmgBonusActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0))))) {
            this->f_dmgBonusActive = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            {
                gd::GdVal _t1077 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
                gd::GdArr* _t1078 = (_t1077.kind == gd::GdVal::Kind::Arr) ? _t1077.arr : nullptr;
                uint32_t _len__t1079 = _t1078 ? _t1078->len : 0u;
                for (uint32_t _t1079 = 0; _t1079 < _len__t1079; ++_t1079) {
                    gd::GdVal lv_weapon = _t1078->data[_t1079];
                    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, lv_weapon, SYM_GEN_addBonusDamage_159, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ArtifactStoneHeat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Stone::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_gemColor_991: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.7)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_gemColor_991: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__BurningCoal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BurningCoal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canBlock_289: return true;
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_preAttack_992: return true;
        case SYM_GEN_prepareArmor_979: return true;
        case SYM_GEN_combatStartArmor_982: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_988: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__BurningCoal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canBlock_289: out = fn_canBlock(args, argc); return true;
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_preAttack_992: out = fn_preAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_979: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_combatStartArmor_982: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_988: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_deal_damage_early", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preAttack", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Cold_2573), gd::gd_round(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0)))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeResistStacks_1022, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningCoal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_critBonusActive_1733: out = this->f_critBonusActive; return true;
        case SYM_GEN_poisonThreshold_1734: out = this->f_poisonThreshold; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__DeathScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_critBonusActive_1733: this->f_critBonusActive = val; return true;
        case SYM_GEN_poisonThreshold_1734: this->f_poisonThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DeathScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onOpponentPoisonChanged_1735: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__DeathScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1735: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Poison_2566)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_84, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_poison_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentPoisonChanged", 23u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    {
        gd::GdVal _t1080 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1081 = (_t1080.kind == gd::GdVal::Kind::Arr) ? _t1080.arr : nullptr;
        uint32_t _len__t1082 = _t1081 ? _t1081->len : 0u;
        for (uint32_t _t1082 = 0; _t1082 < _len__t1082; ++_t1082) {
            gd::GdVal lv_item = _t1081->data[_t1082];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Poison_2566), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_301, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getPoison_1209, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_critBonusActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, this->f_poisonThreshold)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCritChancePercent_179, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeathScythe::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_poisonThreshold = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DeathScythe(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__DeathScythe>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__DeathScythe = {CLS_Gd__gd_core_items__DeathScythe, "DeathScythe", "res://gd_core_items/DeathScythe.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__DeathScythe, &Gd__gd_core_items__DeathScythe::get_static_prop_fn, &Gd__gd_core_items__DeathScythe::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofLight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regenOnActivate = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofLight::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofLight; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_1924: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.850098), gd::GdVal::from_float(0.400391)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_regenOnActivate_1935: out = this->f_regenOnActivate; return true;
        case SYM_GEN_amuletColor_1924: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regenOnActivate_1935: this->f_regenOnActivate = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemActivated_934: return true;
        case SYM_GEN_onRegenChanged_1795: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_934: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_onRegenChanged_1795: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    {
        gd::GdVal _t1083 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1084 = (_t1083.kind == gd::GdVal::Kind::Arr) ? _t1083.arr : nullptr;
        uint32_t _len__t1085 = _t1084 ? _t1084->len : 0u;
        for (uint32_t _t1085 = 0; _t1085 < _len__t1085; ++_t1085) {
            gd::GdVal lv_item = _t1084->data[_t1085];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1453), SYM_GEN_hasType_77, _ca, 1); })())) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance2_172, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenOnActivate, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    else {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenOnActivate, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_regenOnActivate = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofLight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofLight>(&ctx); }
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
        case SYM_GEN_permDamBonus_993: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Axe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_permDamBonus_993: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Axe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Axe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Axe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
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
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_damFactor_1799: out = this->f_damFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Bomb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_damFactor_1799: this->f_damFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Bomb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Bomb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Bomb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Bomb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_LoggingMode_1506), SYM_GEN_Delayed_2588)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_setLoggingMode_1495, _ca, 1); })();
        gd::GdVal lv_removedBuffs = gd::GdVal::from_int(0LL);
        {
            gd::GdVal _t1086 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0));
            gd::GdArr* _t1087 = (_t1086.kind == gd::GdVal::Kind::Arr) ? _t1086.arr : nullptr;
            uint32_t _len__t1088 = _t1087 ? _t1087->len : 0u;
            for (uint32_t _t1088 = 0; _t1088 < _len__t1088; ++_t1088) {
                gd::GdVal lv_buff = _t1087->data[_t1088];
                gd::GdVal lv_numStacks = ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getStacks_1018, _ca, 1); })();
                lv_removedBuffs = gd::gd_add(gd_ctx, lv_removedBuffs, lv_numStacks);
                (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_numStacks, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_useStacks_1199, _ca, 3); })();
            }
        }
        (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_flushLoggingQueue_1498, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(this->f_damFactor), lv_removedBuffs)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
        gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1577);
        gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_219, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Bomb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damFactor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
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
        case SYM_GEN_spikesAcc_2012: out = this->f_spikesAcc; return true;
        case SYM_GEN_affectedItemsDict_2013: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        case SYM_GEN_spikesNeeded_2014: out = this->f_spikesNeeded; return true;
        case SYM_GEN_heatForSpikes_2015: out = this->f_heatForSpikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesAcc_2012: this->f_spikesAcc = val; return true;
        case SYM_GEN_affectedItemsDict_2013: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_spikes_894: this->f_spikes = val; return true;
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        case SYM_GEN_spikesNeeded_2014: this->f_spikesNeeded = val; return true;
        case SYM_GEN_heatForSpikes_2015: this->f_heatForSpikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onSpikesChanged_940: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BurningSpikes::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_940: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Spikes_2564)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_84, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_spikesAcc = gd::GdVal::from_int(0LL);
    this->f_affectedItemsDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_arrayAsIndexDict_1703, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1453), this->f_affectedItemsDict))) : gd::GdVal::from_bool(false)))) {
        this->f_spikesAcc = gd::gd_add(gd_ctx, this->f_spikesAcc, lv_amount);
        gd::GdVal lv_numProccs = gd::gd_div(gd_ctx, this->f_spikesAcc, this->f_spikesNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_heatForSpikes, lv_numProccs)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
            this->f_spikesAcc = gd::gd_mod(gd_ctx, this->f_spikesAcc, this->f_spikesNeeded);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BurningSpikes::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_spikesNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikest", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_heatForSpikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_buffs_1044: out = this->f_buffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffs_1044: this->f_buffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2049: return true;
        case SYM_GEN_doEliminatedEffect_2051: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackQueen::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2049: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2051: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        return ([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_371, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_371, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackQueen::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_328, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackQueen::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_chargeCells1_2036: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(3LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(2LL))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float())}));
        case SYM_GEN_chargeCells2_2037: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(2LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(2LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float())}));
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
        case SYM_GEN_hasActivated_1810: out = this->f_hasActivated; return true;
        case SYM_GEN_speedMalus_2084: out = this->f_speedMalus; return true;
        case SYM_GEN_cdAdvanceBase_2085: out = this->f_cdAdvanceBase; return true;
        case SYM_GEN_cdAdvanceBonus_2086: out = this->f_cdAdvanceBonus; return true;
        case SYM_GEN_healthThreshold_1758: out = this->f_healthThreshold; return true;
        case SYM_GEN_chargeCells1_2036: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_chargeCells2_2037: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1810: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_speedMalus_2084: this->f_speedMalus = val; return true;
        case SYM_GEN_cdAdvanceBase_2085: this->f_cdAdvanceBase = val; return true;
        case SYM_GEN_cdAdvanceBonus_2086: this->f_cdAdvanceBonus = val; return true;
        case SYM_GEN_healthThreshold_1758: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_lightning_287: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onDamaged_1759: return true;
        case SYM_GEN_emitCharge_1962: return true;
        case SYM_GEN_onChargeEnteredCell_1963: return true;
        case SYM_GEN_chargedItemStatChange_1964: return true;
        case SYM_GEN_getTextureSize_777: return true;
        case SYM_GEN_getSpriteOffset_779: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ConTrapTron::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_lightning_287: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1759: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_emitCharge_1962: out = fn_emitCharge(args, argc); return true;
        case SYM_GEN_onChargeEnteredCell_1963: out = fn_onChargeEnteredCell(args, argc); return true;
        case SYM_GEN_chargedItemStatChange_1964: out = fn_chargedItemStatChange(args, argc); return true;
        case SYM_GEN_getTextureSize_777: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN_getSpriteOffset_779: out = fn_getSpriteOffset(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_294, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_reactsToCharges_297, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    gd::GdVal lv_item = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_426, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_speedMalus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_272, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRelativeHealth_300, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_emitCharge_1962, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charge_emitted", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 3); })();
        gd::GdVal lv_item = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_426, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
            gd::GdVal lv_cdAdvance = this->f_cdAdvanceBase;
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_80, nullptr, 0))))) {
                lv_cdAdvance = gd::gd_add(gd_ctx, lv_cdAdvance, this->f_cdAdvanceBonus);
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_cdAdvance}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_advanceCooldownSeconds_145, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_emitCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speedFactor = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_event = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), Gd__gd_core_items__Exclusive__ConTrapTron::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells1_2036), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_318, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), Gd__gd_core_items__Exclusive__ConTrapTron::get_static_const_or_enum(gd_ctx, SYM_GEN_chargeCells2_2037), lv_speedFactor, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sendCharge_318, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_onChargeEnteredCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_charge, lv_cellIndex, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeChargedItemStat_324, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ConTrapTron::fn_chargedItemStatChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_195, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedMalus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_cdAdvanceBase = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdadvance_base", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_cdAdvanceBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cdadvance_bonus", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healtht", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
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
        case SYM_GEN_debuffsNeeded_2110: out = this->f_debuffsNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_debuffsNeeded_2110: this->f_debuffsNeeded = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_debuffsChanged_2111: return true;
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_debuffsChanged_2111: out = fn_debuffsChanged(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DivinePotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffsChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterDebuffs_373, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_debuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_919, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getDebuffStacks_1196, nullptr, 0), this->f_debuffsNeeded)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1752, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DivinePotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_debuffsNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
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
        case SYM_GEN_gemColor_991: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.466766), gd::GdVal::from_float(0.625994), gd::GdVal::from_float(0.742188)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_stunReadyTime_2142: out = this->f_stunReadyTime; return true;
        case SYM_GEN_debuffResistChance_2143: out = this->f_debuffResistChance; return true;
        case SYM_GEN_debuffResistTimer_2144: out = this->f_debuffResistTimer; return true;
        case SYM_GEN_stunCd_2145: out = this->f_stunCd; return true;
        case SYM_GEN_gemColor_991: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stunReadyTime_2142: this->f_stunReadyTime = val; return true;
        case SYM_GEN_debuffResistChance_2143: this->f_debuffResistChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_debuffResistTimer_2144: this->f_debuffResistTimer = val; return true;
        case SYM_GEN_stunCd_2145: this->f_stunCd = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_onAttack_1956: return true;
        case SYM_GEN_prepareArmor_979: return true;
        case SYM_GEN_combatStartArmor_982: return true;
        case SYM_GEN_removeDebuffResistance_2146: return true;
        case SYM_GEN_combatEndArmor_985: return true;
        case SYM_GEN_hasCooldown_93: return true;
        case SYM_GEN_combatStartInventory_980: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_988: return true;
        case SYM_GEN_hasInventoryDuration_793: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1956: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_979: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_combatStartArmor_982: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_removeDebuffResistance_2146: out = fn_removeDebuffResistance(args, argc); return true;
        case SYM_GEN_combatEndArmor_985: out = fn_combatEndArmor(args, argc); return true;
        case SYM_GEN_hasCooldown_93: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_combatStartInventory_980: out = fn_combatStartInventory(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_988: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN_hasInventoryDuration_793: out = fn_hasInventoryDuration(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ElephantRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1378), this->f_stunReadyTime)))) {
            this->f_stunReadyTime = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1378), this->f_stunCd);
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_328, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_debuffResistChance = gd::gd_coerce_float(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {this->f_debuffResistChance}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDebuffResistChances_1200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_resist", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_debuffResistTimer, SYM_GEN_start_1683, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_removeDebuffResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_debuffResistChance)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDebuffResistChances_1200, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatEndArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_debuffResistTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ElephantRune::fn_combatStartInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_debuffResistTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "DebuffResistTimer", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "removeDebuffResistance", 22u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_stunCd = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldown_98, nullptr, 0);
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
        case SYM_GEN_cleanses_1802: out = this->f_cleanses; return true;
        case SYM_GEN_potionSpeed_2164: out = this->f_potionSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Shelly::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cleanses_1802: this->f_cleanses = val; return true;
        case SYM_GEN_potionSpeed_2164: this->f_potionSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Shelly::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onPrepare_121: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Shelly::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cleanses}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDebuffProtectionChance_1267, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_potionSpeed, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Shelly::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cleanses = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffs", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_potionSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_active_2128: out = this->f_active; return true;
        case SYM_GEN_blockAmp_2189: out = this->f_blockAmp; return true;
        case SYM_GEN_damReduction_1777: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_2128: this->f_active = val; return true;
        case SYM_GEN_blockAmp_2189: this->f_blockAmp = val; return true;
        case SYM_GEN_damReduction_1777: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemAdded_435: return true;
        case SYM_GEN_onItemRemoved_436: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_checkItems_2127: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_preTakeDamage_1848: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FullBodyProtection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemAdded_435: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_436: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_checkItems_2127: out = fn_checkItems(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preTakeDamage_1848: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_435, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2127, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_436, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2127, nullptr, 0);
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
        gd::GdVal _t1089 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t1090 = (_t1089.kind == gd::GdVal::Kind::Arr) ? _t1089.arr : nullptr;
        uint32_t _len__t1091 = _t1090 ? _t1090->len : 0u;
        for (uint32_t _t1091 = 0; _t1091 < _len__t1091; ++_t1091) {
            gd::GdVal lv_item = _t1090->data[_t1091];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Armor_2750)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
                lv_numArmor = gd::gd_add(gd_ctx, lv_numArmor, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Helmet_2751)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
                lv_numHelmets = gd::gd_add(gd_ctx, lv_numHelmets, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Shoes_2752)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_289, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1092 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1093 = (_t1092.kind == gd::GdVal::Kind::Arr) ? _t1092.arr : nullptr;
        uint32_t _len__t1094 = _t1093 ? _t1093->len : 0u;
        for (uint32_t _t1094 = 0; _t1094 < _len__t1094; ++_t1094) {
            gd::GdVal lv_item = _t1093->data[_t1094];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Block_2563), this->f_blockAmp}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_301, _ca, 2); })();
        }
    }
    if (gd::gd_truth(this->f_active)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preTakeDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttackOrEffect_1469, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_applyDamageReduction_1433, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FullBodyProtection::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_blockAmp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damreduction", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_flatDam_2211: out = this->f_flatDam; return true;
        case SYM_GEN_damFactor_1799: out = this->f_damFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeroShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_flatDam_2211: this->f_flatDam = val; return true;
        case SYM_GEN_damFactor_1799: this->f_damFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeroShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__WoodenBuckler::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeroShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeroShield::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1095 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1096 = (_t1095.kind == gd::GdVal::Kind::Arr) ? _t1095.arr : nullptr;
        uint32_t _len__t1097 = _t1096 ? _t1096->len : 0u;
        for (uint32_t _t1097 = 0; _t1097 < _len__t1097; ++_t1097) {
            gd::GdVal lv_item = _t1096->data[_t1097];
            (void)([&]() { gd::GdVal _ca[] = {this->f_flatDam}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_damFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_304, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeroShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__WoodenBuckler::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_flatDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_damFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damfactor", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Crown::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__KingCrown::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Crown::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__KingCrown::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Crown::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gemPower = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gempower", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t1098 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_495, nullptr, 0));
        gd::GdArr* _t1099 = (_t1098.kind == gd::GdVal::Kind::Arr) ? _t1098.arr : nullptr;
        uint32_t _len__t1100 = _t1099 ? _t1099->len : 0u;
        for (uint32_t _t1100 = 0; _t1100 < _len__t1100; ++_t1100) {
            gd::GdVal lv_gem = _t1099->data[_t1100];
            (void)([&]() { gd::GdVal _ca[] = {lv_gemPower}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN_changeGemPower_970, _ca, 1); })();
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Crown::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeBuffProtectStacks_1167, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_Normal_2540), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingCrown::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Crown::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MagicBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Mana_2570)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_84, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicBadge::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1101 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1102 = (_t1101.kind == gd::GdVal::Kind::Arr) ? _t1101.arr : nullptr;
        uint32_t _len__t1103 = _t1102 ? _t1102->len : 0u;
        for (uint32_t _t1103 = 0; _t1103 < _len__t1103; ++_t1103) {
            gd::GdVal lv_item = _t1102->data[_t1103];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Mana_2570), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_194, _ca, 2); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_mana = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_totalBlockRemoval_1885: out = this->f_totalBlockRemoval; return true;
        case SYM_GEN_blockRemoval_1801: out = this->f_blockRemoval; return true;
        case SYM_GEN_missDamage_2311: out = this->f_missDamage; return true;
        case SYM_GEN_heatNeeded_1784: out = this->f_heatNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_totalBlockRemoval_1885: this->f_totalBlockRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockRemoval_1801: this->f_blockRemoval = val; return true;
        case SYM_GEN_missDamage_2311: this->f_missDamage = val; return true;
        case SYM_GEN_heatNeeded_1784: this->f_heatNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_affectsEmpty_253: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_onPreDealDamage_late_902: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_affectsEmpty_253: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_902: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_totalBlockRemoval = gd::gd_coerce_int(gd::gd_mul(this->f_blockRemoval, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_427, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_424, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), this->f_heatNeeded)))) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425), this->f_missDamage));
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1427, gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_352, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_totalBlockRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_203, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_blockRemoval = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blockremoval", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_missDamage = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "missdam", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_heatNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MoltenSpear(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MoltenSpear>(&ctx); }
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__BoxofRiches::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__BoxofRiches::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__BoxofRiches::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_countSocketedGems_1521, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Box of Riches", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })(), SYM_GEN_gatedItems_1593);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__BoxofRiches::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_numGems = gd::GdVal::from_int(2LL);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PiggyofRiches(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PiggyofRiches>(&ctx); }
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
        case SYM_GEN_bonusdur_2354: out = this->f_bonusdur; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusdur_2354: this->f_bonusdur = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN_onPrepare_121: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getBagEffect_478: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagJ::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getBagEffect_478: out = fn_getBagEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasInventoryDuration_793, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1104 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1105 = (_t1104.kind == gd::GdVal::Kind::Arr) ? _t1104.arr : nullptr;
        uint32_t _len__t1106 = _t1105 ? _t1105->len : 0u;
        for (uint32_t _t1106 = 0; _t1106 < _len__t1106; ++_t1106) {
            gd::GdVal lv_item = _t1105->data[_t1106];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u)), this->f_bonusdur}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_modifyParam_189, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn_getBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_number = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getName_232, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_BAGEFFECT", 10u)))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_bonusdur", 10u)), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonusdur", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), lv_number)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagJ::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_bonusdur = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonusdur", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_stamina_2059: out = this->f_stamina; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RatChef::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stamina_2059: this->f_stamina = val; return true;
        case SYM_GEN_empower_994: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RatChef::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_initRat_2370: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_getCraftingOffset_846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Rat::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RatChef::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_initRat_2370: out = fn_initRat(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_846: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        gd::GdVal _t1107 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1108 = (_t1107.kind == gd::GdVal::Kind::Arr) ? _t1107.arr : nullptr;
        uint32_t _len__t1109 = _t1108 ? _t1108->len : 0u;
        for (uint32_t _t1109 = 0; _t1109 < _len__t1109; ++_t1109) {
            gd::GdVal lv_item = _t1108->data[_t1109];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Food_2604)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
                lv_numAffectedFood = gd::gd_add(gd_ctx, lv_numAffectedFood, gd::GdVal::from_int(1LL));
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_numAffectedFood}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_316, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1110 = lv_forDirection;
        if (gd::gd_eq(_t1110, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1110, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1110, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        }
        else if (gd::gd_eq(_t1110, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RatChef::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Rat::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_damageAcc_1864: out = this->f_damageAcc; return true;
        case SYM_GEN_manaUseEvents_2390: out = this->f_manaUseEvents; return true;
        case SYM_GEN_manaCost_1719: out = this->f_manaCost; return true;
        case SYM_GEN_permDamBonus_993: out = this->f_permDamBonus; return true;
        case SYM_GEN_poison_1866: out = this->f_poison; return true;
        case SYM_GEN_damageForPoison_2391: out = this->f_damageForPoison; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1864: this->f_damageAcc = val; return true;
        case SYM_GEN_manaUseEvents_2390: this->f_manaUseEvents = val; return true;
        case SYM_GEN_manaCost_1719: this->f_manaCost = val; return true;
        case SYM_GEN_permDamBonus_993: this->f_permDamBonus = val; return true;
        case SYM_GEN_poison_1866: this->f_poison = val; return true;
        case SYM_GEN_damageForPoison_2391: this->f_damageForPoison = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SerpentStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Poison_2566), gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeResistChance_1021, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_manaUseEvent = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_331, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_manaUseEvent, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_manaUseEvent}; return gd::call_method(gd_ctx, this->f_manaUseEvents, gd::SYM_push_back, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_manaUseEvents, gd::SYM_empty, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        this->f_damageAcc = gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425));
        gd::GdVal lv_curPoison = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damageForPoison);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_curPoison, gd::GdVal::from_int(0LL))))) {
            this->f_damageAcc = gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damageForPoison);
            (void)([&]() { gd::GdVal _ca[] = {lv_curPoison, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 2); })();
        }
        (void)gd::call_method(gd_ctx, this->f_manaUseEvents, gd::SYM_pop_back, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SerpentStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_permDamBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_poison = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_damageForPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damforpoison", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SerpentStaff(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SerpentStaff>(&ctx); }
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
        case SYM_GEN_cold_1949: out = this->f_cold; return true;
        case SYM_GEN_maxHealthReduction_2056: out = this->f_maxHealthReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Snowball::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_1949: this->f_cold = val; return true;
        case SYM_GEN_maxHealthReduction_2056: this->f_maxHealthReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Snowball::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Snowball::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Snowball::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealthReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeMaxHealthGain_1257, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_maxHealthReduction = gd::gd_div(gd_ctx, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healthreduction", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Snowball(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Snowball>(&ctx); }
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
        case SYM_GEN_colors_2442: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.489231), gd::GdVal::from_float(0.301961)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.301961), gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.41682)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.941176), gd::GdVal::from_float(0.301961), gd::GdVal::from_float(0.513726)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.320312), gd::GdVal::from_float(0.466339), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })()); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_neutralColor_2443: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.364706)}; return gd::make_color_from_args(_ca, 4); })();
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
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        case SYM_GEN_frame_2444: out = this->f_frame; return true;
        case SYM_GEN_skillLight_2445: out = this->f_skillLight; return true;
        case SYM_GEN_colors_2442: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_neutralColor_2443: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        case SYM_GEN_frame_2444: this->f_frame = val; return true;
        case SYM_GEN_skillLight_2445: this->f_skillLight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_ready_deferred_461: return true;
        case SYM_GEN_updateColor_2446: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_gainsStack_84: return true;
        case SYM_GEN_rotateTo_474: return true;
        case SYM_GEN_setFaceDirectionInstant_465: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_ready_deferred_461: out = fn_ready_deferred(args, argc); return true;
        case SYM_GEN_updateColor_2446: out = fn_updateColor(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_gainsStack_84: out = fn_gainsStack(args, argc); return true;
        case SYM_GEN_rotateTo_474: out = fn_rotateTo(args, argc); return true;
        case SYM_GEN_setFaceDirectionInstant_465: out = fn_setFaceDirectionInstant(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpintoWin::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_ready_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_ready_deferred_461, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2446, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_updateColor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_638, _ca, 1, _out); return _out; })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731)}));
    gd::GdVal lv_gold = gd::GdVal::from_int(0);
    if (gd::gd_truth(this->f_placed)) {
        { gd::GdVal _t1111 = lv_colors; gd::GdVal _t1112 = this->f_faceDirection; gd::set_index(gd_ctx, _t1111, _t1112, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_modifiedColor_2724)); }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(false), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_641, _ca, 4); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1113 = this->f_faceDirection;
        if (gd::gd_eq(_t1113, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
        }
        else if (gd::gd_eq(_t1113, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
        }
        else if (gd::gd_eq(_t1113, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
        }
        else if (gd::gd_eq(_t1113, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_gainsStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1114 = this->f_faceDirection;
        if (gd::gd_eq(_t1114, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            return gd::GdVal::from_bool(gd::gd_eq(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Heat_2572)));
        }
        else if (gd::gd_eq(_t1114, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            return gd::GdVal::from_bool(gd::gd_eq(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Lucky_2569)));
        }
        else if (gd::gd_eq(_t1114, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            return gd::GdVal::from_bool(gd::gd_eq(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Regeneration_2568)));
        }
        else if (gd::gd_eq(_t1114, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            return gd::GdVal::from_bool(gd::gd_eq(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Mana_2570)));
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_rotateTo(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetRotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.15));
    (void)([&]() { gd::GdVal _ca[] = {lv_targetRotation, lv_duration}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_rotateTo_474, _ca, 2, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2446, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn_setFaceDirectionInstant(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv__faceDirection}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_setFaceDirectionInstant_465, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateColor_2446, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpintoWin::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_curLifesteal_2469: out = this->f_curLifesteal; return true;
        case SYM_GEN_lifestealGiven_2470: out = this->f_lifestealGiven; return true;
        case SYM_GEN_lifestealTimer_2471: out = this->f_lifestealTimer; return true;
        case SYM_GEN_lifestealPerTrigger_2472: out = this->f_lifestealPerTrigger; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_curLifesteal_2469: this->f_curLifesteal = gd::gd_coerce_float(val); return true;
        case SYM_GEN_lifestealGiven_2470: this->f_lifestealGiven = val; return true;
        case SYM_GEN_lifestealTimer_2471: this->f_lifestealTimer = val; return true;
        case SYM_GEN_lifestealPerTrigger_2472: this->f_lifestealPerTrigger = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_onOpponentDamaged_1896: return true;
        case SYM_GEN_onLifestealTimeout_2473: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1896: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_onLifestealTimeout_2473: out = fn_onLifestealTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StrongVampiricPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__VampiricPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, SYM_GEN_onPrepare_121, nullptr, 0, _out); return _out; })();
    this->f_curLifesteal = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)gd::call_method(gd_ctx, this->f_lifestealGiven, gd::SYM_clear, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_attacked", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDamaged", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_amount = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_curLifesteal = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curLifesteal, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, this->f_lifestealGiven, gd::SYM_push_back, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_lifestealTimer, SYM_GEN_start_1683, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_curLifesteal, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_canApplyLifesteal_1470, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425), this->f_curLifesteal)), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 2); })();
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
    (void)gd::call_method(gd_ctx, this->f_lifestealTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StrongVampiricPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__VampiricPotion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_lifestealTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "LifestealTimer", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLifestealTimeout", 18u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_lifestealPerTrigger = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_extraDamBlock_2500: out = this->f_extraDamBlock; return true;
        case SYM_GEN_maxHealthBlock_2501: out = this->f_maxHealthBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Turtle::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraDamBlock_2500: this->f_extraDamBlock = val; return true;
        case SYM_GEN_maxHealthBlock_2501: this->f_maxHealthBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Turtle::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreCombatStart_123: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Turtle::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreCombatStart_123: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Shield_2753)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1115 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1116 = (_t1115.kind == gd::GdVal::Kind::Arr) ? _t1115.arr : nullptr;
        uint32_t _len__t1117 = _t1116 ? _t1116->len : 0u;
        for (uint32_t _t1117 = 0; _t1117 < _len__t1117; ++_t1117) {
            gd::GdVal lv_item = _t1116->data[_t1117];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damblock", 8u)), this->f_extraDamBlock}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_modifyParam_189, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onPreCombatStart_123, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_buffEnded_1721, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_blockAmount = gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), gd::gd_mul(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMaxHealth_1140, nullptr, 0), this->f_maxHealthBlock));
    (void)([&]() { gd::GdVal _ca[] = {lv_blockAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Turtle::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_extraDamBlock = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonus_damblock", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxHealthBlock = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_gemColor_991: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.783203), gd::GdVal::from_float(0.972054), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_damageAcc_1864: out = this->f_damageAcc; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_natureSpeed_2527: out = this->f_natureSpeed; return true;
        case SYM_GEN_damageForSpikes_2528: out = this->f_damageForSpikes; return true;
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        case SYM_GEN_gemColor_991: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Wisp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1864: this->f_damageAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_natureSpeed_2527: this->f_natureSpeed = val; return true;
        case SYM_GEN_damageForSpikes_2528: this->f_damageForSpikes = val; return true;
        case SYM_GEN_spikes_894: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Wisp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasCooldown_93: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_prepareInventory_977: return true;
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_onAttack_1956: return true;
        case SYM_GEN_combatStart_125: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_playPickupSound_732: return true;
        case SYM_GEN_playDropSound_147: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Wisp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasCooldown_93: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepareInventory_977: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1956: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_combatStart_125: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_732: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_147: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Wisp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Armor_2750))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_prepareInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), this->f_natureSpeed)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        this->f_damageAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425)));
        gd::GdVal lv_numProccs = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damageForSpikes);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            this->f_damageAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damageForSpikes));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_spikes, lv_numProccs)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1118 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0);
        if (gd::gd_eq(_t1118, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754))) {
            this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_99, _ca, 1); })());
        }
        else if (gd::gd_eq(_t1118, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Armor_2750))) {
            this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_99, _ca, 1); })());
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN_combatStart_125, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1119 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0);
        if (gd::gd_eq(_t1119, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
        }
        else if (gd::gd_eq(_t1119, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Wisp::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Armor_2750))) {
            gd::GdVal lv_bonusHealth = gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getCurrentHealth_1134, nullptr, 0));
            lv_bonusHealth = gd::gd_mul(lv_bonusHealth, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0));
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusHealth}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, _ca, 1); })();
            this->f_consumed = gd::GdVal::from_bool(true);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wisp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_natureSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageForSpikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_gemColor_991: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(0.8), gd::GdVal::from_int(3LL)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_manaCounter_2536: out = this->f_manaCounter; return true;
        case SYM_GEN_spectral_2537: out = this->f_spectral; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_gemColor_991: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Sapphire::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaCounter_2536: this->f_manaCounter = val; return true;
        case SYM_GEN_spectral_2537: this->f_spectral = val; return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Sapphire::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_preAttack_992: return true;
        case SYM_GEN_onAttack_1956: return true;
        case SYM_GEN_prepareArmor_979: return true;
        case SYM_GEN_onManaChanged_1833: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Sapphire::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_preAttack_992: out = fn_preAttack(args, argc); return true;
        case SYM_GEN_onAttack_1956: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_979: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onManaChanged_1833: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Sapphire::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_spectral = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_deal_damage_late", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preAttack", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_spectral = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0);
    if (gd::gd_truth(this->f_spectral)) {
        (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_makeSpectral_1471, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(this->f_spectral) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaCounter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_manaCounter = gd::gd_add(gd_ctx, this->f_manaCounter, lv_amount);
        gd::GdVal lv_relMana = gd::gd_div(gd_ctx, this->f_manaCounter, this->f_manaNeeded);
        gd::GdVal lv_block = gd::gd_mul(lv_relMana, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
        this->f_manaCounter = gd::gd_mod(gd_ctx, this->f_manaCounter, this->f_manaNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_block, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0), lv_block), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_relMana, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_relMana, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Sapphire::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
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
        case SYM_GEN_emitter_1556: out = this->f_emitter; return true;
        case SYM_GEN_signalName_1009: out = this->f_signalName; return true;
        case SYM_GEN_receiver_1557: out = this->f_receiver; return true;
        case SYM_GEN_methodName_1558: out = this->f_methodName; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_emitter_1556: this->f_emitter = val; return true;
        case SYM_GEN_signalName_1009: this->f_signalName = val; return true;
        case SYM_GEN_receiver_1557: this->f_receiver = val; return true;
        case SYM_GEN_methodName_1558: this->f_methodName = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_destroy_1559: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Item__INNER__SignalConnection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_destroy_1559: out = fn_destroy(args, argc); return true;
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Pineapple::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Pineapple::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Pineapple::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pineapple::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_blockFactor_1881: out = this->f_blockFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::get_prop(prop, out);
}
bool Gd__gd_core_items__ShieldofValor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockFactor_1881: this->f_blockFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ShieldofValor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_afterBlock_1846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::has_own_method(m);
}
bool Gd__gd_core_items__ShieldofValor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1846: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_289, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1120 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1121 = (_t1120.kind == gd::GdVal::Kind::Arr) ? _t1120.arr : nullptr;
        uint32_t _len__t1122 = _t1121 ? _t1121->len : 0u;
        for (uint32_t _t1122 = 0; _t1122 < _len__t1122; ++_t1122) {
            gd::GdVal lv_item = _t1121->data[_t1122];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Block_2563), this->f_blockFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_301, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_115, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ShieldofValor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_blockFactor = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_onSpikesChanged_940: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__ThornWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onSpikesChanged_940: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ThornWhip::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ThornWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ThornWhip(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ThornWhip>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__ThornWhip = {CLS_Gd__gd_core_items__ThornWhip, "ThornWhip", "res://gd_core_items/ThornWhip.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__ThornWhip, &Gd__gd_core_items__ThornWhip::get_static_prop_fn, &Gd__gd_core_items__ThornWhip::call_static_fn};
