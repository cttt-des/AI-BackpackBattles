# =============================================================================
# Item.gd — 物品基类适配层（**自动生成，勿手改**）
# 生成器：tools/build_item_scripts.py
# =============================================================================
# 原版 `Items/Item.gd` 是 6573 行 / 628 方法的 RigidBody2D：战斗主干 + 拖拽物理
# + 粒子音效 + 商店存档混在一起。战斗主干已逐行移植进 `gd_core/CoreItem.gd`，
# 本文件承载**CoreItem 之外的剩余面**，使 502 个原版物品脚本（其中 238 个
# 直接 `extends Item`，其余经 `Weapon`/`Bag`/`Gem`/`Card` 等中间类间接继承）
# 能逐字不改地跑在无头内核里。
#
# ★ 本注释里的数字**全部在生成时现算**；覆盖率与「判定路径缺口」不在注释里断言，
#   以 `tools/gd_core_coverage.py` 的现场核算为准（见 tools/run_gd_core.py 闸门）。
#
# 生成方式（不是手写）：把原版 Item.gd 过一遍与物品脚本相同的转译流水线，
# 再与 CoreItem 求差 —— 同名函数/成员/常量/枚举一律丢弃（**内核版本权威**），
# 其余照搬。视觉调用已由通用规则剥成 `ctx.hooks.*` 空钩子或空桩；
# 剥空的块由 ensure_blocks_nonempty() 补 `pass`，故块结构始终合法。
# =============================================================================
extends "res://gd_core/CoreItem.gd"
class_name Item
signal hovered
signal unhovered
signal picked_up
signal dropped
signal added_to_inventory
signal info_panel_clicked
enum Owner{
	Shop, 
	PlayerInventory, 
	PlayerStorageBox, 
	Opponent, 
	Title, 
	RecipeBook, 
	Tooltip, 
	Socket, 
	ItemLibrary, 
	InfoPanelIcon, 
	BuildViewer, 
	BuildViewerIcon, 
	GridStorage, 
	Undefined
}
enum Type{
	Bag, 
	Consumable, 
	Food, 
	Pet, 
	Weapon, 
	Shield, 
	Armor, 
	Gloves, 
	Shoes, 
	Helmet, 
	Accessory, 
	Potion, 
	Card, 
	Gem, 
	Scroll, 
	Book, 
	Skill, 
	ChessPiece, 
	Spell, 
	Melee, 
	Ranged, 
	Effect, 
	Holy, 
	Magic, 
	Vampiric, 
	Dark, 
	Nature, 
	Fire, 
	Ice, 
	Musical
}
enum Priority{
	Lowest = - 10000, 
	Low = - 1000, 
	Normal = 0, 
	High = 1000, 
	Highest = 10000
}
enum CraftingPriority{
	Gem = 3, 
	Mixed = 2
	NonGem = 1
}
enum Tag{
	None = 0, 
	Lifesteal = 1, 
	Stone = 2, 
	Scroll = 8, 
	Dragon = 16, 
	Staff = 32, 
	BattleRage = 64, 
	Singular = 128, 
	Transient = 256, 
	Bow = 512
}
enum Stack{
	None = 0, 
	Block = 1, 
	Lucky = 2, 
	Regeneration = 4, 
	Vampirism = 8, 
	Spikes = 16, 
	Mana = 32, 
	Empower = 64, 
	Heat = 128, 
	Poison = 256, 
	Blind = 512, 
	Cold = 1024, 
	Buff = 128 + 64 + 32 + 16 + 8 + 4 + 2, 
	Debuff = 1024 + 512 + 256, 
	BuffNoLuck = 128 + 64 + 32 + 16 + 8 + 4
}
enum Mat{
	Default, 
	Wood, 
	Metal, 
	Leather, 
	Glass, 
	Stone, 
	Squishy, 
	Jewelry, 
	Sand, 
	Paper, 
	Slime, 
	Ice, 
	Fire, 
	Dragon, 
	Bird, 
	Leaf
}
enum Physics{
	Default, 
	Light, 
	Slime, 
	Dense, 
	VeryDense, 
	Floaty, 
	Sand, 
	Plush, 
	BouncyDense, 
	Ice, 
	Ghost, 
	BlackHole
}
enum Rarity{
	Common = 0, 
	Rare = 1, 
	Epic = 2, 
	Legendary = 3, 
	Godly = 4, 
	Unique = 5
}
enum FaceDirection{
	UP = 0, 
	RIGHT = 1, 
	DOWN = 2, 
	LEFT = 3
}
enum StatModified{
	No = 0, 
	Positive = 1, 
	Negative = 2
}
enum DropResult{
	AddedToInventory, 
	Hotswap, 
	InventoryCollision, 
	OutsideInventory, 
	AddedToStorageBox, 
	Sold, 
	Socketed, 
	SocketHotswap, 
	Failed
}
enum PickupType{
	Grabbed, 
	Hotswap, 
	MultiSelect
}
enum Affected{
	Primary = 0, 
	Secondary = 2, 
	Tertiary = 4, 
	Lightning = 7
}
enum Tiles{
	Extension = 2, 
	Collision = 3, 
	Affected = 4, 
	AffectedDynamic = 5, 
	AffectedSecondary = 6, 
	AffectedSecondaryDynamic = 7, 
	AffectedExtension = 8, 
	AffectedTertiary = 10, 
	AffectedLightning = 11
}
const affectedColorToTileId = {
	CoreConst.Affected.Primary: Tiles.Affected, 
	CoreConst.Affected.Secondary: Tiles.AffectedSecondary, 
	CoreConst.Affected.Tertiary: Tiles.AffectedTertiary, 
	CoreConst.Affected.Lightning: Tiles.AffectedLightning
}
enum ActivationAni{
	Scale, 
	Jump, 
	SquishyJump, 
	VerySquishyJump, 
	Slash, 
	Stab, 
	Bonk, 
	ReverseBonk, 
	Chop, 
	Squish, 
	Block, 
	Wave, 
	Potion, 
	Sweep, 
	Spin, 
	Throw, 
	Shoot, 
	Struggle, 
	ReverseStab, 
	Hiss, 
	Tackle, 
	DoubleSlash, 
	Flash
}
enum Stat{
	MinDamage, 
	MaxDamage, 
	StaminaCost, 
	Speed, 
	BaseCooldown, 
	Accuracy, 
	CritChance, 
	Chance, 
	Chance2, 
	Cooldown
}
enum StackChangeType{
	Added_Player, 
	Added_Opponent, 
	Removed_Player, 
	Removed_Opponent, 
	Used_Player, 
	Used_Opponent
}
var numStackChangeTypes = CoreConst.StackChangeType.size()
const rarityColors = [
	Color(0.460205, 0.874887, 0.90625), 
	Color(0.0737, 0.337874, 0.898438), 
	Color(0.828125, 0, 1), 
	Color(1, 0.609375, 0), 
	Color(0.980469, 0.946239, 0.582153), 
	Color(0.094223, 0.964844, 0.250663)
]
var spriteScale
var hasSquishySprite: = false
var specificDragParticles: Array
var dragParticlesEnabled: = true
const offset = 40
const impulse = 50
const momentumFactor = 20.0
var frictionTime: = 15.0
var totalWeight: float
const affectedSoundsVolume = {
	CoreConst.Affected.Primary: - 8, 
	CoreConst.Affected.Secondary: - 1, 
	CoreConst.Affected.Tertiary: - 1, 
	CoreConst.Affected.Lightning: - 1}
const cellSize = Vector2(80, 80)
const halfCellSize = 0.5 * cellSize
const shadowOffset_shop = Vector2(5, 1)
const shadowOffset_dropped = Vector2(5, 5)
const shadowOffset_dragged = Vector2(15, 15)
const DRAG_PRIORITY = 2
var me = self
var mouseIsOverItem: = false
var hovered: = false
var focus: = false
var spotlight: = false
var collisionShape
var wasJustCrafted: = false
var pickupPosition: Vector2
var pickupRotation: float
var pickupTopLeftCell: Vector2
var pickupFaceDirection: int
var sameOrientationAsPickup: bool
var movebackTween: SceneTreeTween
var rotationTween: SceneTreeTween
var pickingEnabled = true
var tooltipEnabled = true
var hoverResponseEnabled = true
var focusEnabled = true
var affectedCellsActive = true
var affordable: bool
var momentumStrength: float
var momentum: Vector2
var tooltip = null
var tooltipMargin = Vector2(100, 0)
var tooltipUpdateQueued: = false
var shadows: Array
var spritesWithShadows: Array
var shadowOffset = shadowOffset_dropped
var shadowTween
var dropFrame: int = 0
var pickupFrame: int = 0
var mouseWheelRotationReadyTime: float = 0.0
var notEnoughGoldLabelReadyTime: float = 0.0
var averagedPosition: Vector2
var impactSoundVolume: float = 0.0
var progressMaterial = null
var insideRotationNode = null
var draggedInsideItems: = []
var draggingParent = null
var sold: bool = false
var lastVelocity: = Vector2.ZERO
var lastCollisionPos: = Vector2.ZERO
var lastCollider = null
var impactSoundReadyTime = 0.0
var buffLabelPositionTimestamps = [0.0, 0.0, 0.0, 0.0, 0.0]
var globalAffectVisuals: = []
var bondedBaseItem = null
var bondedIngredients = []
var locked = false
var bound = false
var curRecipe = null
var bondVisuals = []
var craftingLabel = null
var craftingAniReadyTime: float = 0.0
var pooled: bool = false
var initialized: bool = false
const correction = [
	Vector2.ZERO, 
	Vector2( - cellSize.x, 0), 
	Vector2( - cellSize.x, - cellSize.y), 
	Vector2(0, - cellSize.y)
]
var canAffectVisuals = []
const angleStep = 45
var rotationMomentum = 0
var bonusRotation = 0
const moveRotationMouseFactor = 0.015
const backforce = 5.0
const fric = 15.0
const maxAngle = 10
const moveRotationSpeed = 60.0
var brightColor = Color(1.3, 1.3, 1.3, 1)
var defaultColor = Color.white
var buildIntoRecipesTooltip = null
var owningBuildIntoRecipesTooltip = null
var ownerTypesWithBuildTooltip = {
	CoreConst.Owner.BuildViewer: true, 
	CoreConst.Owner.PlayerStorageBox: true, 
	CoreConst.Owner.PlayerInventory: true, 
	CoreConst.Owner.Opponent: true, 
	CoreConst.Owner.GridStorage: true
}
const hoverableWhenMenuOpen = {
	CoreConst.Owner.ItemLibrary: true, 
	CoreConst.Owner.InfoPanelIcon: true, 
	CoreConst.Owner.Tooltip: true, 
	CoreConst.Owner.RecipeBook: true
}
var shaderTween
var canCancelShaderTween = true
var nonRotatedProgress = 0.0
const MISS_OFFSET = 100.0
const PRE_FUSE_DUR = 1.0
const PRE_FUSE_DUR_COG = 0.2
const FUSE_DUR = 1.0
const TRANSFORMATION_DUR = 1.0
var fusing = false
var willBeConsumed = false
var fuseParticles1 = null
var fuseParticles2 = null
var fuseTween = null
var fusingBonds: Array
const labelOffsets = [Vector2.ZERO, Vector2(30, 30), Vector2( - 30, 30), 
	Vector2(30, - 30), Vector2( - 30, - 30)]
var collisionMap
var animation
var sprite
var clickArea
var dragParticles
var sockets: Array
var lock
var lockAnimation
var baseBounce: float
var baseFriction: float

func _readyInit():
	._readyInit()
	hasPreDealDamageEarlyEffect = has_method("onPreDealDamage_early")
	hasPreDealDamageLateEffect = has_method("onPreDealDamage_late")
	hasDealtDamageEffect = has_method("onDealtDamage")
	hasOnChargeReceivedEffect = has_method("onChargeReceived")
	hasOnChargeLeftEffect = has_method("onChargeLeft")

static func getNumTooltipStats():
	return CoreConst.ItemStat.size()


static func getNumStackChangeTypes():
	return CoreConst.StackChangeType.size()









func preset():
	pass



func initPhysicsMaterial():
	pass

func getShadowOffset() -> Vector2:
	if ownerType == CoreConst.Owner.Shop:
		return shadowOffset_shop
	else:
		return shadowOffset_dropped





func initRecipeBook():
	pass

func initItemLibrary():
	pass

func setSpotlight(_spotlight):
	hoverEnd()
	if spotlight:
		respondToHover()
	else:
		respondToHoverEnd()


func initTitle():
	pass

func initTooltip():
	pass

func initBuildViewer():
	pass

func initBuildViewerIcon():
	pass

func initInfoPanelIcon():
	pass

func initGridStorageIcon():
	initBuildViewerIcon()



func getData():
	return null


func setData(_data):
	pass



func persistDataInShop() -> bool:
	return false









func getTranslatedName(removeLinebreaks = false) -> String:
	if removeLinebreaks:
		return descriptor.getTranslatedName().replace("\n", "")
	else:
		return descriptor.getTranslatedName()


func getDescription(wrapInColor = true) -> String:
	var descr = descriptor.getDescription()
	if descriptor.requiredItem != null:
		var requiredStr = ctx.util.tra("TOOLTIP_Requires").format({
			"itemName": descriptor.requiredItem.getTranslatedName()
			})
		if descr.begins_with("$t"):
			descr = requiredStr + descr
		else:
			descr = str(requiredStr, "\n\n", descr)

	return insertParameters(descr, wrapInColor)


func insertParameters(descr, wrapInColor = true):
	if getBaseMinDamage() > 0 and wrapInColor:
		descr = descr.replace("$dam", ctx.util.wrapInColor_fixed(str(descriptor.minDam), ctx.util.paramColor))

	for i in descriptor.extraCds.size() + 1:
		descr = insertParameter(descr, str("cd", i + 1), getModifiedCooldownIndex(i), 
			isCooldownModified(), true, wrapInColor)

	descr = insertParameter(descr, "cd", getModifiedCooldown(), isCooldownModified(), true, wrapInColor)
	descr = insertParameter(descr, "chance2", getChance2(), isChance2Modified(), true, wrapInColor)
	descr = insertParameter(descr, "chance", getChance(), isChance1Modified(), true, wrapInColor)
	descr = insertParameter(descr, "shopchance", getShopChance(), CoreConst.StatModified.No, true, wrapInColor)
	descr = insertParameter(descr, "stamina", getStaminaCost(), isStaminaModified(), true, wrapInColor)
	for i in descriptor.params.size():
		descr = insertParameter(descr, "p" + String(i + 1), getP(i), CoreConst.StatModified.No, true, wrapInColor)
	for paramName in descriptor.sortedParamNames:
		descr = insertParameter(descr, "p_" + paramName, getP(paramName), CoreConst.StatModified.No, true, wrapInColor)

	if wrapInColor:
		descr = descr.replace("$block", ctx.util.wrapInColor_fixed(String(getBlock()), ctx.util.paramColor))


	return descr


func insertParameter(descr, paramName, value, modified = CoreConst.StatModified.No, checkZero = true, wrapInColor = true):
	value = stepify(value, 0.01)
	if value != 0 or not checkZero:
		var replacedString = "$" + paramName
		var startPos = descr.find(replacedString)
		if startPos != - 1:
			var refEndPos = ctx.util.findHighlightEnd(descr, startPos + 1)
			var unit = descr.substr(startPos + replacedString.length(), refEndPos - (startPos + 1) - paramName.length())

			var replacement = String(value) + unit
			if startPos > 0:
				if descr[startPos - 1] == "+":
					replacedString = "+" + replacedString
					replacement = "+" + replacement
				elif descr[startPos - 1] == "-":
					replacedString = "-" + replacedString
					replacement = "-" + replacement

			if wrapInColor:
				replacement = ctx.util.wrapInColor_fixed(replacement, ctx.util.statColors[modified])

			descr = descr.replace(replacedString + unit, replacement)

	return descr




func getModeDescription(text: String, colors: Array, center: bool = true, wrapInColor: bool = true):
	pass

func getFlavorText() -> String:
	return descriptor.getFlavorText()


func disablePicking():
	pass


func enablePicking():
	pass


func enableTooltip():
	pass


func disableTooltip():
	pass


func disableFocus():

	if focus:
		loseFocus()


func enableFocus():
	pass


func setEditMode(active: bool):
	pass

func setShadowAlpha(alpha: float):
	pass

func getTopLeftGlobal() -> Vector2:
	return Vector2.ZERO

func getBottomRightGlobal() -> Vector2:
	return Vector2.ZERO

func getBottomCenter() -> Vector2:
	return Vector2.ZERO

func getInventory():
	if placed:
		return inventory
	else:
		return null


static func wasAddedToInventory(dropRes):
	return dropRes == DropResult.AddedToInventory or dropRes == DropResult.Hotswap



static func wasBought(dropRes):
	return (wasAddedToInventory(dropRes) or 
			dropRes == DropResult.AddedToStorageBox or 
			dropRes == DropResult.Socketed or 
			dropRes == DropResult.SocketHotswap)


static func wasHotSwap(dropRes):
	return dropRes == DropResult.Hotswap or dropRes == DropResult.SocketHotswap


func removeFromInventory():
	pass

func playAffectedPlacedAnimation(newItemIsAffected: Dictionary):
	var sum = 0
	for color in newItemIsAffected:
		sum += int(newItemIsAffected[color])

	if sum > 1:
		pass
	elif newItemIsAffected[CoreConst.Affected.Primary]:
		pass
	elif newItemIsAffected[CoreConst.Affected.Secondary]:
		pass
	elif newItemIsAffected[CoreConst.Affected.Tertiary]:
		pass
	elif newItemIsAffected[CoreConst.Affected.Lightning]:
		pass





func clearCanAffectVisuals():
	pass




func liesInStorage() -> bool:
	return ownerType == CoreConst.Owner.PlayerStorageBox and not dragged


func pushToStorage(targetPos = null):
	pass

func addToStorageBox(addImpulse = true, tweenBouncyness: bool = true, 
	checkCollisions = true, targetPos = null, speed = 1.0, secondCheck = false):
	pass

func removeFromStorage():

	killMovebackTween()
	onStorageLeft()


func onStorageLeft():
	pass

func isInGridStorage() -> bool:
	return false

func getGridStorageProxy():
	pass

func onAddedToGridStorage():
	pass

func onRemovedFromGridStorage():
	pass

func makeGrabbable(extended: bool):
	pass

func moveToFreeSpaceInStorage(targetPos = null, 
	addImpulse = false, speed = 1.0, secondCheck = false, 
	tweenBouncyness: bool = true):
	pass

func checkIfOutofStorageBounds():
	ctx.util.callNextFrame(self, "checkIfOutofStorageBounds2")


func checkIfOutofStorageBounds2():
	ctx.util.callNextFrame(self, "checkIfOutofStorageBounds3")


func checkIfOutofStorageBounds3():
	pass

func findFreeSpace(startPos: Vector2) -> Vector2:
	return Vector2.ZERO

func unclip():
	pass

func onAddedToStorageBox():
	pass


func _process(delta: float) -> void :
	pass

func _integrate_forces(state) -> void :
	if state.get_contact_count() > 0:
		pass
	else:
		pass


func updateShadow():
	pass

func lerpAngle_local(interpolationPoint, from, to):
	updateInsideRotationNode()
	updateShadow()


func updateInsideRotationNode():
	if insideRotationNode != null:
		pass


func spawnRotationSparks(rotateRight):
	pass

func highlight():
	pass


func unhighlight():
	resetSprite()


func setBright():
	pass

func resetBright():
	pass

func getHoverPriority():
	if dragged: return DRAG_PRIORITY
	else: return 0


func canGainFocus():
	pass

func gainFocus():
	if not canGainFocus(): return


	if (ownerType == CoreConst.Owner.PlayerInventory or 
		ownerType == CoreConst.Owner.Socket or 
		ownerType == CoreConst.Owner.Opponent):
		ctx.combat_log.highlightItem(self, false)


	respondToHover()


func respondToHover():
	pass

func canShowBuildIntoRecipesTooltip() -> bool:
	if dragged: return false

	var effectiveOwner = getEffectiveOwnerType()

	if ownerType == CoreConst.Owner.Tooltip and owningBuildIntoRecipesTooltip != null:
		if not canShowSubBuildIntoRecipesTooltip():
			return false
	elif not (ownerType == CoreConst.Owner.Shop or 
			ownerType == CoreConst.Owner.ItemLibrary or 
			effectiveOwner in ownerTypesWithBuildTooltip):
		return false

	var descr = getRecipeDescriptor()
	if descr.getNumRecipes() > 0:
		return true

	if getRelatedItems().size() > 0:
		return true

	return false


func canShowSubBuildIntoRecipesTooltip():
	pass

func showBuildIntoRecipesTooltip():
	pass

func getRelatedItemColumns() -> int:
	return 5


func getRelatedItemHeight() -> int:
	return 150


func getRecipeDescriptor():
	return descriptor



func hideBuildIntoRecipesTooltip():
	if buildIntoRecipesTooltip != null:
		pass


func loseFocus():
	if dragged: return

	if not focus: return



	respondToHoverEnd()


func respondToHoverEnd():
	pass

func activateDragParticles():
	for specificParticles in specificDragParticles:
		specificParticles.activate()


func deactivateDragParticles():
	for specificParticles in specificDragParticles:
		specificParticles.deactivate()



func updateTooltip():
	pass


func queueTooltipUpdate():
	pass

func clearTooltip():

	hideBuildIntoRecipesTooltip()
	clearCanAffectVisuals()


func mouseEntered():
	pass

func hover():
	pass

func mouseExited():
	pass

func hoverEnd():
	pass

func isHovered():
	return hovered or dragged


func getScaleProp() -> String:
	if hasSquishySprite:
		return "baseScale"
	else:
		return "scale"


func setSpriteScale(newScale: Vector2):
	if hasSquishySprite:
		pass


func pickup(pickupType = PickupType.Grabbed):
	pass

func onDraggedWithParentStart(parentItem):
	finishMoveback()


func finishMoveback():
	pass

func onDraggedWithParentEnd():
	pass


func canSnap() -> bool:
	return draggedInsideItems.empty() and draggingParent == null


func reactToDropResult(result):
	pass

func drop() -> int:
	return 0

func showClickArea():
	pass


func cancelDrag():
	pass

func emptyTweenCallback():
	pass


func killMovebackTween():
	showClickArea()


func setSpriteGlobalPos(pos):
	updateShadow()


func dropIntoInventory(hotswap):
	pass

func finishInsideItemsRotation():
	pass

func pushDraggedItemsToStorage():
	for item in draggedInsideItems:
		item.pushToStorage()
	correctInsideItemFacedirection()
	clearDraggedInsideItems()



func reparentItemsInside():
	for item in draggedInsideItems:
		pass
	correctInsideItemFacedirection()
	clearDraggedInsideItems()


func clearDraggedInsideItems():
	for item in draggedInsideItems:
		item.onDraggedWithParentEnd()


func showSockets():
	pass

func hideSockets():
	pass

func playPickupSound():
	pass

func playDropSound(volume = 0):
	pass

func canBeSold() -> bool:
	return (ownerType == CoreConst.Owner.PlayerInventory or 
		ownerType == CoreConst.Owner.PlayerStorageBox or 
		ownerType == CoreConst.Owner.Socket)


func isPickingPossible() -> bool:
	return false

func canBePicked() -> bool:
	return focus and isPickingPossible() and ctx.frame_counter > dropFrame


func canBeDraggedWithBag() -> bool:
	return false

func canBeDropped() -> bool:
	return dragged and ctx.frame_counter > pickupFrame


func _input(event: InputEvent) -> void :
	pass

func resetSprite():
	pass

func combatToShop():
	if isOwnedByOpponent():
		disableTooltip()
	else:
		resetSprite()
		cachedAffectedItems.clear()


func shopEntered(craft: bool):
	baseCooldownOverride = descriptor.cd
	speedScale = 0.0
	bonusMinDam = 0
	bonusMaxDam = 0
	removableDam = 0
	bonusDamageFactor = 1.0
	staminaFactor = 1.0
	for buff in buffPowers:
		buffPowers[buff] = 1.0
		buffAmplificationChances[buff] = 0.0

	critChancePercent = 0.0
	critTokens = 0
	critSeverity = BASE_CRIT_SEVERITY
	bonusChancePercent_mult = 0.0
	bonusChancePercent_additive1 = 0.0
	bonusChancePercent_additive2 = 0.0
	bonusAccuracy = 0.0
	doubleActivationChance = 0.0
	doubleAttackEffectChance = 0.0
	paramMult.clear()
	paramAdd.clear()
	numCharges = 0
	statDisplayOverrides.fill(null)
	itemMetrics.fill(0)
	consumed = false
	showCooldownSmooth(0)


	enablePicking()
	for gem in getGemsNoNull():
		gem.shopEntered(craft)

	if craft:
		addToCraftingQueue()

	onShopEntered()


func onShopEntered():
	pass


func startFusing_inShop():
	startFusing(PRE_FUSE_DUR_COG)


func getCraftingPriority() -> int:
	if isGem(): return CoreConst.CraftingPriority.Gem

	for bonded in bondedIngredients:
		if bonded.isGem():
			return CoreConst.CraftingPriority.Mixed

	return CoreConst.CraftingPriority.NonGem


func addToCraftingQueue():
	pass

func combatToTitle():
	if isOwnedByOpponent():
		disableTooltip()


func readyToFuse() -> bool:
	return curRecipe and curRecipe.getProgress(bondedIngredients) == 1


func startFusing(delay = PRE_FUSE_DUR):
	if readyToFuse():
		ctx.util.callDelayed(self, "fuse", delay)
		disablePicking()
		for bonded in bondedIngredients:
			if curRecipe == null or not curRecipe.isNeighborCatalyst(bonded):
				ctx.defer(bonded, "disablePicking", [])
				bonded.willBeConsumed = true


func readyToTransform() -> bool:
	return false


func giveGold(amount: int):
	pass

func getTranslatedTypeName(type) -> String:
	return descriptor.getTranslatedTypeName(type)


func getTypeDescription(type) -> String:
	return ctx.util.tra("TYPE_" + CoreConst.Type.keys()[type] + "_DESCR")


func getTranslatedRarity() -> String:
	return getRarityName(getRarity())


static func getRarityName(_rarity: int) -> String:
	return ""

func logCooldown() -> bool:
	return hasCooldown()


func getCombatDisplayAccuracy() -> String:
	var acc = getAccuracy()
	if acc > 100:
		return ">100"
	elif acc < 0:
		return "<0"
	else:
		return String(acc)


func getDisplayCritChance() -> String:
	var c = getCritChancePercent()
	if c > 100:
		return ">100"


	else:
		return String(stepify(c, 0.1))



func getSalesMultiplier():
	return 1.0


func prepareDiscard():
	pass

func discard(discardGems = true):
	pass

func popIn(withParticles: bool = true, speed = 1.0, jump = false):
	pass

func disappear():
	pass



func appearInLibrary():
	pass

func createParticles(scene, baseScale = Vector2.ONE):
	pass

func deactivateParticles():
	pass

func makeRigidBody():
	pass

func dropImpulse(direction = null, tweenBouncyness: bool = true):
	pass

func makeNonRigidBody():
	pass

func rollShopChance(shopChance = descriptor.shopChance) -> bool:
	return false

func _physics_process(delta: float):
	if not character().isStunned():
		triggerTime -= delta * getSpeed()
		showCooldown(1.0 - (triggerTime / iterationCooldown))
		if triggerTime <= 0:
			trigger()





func playActivationAnimation_Scale(maxScale: float):
	pass


func playActivationAnimation_Jump(height, maxScale: float = 1.0):
	pass




func playActivationAnimation_JumpSquash(height, intensity = 0.2):

	var longScale = 1.0 + intensity
	var shortScale = 1.0 / longScale
	var scaling: Vector2
	if faceDirection == CoreConst.FaceDirection.UP or faceDirection == CoreConst.FaceDirection.DOWN:
		scaling = Vector2(shortScale, longScale)
	else:
		scaling = Vector2(longScale, shortScale)




func playActivationAnimation(aniType = descriptor.activationAni, 
	consume: bool = false):

	resetSprite()

	if aniType == ActivationAni.Jump:
		playActivationAnimation_Jump(40)

	elif aniType == ActivationAni.SquishyJump:
		playActivationAnimation_JumpSquash(40, 0.1)

	elif aniType == ActivationAni.VerySquishyJump:
		playActivationAnimation_JumpSquash(40, 0.2)

	elif aniType == ActivationAni.Slash:
		pass

	elif aniType == ActivationAni.Stab:
		pass

	elif aniType == ActivationAni.ReverseStab:
		pass

	elif aniType == ActivationAni.Bonk:
		pass

	elif aniType == ActivationAni.ReverseBonk:
		pass

	elif aniType == ActivationAni.Sweep:
		pass

	elif aniType == ActivationAni.Block:
		playActivationAnimation_Jump(30, 1.3)

	elif aniType == ActivationAni.Chop:
		pass

	elif aniType == ActivationAni.Wave:
		pass

	elif aniType == ActivationAni.Throw:
		pass

	elif aniType == ActivationAni.Scale:
		playActivationAnimation_Scale(1.5)

	elif aniType == ActivationAni.Squish:

		if hasSquishySprite:
			pass
		else:
			pass

	elif aniType == ActivationAni.Potion:
		pass

	elif aniType == ActivationAni.Hiss:
		pass

	elif aniType == ActivationAni.Spin:
		pass

	elif aniType == ActivationAni.Tackle:
		pass

	elif aniType == ActivationAni.DoubleSlash:
		pass

	elif aniType == ActivationAni.Struggle:
		playActivationAnimation_Jump(30)

	elif aniType == ActivationAni.Shoot:
		pass

	elif aniType == ActivationAni.Flash:
		pass

	if consume:
		pass


func playActivationSound():
	playDropSound( - 6)


func clearSpriteMaterial():
	pass


func giveProgressMaterial():
	pass


func getTextureSize() -> Vector2:
	return Vector2.ZERO

func scaleToFit(maxSize: Vector2, maxScale: float):
	pass

func getSpriteOffset() -> Vector2:
	return Vector2.ZERO

func getGlobalCenter() -> Vector2:
	return Vector2.ZERO

func getTextureSize_local() -> Vector2:
	return Vector2.ZERO

func scaleToFit_local(maxSize: Vector2, maxScale: float):
	pass

func getSpriteOffset_local() -> Vector2:
	return Vector2.ZERO

func setTexture(newTex):
	initSpriteMaterial()


func updateShadowTexture():
	pass


func initSpriteMaterial():
	pass




func updateShaderRotation():
	pass

func allowCancelShaderTween():
	pass


func showCooldownSmooth(progress: float, fill: bool = false):
	if not canCancelShaderTween:
		return


	if fill:
		pass
	else:
		pass


func showCooldown(progress: float):
	pass

func createAnimation():
	pass

func playAnimation(hit: bool = true):
	if not descriptor.animationScene: return



func hasInventoryDuration() -> bool:
	return descriptor.hasParam("dur")


func reveal():
	pass


func setRevealed():
	reveal()


func isCrafted() -> bool:
	return descriptor.isCraftedItem()


func isMovingBack() -> bool:
	return false

func _notification(what: int) -> void :
	pass

func getAllInInventoryOfType(descr) -> Array:
	if isOwnedByOpponent():
		return ctx.item_book.getItemsInInventoryOfType_opponent(descr)
	else:
		return ctx.item_book.getItemsInInventoryOfType(descr)


func countAllInInventoryOfType(descr) -> int:
	if isOwnedByOpponent():
		return ctx.item_book.countItemsInInventoryOfType_opponent(descr)
	else:
		return ctx.item_book.countItemsInInventoryOfType(descr)


func isTypeInInventory(descr) -> bool:
	if isOwnedByOpponent():
		return ctx.item_book.isItemInInventory_opponent(descr)
	else:
		return ctx.item_book.isItemInInventory(descr)




func isRecipeFinished():
	return curRecipe.getProgress(bondedIngredients) == 1


func canStartNewRecipe() -> bool:
	return not isBaseItem() and isAvailableForCrafting()


func getRecipes(checkClassAvailability = true):
	var recipes = []
	for recipe in descriptor.recipes:

		recipes.push_back(recipe)
	return recipes



func breakBondVisual(toItem):
	var bondIndex = bondedIngredients.find(toItem)
	if bondIndex != - 1:
		pass



func removeBondedBaseItem():
	setBoundAsIngredient(false)


func removeBondedIngredient(item):

	breakBondVisual(item)


	if fusing:
		return

	showProgressLabel()

	if bondedIngredients.empty():
		pass

	else:
		updateBondVisuals()


func removeAllIngredients():



	showProgressLabel()












func considerAsBond(neighbor):
	var score = 0.0
	var recipe = null
	if curRecipe:
		if isRecipeFinished():
			return null

		if curRecipe.checkNeighbor(bondedIngredients, neighbor):
			var progressBefore = curRecipe.getProgress(bondedIngredients)
			var progressWithNeighbor = (bondedIngredients.size() + 1) / float(curRecipe.getNumIngredients())
			score = progressWithNeighbor + 0.1 * progressBefore
			recipe = curRecipe
	else:
		var bestScore = 0.0
		for r in getRecipes():
			if r.checkNeighbor([], neighbor):
				var s = 1.0 / r.getNumIngredients()
				if s > bestScore:
					bestScore = s
					recipe = r

		score = bestScore

	if recipe:
		return [recipe, score]
	else:
		return null


func addBondedIngredient(forRecipe, neighbor):
	if curRecipe:

		pass
	else:
		pass

	createBondVisual(neighbor)
	updateBondVisuals()
	playBondAnimation()

	if neighbor.placedByPlayer or placedByPlayer:
		showProgressLabel()


func addToBaseItem(baseItem):
	setBoundAsIngredient(true)
	playBondAnimation()


func playBondAnimation():

	var catalyst: = false
	if bondedBaseItem != null:
		if bondedBaseItem.curRecipe != null:
			catalyst = bondedBaseItem.curRecipe.isCatalystRecipe()
	else:
		if curRecipe != null:
			catalyst = curRecipe.isCatalystRecipe()

	if catalyst:
		pass
	else:
		pass


func playBondFailedAnimation():
	pass


func isCatalystBond(bondedItem) -> bool:
	if curRecipe == null:
		return false

	return curRecipe.isNeighborCatalyst(bondedItem)


func isLocked() -> bool:
	return locked


func canLockBag():
	return false


func canBeLocked() -> bool:
	return false

func setLocked(_locked, showLabel = true):

	if locked == _locked: return

	if _locked:
		lockCombining(showLabel)
	else:
		unlockCombining()


func unlockCombining(playAni: bool = true):
	pass

func lockCombining(showLabel = true):
	pass

func showLockLabel():
	pass

func getLockPosition() -> Vector2:
	return Vector2.ZERO

func setBoundAsIngredient(_bound: bool):
	pass



func canPreviewFusions():
	pass

func getCraftingPreviewPosition():
	pass

func previewFusions():
	pass

func previewRecipeIngredients():
	pass

func previewFusionToItem(hoveredIngredient):
	pass

func hasShopItemCraftCandidates() -> bool:
	return false

func typeInIngredients(candidate, ingredients):
	for ingredient in ingredients:
		if candidate.hasType(ingredient):
			return true
	return false


func getTextEffect() -> int:
	return descriptor.textEffect


func getFusionItemName() -> String:
	return curRecipe.fusedItem.getTranslatedName()


func showProgressLabel():
	pass

func onCraftingLabelReturned():
	pass


func createBondVisual(bondNeighbor):
	pass

func updateBondVisuals():
	pass

func fuse():
	pass

func onFusingAsIngredient():
	pass


func onFusingAsCatalystFinished():
	clearSpriteMaterial()
	setBoundAsIngredient(false)


func createCraftedShockwave(fusedItem):
	pass

func finishFusing():
	pass

func allowGeneratingFusionItem() -> bool:
	return true


func catalystFusingFinished():
	pass

func onFusingFinished(validBonds):
	pass

func onCraftedFrom(baseItem, ingredients):
	pass


func getCraftingOffset(_forDirection):
	return Vector2.ZERO



func playCraftedAnimation(originPosition: Vector2):
	pass

func getNextFreeLabelPosition() -> Vector2:
	return Vector2.ZERO

func onRestoreSnapshot():
	finishMoveback()


func getShopPriority() -> int:
	return CoreConst.Priority.Normal




class SignalConnection:
	var emitter
	var signalName
	var receiver
	var methodName

	func _init(_emitter, _signalName, _receiver, _methodName, binds = []):
		emitter = _emitter
		signalName = _signalName
		receiver = _receiver
		methodName = _methodName

		emitter.connect(signalName, receiver, methodName, binds)

	func destroy():
		pass
