extends RigidBody2D
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
	Affected.Primary: Tiles.Affected, 
	Affected.Secondary: Tiles.AffectedSecondary, 
	Affected.Tertiary: Tiles.AffectedTertiary, 
	Affected.Lightning: Tiles.AffectedLightning
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

static func getNumTooltipStats():
	return Stat.size()

var itemMetrics = []

enum StackChangeType{
	Added_Player, 
	Added_Opponent, 
	Removed_Player, 
	Removed_Opponent, 
	Used_Player, 
	Used_Opponent
}

var numStackChangeTypes = StackChangeType.size()

static func getNumNonStackItemMetrics():
	return (Game.ItemMetrics.Stamina + 
			(Game.ItemMetrics.Block - Game.ItemMetrics.Stamina) * StackChangeType.size())

static func getNumItemMetrics():
	return (Game.ItemMetrics.Stamina + 
			(Game.ItemMetrics.size() - Game.ItemMetrics.Stamina) * StackChangeType.size())

static func getNumStackChangeTypes():
	return StackChangeType.size()







		
var statDisplayOverrides = []

const rarityColors = [
	Color(0.460205, 0.874887, 0.90625), 
	Color(0.0737, 0.337874, 0.898438), 
	Color(0.828125, 0, 1), 
	Color(1, 0.609375, 0), 
	Color(0.980469, 0.946239, 0.582153), 
	Color(0.094223, 0.964844, 0.250663)
]

onready var collisionMap = $CollisionMap
onready var animation = $AnimationPlayer
onready var sprite = $Icon
var spriteScale
var hasSquishySprite: = false
onready var clickArea = $ClickArea

onready var dragParticles = $DragParticles
var specificDragParticles: Array
var dragParticlesEnabled: = true
onready var sockets: Array = $Icon / Sockets.get_children()
onready var lock = $Lock
onready var lockAnimation = $Lock / AnimationPlayer

onready var baseBounce: float = physics_material_override.bounce
onready var baseFriction: float = physics_material_override.friction
const offset = 40
const impulse = 50
const momentumFactor = 20.0
var frictionTime: = 15.0
var totalWeight: float



const itemMaterial = preload("res://Items/Materials/NewProgressMaterial.material")

const grayscaleMaterial = preload("res://Shader/Grayscale.material")
const shadowScene = preload("res://Items/Shadow.tscn")
const dropParticlesScene = preload("res://Interface/Inventory/DropParticles.tscn")
const tooltipScenes = [
	preload("res://Interface/Tooltips/CommonTooltip.tscn"), 
	preload("res://Interface/Tooltips/RareTooltip.tscn"), 
	preload("res://Interface/Tooltips/EpicTooltip.tscn"), 
	preload("res://Interface/Tooltips/LegendaryTooltip.tscn"), 
	preload("res://Interface/Tooltips/GodlyTooltip.tscn"), 
	preload("res://Interface/Tooltips/UniqueTooltip.tscn")]

const recipeTooltip = preload("res://Interface/Tooltips/RecipeTooltip.tscn")
const rotateSound = preload("res://Assets/Sound/Grind.wav")
const grabSound = preload("res://Assets/Sound/Swing1.wav")
const dustParticles = preload("res://Interface/DustParticles.tscn")
const hoverSound = preload("res://Assets/Sound/Click4.wav")
const lockSound = preload("res://Assets/Sound/Lock.wav")
const unlockSound = preload("res://Assets/Sound/Unlock.wav")
const sparksScene = preload("res://Interface/Inventory/ItemSparks.tscn")
const hoverSparksScene = preload("res://Interface/Inventory/ItemHoverSparks.tscn")
const rotationSparksScene = preload("res://Interface/Inventory/ItemRotationSparks.tscn")
const typeTransformationParticles = {
	Type.Dark: preload("res://Items/Particles/DarkTransformationParticles.tscn"), 
	Type.Holy: preload("res://Items/Particles/HolyTransformationParticles.tscn")
}
const craftingBondScene = preload("res://Items/CraftingBond.tscn")
const catalystBondScene = preload("res://Items/CatalystBond.tscn")
const craftingLabelScene = preload("res://Interface/Inventory/CraftingProgressLabel.tscn")
const craftingReadyAnimation = preload("res://Items/Animations/CraftingReadyAnimation.tscn")
const craftedAnimation = preload("res://Items/Animations/CraftedAnimation.tscn")
const catalystReadyAnimation = preload("res://Items/Animations/CatalystReadyAnimation.tscn")
const lockLabelScene = preload("res://Interface/Inventory/CraftingLockLabel.tscn")
const affectedAnis = {
	Affected.Primary: preload("res://Interface/Inventory/AffectedStarAnimation.tscn"), 
	Affected.Secondary: preload("res://Interface/Inventory/AffectedStarAnimationSecondary.tscn"), 
	Affected.Tertiary: preload("res://Interface/Inventory/AffectedStarAnimationTertiary.tscn"), 
	Affected.Lightning: preload("res://Interface/Inventory/AffectedStarAnimationLightning.tscn")}
const affectedSounds = {
	Affected.Primary: preload("res://Assets/Sound/Chime1.mp3"), 
	Affected.Secondary: preload("res://Assets/Sound/Chime2.mp3"), 
	Affected.Tertiary: preload("res://Assets/Sound/Chime3.mp3"), 
	Affected.Lightning: preload("res://Assets/Sound/Chime3.mp3")}
const affectedSoundsVolume = {
	Affected.Primary: - 8, 
	Affected.Secondary: - 1, 
	Affected.Tertiary: - 1, 
	Affected.Lightning: - 1}
const globalAffectVisual = preload("res://Interface/Inventory/GlobalAffectVisual.tscn")

const cellSize = Vector2(80, 80)
const halfCellSize = 0.5 * cellSize
const shadowOffset_shop = Vector2(5, 1)
const shadowOffset_dropped = Vector2(5, 5)
const shadowOffset_dragged = Vector2(15, 15)
const DRAG_PRIORITY = 2
const cdEncodingFactor: = 100000.0

var me = self
var descriptor
var inventory
var ownerType: int
var placed: = false
var occupiedCells: = []
var mouseIsOverItem: = false
var hovered: = false
var dragged: = false
var focus: = false
var spotlight: = false
var collisionShape
var wasJustCrafted: = false

var collisionCells: Array
var extensionCells: Array
var affectedExtensionCells: Array
var affectedCellsCache: Dictionary = {}




var faceDirection = FaceDirection.UP
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

var dynamicTypes: Dictionary
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
var currentAffectedItems: Dictionary = {}
var cachedAffectedItems: Dictionary
var mouseWheelRotationReadyTime: float = 0.0
var notEnoughGoldLabelReadyTime: float = 0.0
var averagedPosition: Vector2
var impactSoundVolume: float = 0.0
var placedByPlayer: bool
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
var consumed: bool
var globalAffectVisuals: = []


var bondedBaseItem = null
var bondedIngredients = []
var locked = false
var bound = false
var curRecipe = null

var bondVisuals = []
var craftingLabel = null
var craftingAniReadyTime: float = 0.0


var lastActivationTime: float = 0.0
var activationsThisFrame: int = 0
var lastTriggerTime: float = 0.0
var triggersThisFrame: int = 0
var combatConnections: Array = []
var triggerTime: float
var iterationCooldown: float
var baseCooldownOverride: float
var chanceRng = BalancedRng.new()
var damageRangeRng = BalancedRange.new()
var speedScale: float = 0.0
var bonusMaxDam: float = 0.0
var bonusMinDam: float = 0.0
var removableDam: float = 0.0
var bonusDamageFactor: float = 1.0
var staminaFactor: float = 1.0
var critChancePercent: float = 0.0
var critTokens: int = 0
const BASE_CRIT_SEVERITY = 2.0
var critSeverity: float = BASE_CRIT_SEVERITY
var bonusChancePercent_mult: float = 0.0
var bonusChancePercent_additive1: float = 0.0
var bonusChancePercent_additive2: float = 0.0
var bonusAccuracy: float = 0.0
var buffPowers: Dictionary
var buffAmplificationChances: Dictionary
var damageSource = null
var doubleActivationChance: float
var doubleAttackEffectChance: float
var paramMult: Dictionary
var paramAdd: Dictionary
var numCharges: = 0

var pooled: bool = false
var initialized: bool = false

onready var hasPreDealDamageEarlyEffect: = has_method("onPreDealDamage_early")
onready var hasPreDealDamageLateEffect: = has_method("onPreDealDamage_late")
onready var hasDealtDamageEffect: = has_method("onDealtDamage")
onready var hasOnChargeReceivedEffect: = has_method("onChargeReceived")
onready var hasOnChargeLeftEffect: = has_method("onChargeLeft")

func preset():
	pass


func _ready() -> void :
	if not pooled:
		
		
		if not descriptor:
			descriptor = ItemBook.getDescriptor(name)
			ownerType = Owner.RecipeBook
	
	if sprite.get_script() != null:
		if sprite is SquishySprite:
			hasSquishySprite = not pooled or ownerType == Owner.Title
		sprite.init()
	
	if not initialized:
		collisionMap.hide()
		
		
		if Game.EDITOR:
			assert (collisionMap.get_used_cells_by_id(Tiles.AffectedDynamic).empty())
			assert (collisionMap.get_used_cells_by_id(Tiles.AffectedSecondaryDynamic).empty())
		
		clickArea.show()
		
		spriteScale = sprite.scale
		sprite.offset = sprite.position / sprite.scale
		sprite.position = Vector2.ZERO
		$Icon / Sockets.position = sprite.offset
		
		for root in [self, sprite]:
			for child in root.get_children():
				if child.name.begins_with("SpecificDragParticles"):
					specificDragParticles.push_back(child)
		
		for node in sprite.get_children():
			if node is Particles2D or node is Sprite:
				node.position += sprite.offset
			
		initSockets()
		
		empowerEnd()
		baseCooldownOverride = descriptor.cd
		progressMaterial = itemMaterial.duplicate()
		initSpriteMaterial()
		clearSpriteMaterial()
		
		spritesWithShadows.push_back(sprite)
		for node in Util.getAllChildren(sprite):
			if node.is_in_group("hasShadow"):
				spritesWithShadows.push_back(node)
		
		for node in spritesWithShadows:
			var shadow = shadowScene.instance()
			shadows.push_back(shadow)
			
			add_child(shadow)
			shadow.texture = node.texture
			shadow.modulate = Color(0, 0, 0, 0.5)
			shadow.z_index = - 1
			shadow.global_scale = sprite.global_scale
			shadow.offset = sprite.offset
			shadow.global_rotation = sprite.global_rotation
			shadowOffset = getShadowOffset()
			shadow.global_position = sprite.global_position + shadowOffset
		
		collisionShape = get_node_or_null("CollisionShape2D")
		if collisionShape == null:
			collisionShape = get_node("CollisionPolygon2D")
		
		
	
	
		
		dragParticles.modulate = Game.rarityColors[getRarity()].lightened(0.3)
		
		for buff in Game.getStacks():
			buffPowers[buff] = 1.0
			buffAmplificationChances[buff] = 0.0
		
		cacheCollisionCells()
		
		affectedExtensionCells = collisionMap.get_used_cells_by_id(Tiles.AffectedExtension)
		for cell in affectedExtensionCells:
			collisionMap.set_cellv(cell, - 1)
		
		statDisplayOverrides.resize(Stat.size())
		statDisplayOverrides.fill(null)
		
		itemMetrics.resize(getNumItemMetrics())
		itemMetrics.fill(0)
		
		initPhysicsMaterial()
		
		for color in Affected.values():
			currentAffectedItems[color] = {}
		
		initialized = true
	
	
	
	
	set_physics_process(false)
	makeNonRigidBody()
	showCooldown(0.0)
	scale = Vector2.ONE
	modulate = Color.white
	rotation = 0
	clickArea.connect("mouse_entered", self, "mouseEntered")
	clickArea.connect("mouse_exited", self, "mouseExited")
	
	if isOwnable():
		ItemBook.onOwnableItemAdded(self)
		Game.setItemEditMode(self)
	elif isOwnedByOpponent():
		ItemBook.onOpponentItemAdded(self)
		set_process_input(false)
	
	call_deferred("ready_deferred")

func ready_deferred():
	
	if not is_inside_tree():
		return
	
	resetZ()
	averagedPosition = global_position
	
	if ownerType == Owner.Shop:
		makeGrabbable(true)
	
	if isOwnable() and has_method("onItemInstantiated"):
		ItemBook.connect("item_instantiated_deferred", self, "onItemInstantiated")
	
	if not pooled:
		insideRotationNode = Node2D.new()
		insideRotationNode.name = "InsideRotation"
		add_child(insideRotationNode)
	

func initPhysicsMaterial():
	baseFriction = 0.5
	var baseMass = 1 + getNumCells() * 0.5
	match descriptor.physics:
		Physics.Default:
			mass = baseMass
		Physics.Light:
			mass = baseMass * 0.5
			linear_damp = 0.1
		Physics.Dense:
			gravity_scale = 4.5
			mass = baseMass * 2
		Physics.BouncyDense:
			gravity_scale = 4.5
			mass = baseMass * 2
			baseBounce = 2.0
			frictionTime = 20.0
		Physics.VeryDense:
			gravity_scale = 5.5
			mass = baseMass * 2.5
		Physics.Ice:
			gravity_scale = 4
			mass = baseMass * 2
			baseFriction = 0.0
		Physics.Slime:
			baseBounce = 2.0
			baseFriction = 0.4
			frictionTime = 30.0
			linear_damp = - 0.1
			mass = baseMass
		Physics.Floaty:
			gravity_scale = 1.8
			mass = baseMass * 0.5
			linear_damp = 0.3
		Physics.Ghost:
			gravity_scale = 1.2
			mass = baseMass * 2.0 + 2.0
			linear_damp = 0.7
		Physics.Sand:
			gravity_scale = 4
			mass = baseMass * 1.5
			baseBounce = 0.2
		Physics.Plush:
			gravity_scale = 2.5
			mass = baseMass * 0.75
			baseBounce = 0.2
		Physics.BlackHole:
			gravity_scale = 7
			mass = baseMass * 2.5
			baseBounce = 0.3
			baseFriction = 0.8
			
			
	totalWeight = 0.3 + mass * sqrt(getNumCells()) * 0.2

func isA(_descriptor) -> bool:
	return descriptor == _descriptor

func getShadowOffset() -> Vector2:
	if ownerType == Owner.Shop:
		return shadowOffset_shop
	else:
		return shadowOffset_dropped




static func getStackMetricIndex(stackChangeType: int, stackType: int) -> int:
	var offsetStackType = stackType - Game.EventType.Block
	var changeTypeOffset = stackChangeType * Game.numStackTypes
	return getNumNonStackItemMetrics() + changeTypeOffset + offsetStackType


static func getMultiMetricIndex(stackChangeType: int, metric: int) -> int:
	var offsetMetric = metric - Game.ItemMetrics.Stamina
	var numMultiMetrics = offsetMetric * StackChangeType.size()
	return Game.ItemMetrics.Stamina + numMultiMetrics + stackChangeType

func cacheCollisionCells():
	collisionCells = collisionMap.get_used_cells_by_id(Tiles.Collision)
	extensionCells = collisionMap.get_used_cells_by_id(Tiles.Extension)
	
	

func initRecipeBook():
	disablePicking()
	for shadow in shadows:
		shadow.hide()
	collisionShape.disabled = true
	set_collision_layer(0)
	set_collision_mask(0)
	

func initItemLibrary():
	disablePicking()
	disableFocus()
	for shadow in shadows:
		shadow.hide()
	collisionShape.disabled = true
	set_collision_layer(0)
	set_collision_mask(0)
	set_process(false)
	call_deferred("enableFocus")
	
	set_process_input(true)

func setSpotlight(_spotlight):
	hoverEnd()
	spotlight = _spotlight
	if spotlight:
		respondToHover()
	else:
		respondToHoverEnd()

func initTitle():
	disablePicking()
	disableTooltip()
	makeRigidBody()
	disableFocus()
	for shadow in shadows:
		shadow.show()
	collisionShape.disabled = false
	clickArea.hide()
	set_process(true)
	set_process_input(false)

func initTooltip():
	disableTooltip()
	disablePicking()
	disableFocus()
	for shadow in shadows:
		shadow.hide()
	collisionShape.disabled = true
	clickArea.hide()
	set_collision_layer(0)
	set_collision_mask(0)
	set_process(false)
	set_process_input(false)

func initBuildViewer():
	enableTooltip()
	enableFocus()
	clickArea.show()
	disablePicking()
	collisionShape.disabled = true
	set_collision_layer(0)
	set_collision_mask(0)
	for shadow in shadows:
		shadow.show()
	
	
	set_process_input(false)

func initBuildViewerIcon():
	enableTooltip()
	disablePicking()
	enableFocus()
	for shadow in shadows:
		shadow.hide()
	collisionShape.disabled = true
	clickArea.show()
	set_collision_layer(0)
	set_collision_mask(0)
	set_process_input(false)

func initInfoPanelIcon():
	initBuildViewerIcon()
	set_process_input(true)

func initGridStorageIcon():
	initBuildViewerIcon()
	clickArea.hide()


func getData():
	return null

func setData(_data):
	pass


func persistDataInShop() -> bool:
	return false








func getIndex() -> int:
	return descriptor.getIndex()

func getName() -> String:
	return descriptor.getName()

func getTranslatedName(removeLinebreaks = false) -> String:
	if removeLinebreaks:
		return descriptor.getTranslatedName().replace("\n", "")
	else:
		return descriptor.getTranslatedName()

func getDescription(wrapInColor = true) -> String:
	var descr = descriptor.getDescription()
	if descriptor.requiredItem != null:
		var requiredStr = Util.tra("TOOLTIP_Requires").format({
			"itemName": descriptor.requiredItem.getTranslatedName()
			})
		if descr.begins_with("$t"):
			descr = requiredStr + descr
		else:
			descr = str(requiredStr, "\n\n", descr)
	
	return insertParameters(descr, wrapInColor)

func insertParameters(descr, wrapInColor = true):
	if getBaseMinDamage() > 0 and wrapInColor:
		descr = descr.replace("$dam", Util.wrapInColor_fixed(str(descriptor.minDam), Util.paramColor))
	
	for i in descriptor.extraCds.size() + 1:
		descr = insertParameter(descr, str("cd", i + 1), getModifiedCooldownIndex(i), 
			isCooldownModified(), true, wrapInColor)
			
	descr = insertParameter(descr, "cd", getModifiedCooldown(), isCooldownModified(), true, wrapInColor)
	descr = insertParameter(descr, "chance2", getChance2(), isChance2Modified(), true, wrapInColor)
	descr = insertParameter(descr, "chance", getChance(), isChance1Modified(), true, wrapInColor)
	descr = insertParameter(descr, "shopchance", getShopChance(), StatModified.No, true, wrapInColor)
	descr = insertParameter(descr, "stamina", getStaminaCost(), isStaminaModified(), true, wrapInColor)
	for i in descriptor.params.size():
		descr = insertParameter(descr, "p" + String(i + 1), getP(i), StatModified.No, true, wrapInColor)
	for paramName in descriptor.sortedParamNames:
		descr = insertParameter(descr, "p_" + paramName, getP(paramName), StatModified.No, true, wrapInColor)
	
	if wrapInColor:
		descr = descr.replace("$block", Util.wrapInColor_fixed(String(getBlock()), Util.paramColor))
	
	
	return descr

func insertParameter(descr, paramName, value, modified = StatModified.No, checkZero = true, wrapInColor = true):
	value = stepify(value, 0.01)
	if value != 0 or not checkZero:
		var replacedString = "$" + paramName
		var startPos = descr.find(replacedString)
		if startPos != - 1:
			var refEndPos = Util.findHighlightEnd(descr, startPos + 1)
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
				replacement = Util.wrapInColor_fixed(replacement, Util.statColors[modified])
			
			descr = descr.replace(replacedString + unit, replacement)
			
	return descr



func getModeDescription(text: String, colors: Array, center: bool = true, wrapInColor: bool = true):
	var charIndex = 0
	for i in colors.size():
		var dollarPos = text.find("$c[", charIndex)
		var refStartPos = dollarPos + 3
		var refEndPos = ToolTip.findClosingBracket(text, refStartPos)
		var replacement: String
		if i != 0 and center:
			replacement = "\n"
		
		replacement += Util.substr(text, refStartPos, refEndPos - 1)
		if wrapInColor:
			replacement = Util.wrapInColor(replacement, colors[i])
			if center:
				replacement = str("[center]", replacement, "[/center]\n")

		text = Util.replaceSubstr(text, dollarPos, refEndPos, replacement)
		charIndex = refEndPos
	
	return text

func getBagEffect(number):
	if not isBag():
		return ""
	else:
		var descr = Util.tra(getName() + "_BAGEFFECT")
		if descr != "":
			
			descr = insertParameter(descr, "p1", getP(0) * number)
			descr = insertParameter(descr, "p2", getP(1) * number)
			descr = insertParameter(descr, "chance", getChance() * number)
			descr = insertParameters(descr)
		return descr

func getFlavorText() -> String:
	return descriptor.getFlavorText()

func isBag() -> bool:
	return false

func isWeapon() -> bool:
	return descriptor.isWeapon()

func isPlaced() -> bool:
	return placed




func isOwnable() -> bool:
	return (ownerType == Owner.Shop or 
		ownerType == Owner.PlayerInventory or 
		ownerType == Owner.PlayerStorageBox)

func isOwnedByOpponent() -> bool:
	return ownerType == Owner.Opponent


func isClassItem(classIndex = null) -> bool:
	if classIndex != null:
		return descriptor.isClassItem() and descriptor.isAvailableFor(classIndex)
	return descriptor.isClassItem()

func isNeutral() -> bool:
	return descriptor.isNeutral()

func isSubclassItem() -> bool:
	return descriptor.isSubclassItem()

func isGateItem() -> bool:
	return has_method("getGatedDescriptor") or has_method("getReplaceDescriptor")

func getTriggerPriority() -> int:
	return Priority.Normal

func disablePicking():
	pickingEnabled = false

func enablePicking():
	pickingEnabled = true

func enableTooltip():
	tooltipEnabled = true

func disableTooltip():
	tooltipEnabled = false
	if tooltip:
		tooltip.discard()
		tooltip = null

func disableFocus():
	
	focusEnabled = false
	if focus:
		loseFocus()

func enableFocus():
	focusEnabled = true

func setEditMode(active: bool):
	if active:
		if ownerType != Owner.Shop or affordable:
			enablePicking()
		enableFocus()
		clickArea.show()
		modulate.a = 1.0
		setShadowAlpha(1.0)
	else:
		if hovered: hoverEnd()
		disableFocus()
		clickArea.hide()
		disablePicking()
		modulate.a = 0.6
		setShadowAlpha(0.3)

func setShadowAlpha(alpha: float):
	for shadow in shadows:
		shadow.self_modulate.a = alpha

func getCellsForGlobalPositions(points: Array) -> Array:
	var cells = []
	for point in points:
		cells.push_back(collisionMap.world_to_map(point - collisionMap.global_position))
	return cells

func getGlobalPointsForCells(cells):
	var points = []
	for cell in cells:
		points.push_back(collisionMap.to_global(collisionMap.map_to_world(cell))
			+ halfCellSize.rotated(global_rotation))
	
	return points

func getGlobalPointsForCells_noRotate(cells):
	var points = []
	for cell in cells:
		points.push_back(collisionMap.global_position
			+ (collisionMap.map_to_world(cell))
			+ halfCellSize)

	return points

func getNumCells():
	return getNumOccupiedCells() + getNumBagCells()

func getNumOccupiedCells():
	return collisionCells.size()

func getNumBagCells():
	return extensionCells.size()
	
func getCollisionCells():
	return collisionCells



func getNormalizedCollisionCells() -> Array:
	var cells
	if isBag():
		cells = getExtensionCells().duplicate()
	else:
		cells = getCollisionCells().duplicate()
	
	
	var minimum = Vector2(100, 100)
	for cell in cells:
		
		if cell.y <= minimum.y:
			if cell.y < minimum.y:
				minimum.x = cell.x
			else:
				
				minimum.x = min(cell.x, minimum.x)
			minimum.y = cell.y
	
	for i in cells.size():
		cells[i] = cells[i] - minimum
	
	
	var cellOffset = collisionMap.map_to_world(minimum) + collisionMap.position + Vector2(40, 40)
	
	
	
	return [cells, cellOffset]
	

func getCollisionPoints():
	return getGlobalPointsForCells(getCollisionCells())

func getOwnOrPlayerInventory():
	if placed:
		return inventory
	else:
		return Game.PLAYER.INVENTORY



func getAffectedCells_tilemap(color = Affected.Primary) -> Array:
	return collisionMap.get_used_cells_by_id(affectedColorToTileId[color])



func getAffectedCellsAfterRotate(rotatedCells, color = Affected.Primary) -> Array:
	if color == Affected.Primary:
		return getAffectedCellsAfterRotate_primary(rotatedCells)
	elif color == Affected.Secondary:
		return getAffectedCellsAfterRotate_secondary(rotatedCells)
	else:
		return []

func getAffectedCellsAfterRotate_primary(_rotatedCells):
	return []

func getAffectedCellsAfterRotate_secondary(_rotatedCells):
	return []
	

func getAffectedCells_noRotate(color = Affected.Primary):
	var globalCollisionPoints = getCollisionPoints()
	var rotatedCells = getCellsForGlobalPositions(globalCollisionPoints)
	var affectedCells = getAffectedCellsAfterRotate(rotatedCells, color)
	var affectedPoints = getGlobalPointsForCells_noRotate(affectedCells)
	return affectedPoints

func getNumAffectedCells(color = Affected.Primary) -> int:
	if color in affectedCellsCache:
		return affectedCellsCache[color].size()
	else:
		return getAffectedCells_tilemap(color).size() + getAffectedCells_noRotate(color).size()

func getAffectedPoints(color = Affected.Primary) -> Array:
	return getGlobalPointsForCells(getAffectedCells_tilemap(color)) + getAffectedCells_noRotate(color)

func getAffectedCellsInInventory(color = Affected.Primary) -> Array:
	return getOwnOrPlayerInventory().getCellsForGlobalPositions(getAffectedPoints(color))


func getItemsInAffectedCells_cached(color = Affected.Primary) -> Array:
	return getOwnOrPlayerInventory().getItemsInCells(getAffectedCellsInInventory_cached(color))

func getItemsInAffectedCells(color = Affected.Primary) -> Array:
	return getOwnOrPlayerInventory().getItemsInCells(getAffectedCellsInInventory(color))

func countItemsInAffectedCells_cached(color = Affected.Primary) -> Dictionary:
	return getOwnOrPlayerInventory().countItemsInCells(getAffectedCellsInInventory_cached(color))

func getAffectedItems(color = Affected.Primary) -> Array:
	if not cachedAffectedItems.empty():




		return cachedAffectedItems[color]
	
	var items = []
	for item in getItemsInAffectedCells_cached(color):
		if canAffect_color(item, color):
			items.push_back(item)
	return items

func getAffectedItems_nocache(color = Affected.Primary) -> Array:
	var items = []
	for item in getItemsInAffectedCells(color):
		if canAffect_color(item, color):
			items.push_back(item)
	return items

func isItemAffected(item, color = Affected.Primary) -> bool:
	if item.isBag() or not canAffect_color(item, color):
		return false
	
	var affectedTiles = getAffectedCellsInInventory_cached(color)
	
	for cell in item.occupiedCells:
		if cell in affectedTiles:
			return true
	return false
			
func getNumEmptyAffectedCells(color = Affected.Primary) -> int:
	return inventory.getEmptyCellsInCells(getAffectedCellsInInventory(color))

func getNumAffectedItems(color = Affected.Primary) -> int:
	return getAffectedItems(color).size()

func getFirstAffectedItem(color = Affected.Primary):
	var _affectedItems = getAffectedItems(color)
	if not _affectedItems.empty():
		return _affectedItems[0]
	return null

func getNumAffected_type(type: int, color = Affected.Primary) -> int:
	var num = 0
	for item in getAffectedItems(color):
		num += item.getTypeMultiplicity(type)
	return num

func getExtensionCells():
	return extensionCells

func getExtensionPoints():
	return getGlobalPointsForCells(getExtensionCells())

	
const correction = [
	Vector2.ZERO, 
	Vector2( - cellSize.x, 0), 
	Vector2( - cellSize.x, - cellSize.y), 
	Vector2(0, - cellSize.y)
]



func getTopLeftGlobal() -> Vector2:
	var topLeft = Vector2(INF, INF)
	for cell in collisionCells:
		var globalPos = collisionMap.to_global(collisionMap.map_to_world(cell))
		topLeft.x = min(globalPos.x, topLeft.x)
		topLeft.y = min(globalPos.y, topLeft.y)
	return topLeft + correction[getFaceDirection()]

func getBottomRightGlobal() -> Vector2:
	var bottomRight = Vector2( - INF, - INF)
	for cell in collisionCells:
		var globalPos = collisionMap.to_global(collisionMap.map_to_world(cell))
		bottomRight.x = max(globalPos.x, bottomRight.x)
		bottomRight.y = max(globalPos.y, bottomRight.y)
	return bottomRight + cellSize

func getHeightRange() -> Vector2:
	return Vector2(getTopLeftGlobal().y, getBottomRightGlobal().y)


func getTopLeftCell() -> Vector2:
	var topLeft = Vector2(INF, INF)
	for cell in occupiedCells:
		topLeft.x = min(cell.x, topLeft.x)
		topLeft.y = min(cell.y, topLeft.y)
	return topLeft


func getBottomCenter() -> Vector2:
	return $BottomCenter.position








	
func previewCells():
	if not isBag():
		collisionMap.show()
	
	
	
	var globalCollisionPoints = getCollisionPoints()
	var rotatedCells = getCellsForGlobalPositions(globalCollisionPoints)
	for color in [Affected.Primary, Affected.Secondary]:
		var nonMappedCells = getAffectedCellsAfterRotate(rotatedCells, color)
		
		if not nonMappedCells.empty():
			for cell in collisionMap.get_used_cells_by_id(Tiles.AffectedDynamic + color):
				collisionMap.set_cellv(cell, - 1)
			
			for cell in nonMappedCells:
				collisionMap.set_cellv(cell, Tiles.AffectedDynamic + color)


func activateExtendedAffectedCells():
	for cell in affectedExtensionCells:
		collisionMap.set_cellv(cell, Tiles.Affected)
	cacheAffectedCells()

func deactivateExtendedAffectedCells():
	for cell in affectedExtensionCells:
		collisionMap.set_cellv(cell, - 1)
	cacheAffectedCells()

func getEffectiveOwnerType() -> int:
	return ownerType

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

func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	
	
	
	placedByPlayer = _placedByPlayer
	placed = true
	inventory = _inventory
	occupiedCells = _occupiedCells
	if ownerType != Owner.BuildViewer:
		if inventory == Game.PLAYER.INVENTORY:
			ownerType = Owner.PlayerInventory
		elif inventory == Game.OPPONENT.INVENTORY:
			ownerType = Owner.Opponent
	
	inventory.connect("item_added", self, "onItemAdded")
	inventory.connect("item_removed", self, "onItemRemoved")
	inventory.connect("item_type_changed", self, "onItemTypeChanged")
	
	if ownerType != Owner.BuildViewer:
		CraftingManager.itemAdded(self)
		for gem in getGemsNoNull():
			CraftingManager.itemAdded(gem)
	
	cacheAffectedCells()
	
	
	for color in Affected.values():
		for item in getAffectedItems(color):
			currentAffectedItems[color][item] = true
			onAffectedItemAdded(item, color)
	
	makeGrabbable(false)
	
	onAddToInventory()
	
	if ownerType == Owner.PlayerInventory:
		if has_method("getGatedDescriptor"):
			Game.shopSceneNode.connect("gate_item_roll", self, "onGateItemRoll")
		Util.connectIfExists(Game.shopSceneNode, "roll_sale", self, "onSaleRoll")
		Util.connectIfExists(ItemBook, "pre_item_roll", self, "onItemRoll")
		Util.connectIfExists(ItemBook, "item_rolled", self, "onItemRolled")
		Util.connectIfExists(ItemBook, "items_counted", self, "onItemsCounted")
		Util.connectIfExists(Game.SELLBOX, "calc_trade_chance", self, "onCalcTradeChance")
	
	emit_signal("added_to_inventory")

func onGateItemRoll():
	if rollShopChance():
		Game.shopSceneNode.addGateItem(self)

func cacheAffectedCells():
	for color in Affected.values():
		affectedCellsCache[color] = getAffectedCellsInInventory(color)

func removeFromInventory():
	if not placed: return
	
	placed = false

	CraftingManager.itemRemoved(self)
	for gem in getGemsNoNull():
		CraftingManager.itemRemoved(gem)
	
	
	inventory.disconnect("item_added", self, "onItemAdded")
	inventory.disconnect("item_removed", self, "onItemRemoved")
	inventory.disconnect("item_type_changed", self, "onItemTypeChanged")
	
	for color in Affected.values():
		for item in currentAffectedItems[color]:
			onAffectedItemRemoved(item, color)

	cleanCachedAffectedItems()
	
	onRemoveFromInventory()
	
	Util.tryDisconnect(Game.shopSceneNode, "gate_item_roll", self, "onGateItemRoll")
	Util.tryDisconnect(Game.shopSceneNode, "roll_sale", self, "onSaleRoll")
	Util.tryDisconnect(ItemBook, "pre_item_roll", self, "onItemRoll")
	Util.tryDisconnect(ItemBook, "item_rolled", self, "onItemRolled")
	Util.tryDisconnect(ItemBook, "items_counted", self, "onItemsCounted")
	Util.tryDisconnect(Game.SELLBOX, "calc_trade_chance", self, "onCalcTradeChance")

func cleanCachedAffectedItems():
	affectedCellsCache.clear()
	
	
	for color in Affected.values():
		currentAffectedItems[color].clear()
	
	Util.eassert(cachedAffectedItems.empty())

func playAffectedPlacedAnimation(newItemIsAffected: Dictionary):
	var sum = 0
	for color in newItemIsAffected:
		sum += int(newItemIsAffected[color])
	
	if sum > 1:
		animation.play("AffectedPlaced")
	elif newItemIsAffected[Affected.Primary]:
		animation.play("AffectedPlaced_Primary")
	elif newItemIsAffected[Affected.Secondary]:
		animation.play("AffectedPlaced_Secondary")
	elif newItemIsAffected[Affected.Tertiary]:
		animation.play("AffectedPlaced_Tertiary")
	elif newItemIsAffected[Affected.Lightning]:
		animation.play("AffectedPlaced_Lightning")
	



func onItemAdded(item):
	
	
	
	
	var newItemIsAffected = {}
	for color in Affected.values():
		newItemIsAffected[color] = ( not item in currentAffectedItems[color] and 
									isItemAffected(item, color))
	
	if item.placedByPlayer:
		playAffectedPlacedAnimation(newItemIsAffected)
	
	for color in Affected.values():
		if newItemIsAffected[color]:
			currentAffectedItems[color][item] = true
			onAffectedItemAdded(item, color)



func onItemRemoved(item):
	for color in Affected.values():
		currentAffectedItems[color].erase(item)
		if canAffectDraggedItem(item, color):
			
			onAffectedItemRemoved(item, color)

	

func onItemTypeChanged(item):


	
	var canAddAgain = reactToItemTypeChange(item)
	
	if not canAddAgain:
		return
	
	var addedToAffected = {}
	for color in Affected.values():
		addedToAffected[color] = false
	
		if item in currentAffectedItems[color]:
			
			if not canAffect_color(item, color):
				currentAffectedItems[color].erase(item)
				onAffectedItemRemoved(item, color)
		elif item in getAffectedItems(color):
			currentAffectedItems[color][item] = true
			onAffectedItemAdded(item, color)
			addedToAffected[color] = true
	
	if item.placedByPlayer:
		playAffectedPlacedAnimation(addedToAffected)

func getAffectedCellsInInventory_cached(color):
	return affectedCellsCache.get(color, [])

func canAffectDraggedItem(item, color):
	if canAffect_color(item, color):
		
		var affectedCells = getAffectedCellsInInventory_cached(color)
		
		for cell in affectedCells:
			if item.dragged:
				if inventory.isHovered(cell):
					return true
			else:
				if cell in item.occupiedCells:
					return true
	return false















func onAddToInventory():
	pass

func onAffectedItemAdded(item, color: int):
	
	pass

func onAffectedItemRemoved(item, color: int):
	
	pass


func onRemoveFromInventory():
	pass


func reactToItemTypeChange(item) -> bool:
	return true

func onSold():
	pass

func onBought():
	pass

const canAffectVisual = preload("res://Items/Exclusive/Animations/CanAffectVisual.tscn")
var canAffectVisuals = []

func previewCanAffect():
	var visuals: = {}
	
	var itemDict
	if ownerType == Owner.Opponent:
		itemDict = ItemBook.opponentItems
	else:
		itemDict = ItemBook.ownableItems
	
	for color in Affected.values():
		var curAffected = getAffectedItems(color)
		
		for descr in itemDict:
			for item in itemDict[descr]:
				if (item != self and 
					not item.isBag() and 
					( not item.isGem() or item.socket == null)
					and canAffect_color(item, color)
					and not item in curAffected):
					
					var visual = visuals.get(item, null)
					if visual == null:
						visual = ObjectPool.instance(canAffectVisual)
						item.add_child(visual)
						
						canAffectVisuals.push_back(visual)
						visuals[item] = visual
					visual.setColorActive(color)

func clearCanAffectVisuals():
	for visual in canAffectVisuals:
		visual.returnToObjectPool()
	canAffectVisuals.clear()



func liesInStorage() -> bool:
	return ownerType == Owner.PlayerStorageBox and not dragged

func pushToStorage(targetPos = Game.STORAGEBOX.center):
	if isBag():
		z_index = 41
	else:
		z_index = 42
	addToStorageBox(true, true, true, targetPos, 1.0, true)

func addToStorageBox(addImpulse = true, tweenBouncyness: bool = true, 
	checkCollisions = true, targetPos = global_position, speed = 1.0, secondCheck = false):
	
	ownerType = Owner.PlayerStorageBox
	Game.STORAGEBOX.addItem(self)
	occupiedCells.clear()
	Util.reparent(self, Game.STORAGEBOX)
	for particles in specificDragParticles:
		if particles is Particles2D:
			particles.set_visibility_rect(Rect2( - 2000, - 2000, 4000, 4000))
	
	Util.killTween(rotationTween)
	rotation += sprite.rotation
	sprite.rotation = 0
	


	
	if not tweenBouncyness:
		physics_material_override.bounce = 0.0
		physics_material_override.friction = 1.0
	
	if checkCollisions:
		
		moveToFreeSpaceInStorage(targetPos, addImpulse, speed, secondCheck, tweenBouncyness)
	else:
		if mode != RigidBody2D.MODE_RIGID:
			makeRigidBody()
	
	makeGrabbable(true)
	
	Util.connectIfExists(Game.shopSceneNode, "roll_sale", self, "onSaleRoll_storage")
	Util.connectIfExists(Game.shopSceneNode, "gate_item_roll", self, "onGateItemRoll_storage")
	
	onAddedToStorageBox()

func removeFromStorage():
	Util.reparent(self, Game.playerNode)

	killMovebackTween()
	onStorageLeft()

func onStorageLeft():
	makeNonRigidBody()
	Game.STORAGEBOX.removeItem(self)
	Util.tryDisconnect(Game.shopSceneNode, "roll_sale", self, "onSaleRoll_storage")
	Util.tryDisconnect(Game.shopSceneNode, "gate_item_roll", self, "onGateItemRoll_storage")

func isInGridStorage() -> bool:
	return (getEffectiveOwnerType() == Owner.PlayerStorageBox and 
		Game.gridStorage.visible)

func getGridStorageProxy():
	if not dragged and isInGridStorage():
		
		var proxy = Game.gridStorage.getProxy(self)
		if proxy != null:
			return proxy
	
	return self

func onAddedToGridStorage():
	hide()
	disablePicking()
	for particles in specificDragParticles:
		particles.instantClear()
	dragParticles.instantClear()

func onRemovedFromGridStorage():
	show()
	Game.setItemEditMode(self, false)
	for gem in getGemsNoNull():
		gem.onRemovedFromGridStorage()

func makeGrabbable(extended: bool):
	set_collision_layer_bit(3, extended)
	

func moveToFreeSpaceInStorage(targetPos = global_position, 
	addImpulse = false, speed = 1.0, secondCheck = false, 
	tweenBouncyness: bool = true):
	
	resetSprite()
	
	targetPos = Util.clampToRect(targetPos, Game.STORAGEBOX.getStorageRect())
	var freePos = findFreeSpace(targetPos)
	var dif = freePos - global_position
	var length = dif.length()
	if length > 50:
		var dur: float = length * 0.001 / (speed * Util.rng.randf_range(0.8, 1.2))
		dur = clamp(dur, 0.1, 0.5)
		killMovebackTween()
		movebackTween = create_tween()
		movebackTween.tween_property(self, "global_position", freePos, dur)
		movebackTween.tween_callback(self, "makeRigidBody")
		movebackTween.tween_callback(self, "resetZ")
		
		
		
		if isGem():
			set_deferred("z_index", 34)
		elif isBag():
			set_deferred("z_index", 32)
		else:
			set_deferred("z_index", 33)
		
		if addImpulse:
			movebackTween.tween_callback(self, "dropImpulse", [dif, tweenBouncyness])
		
		if secondCheck:
			movebackTween.tween_callback(self, "moveToFreeSpaceInStorage", 
				[targetPos, addImpulse, speed, false])
		else:
			movebackTween.tween_callback(self, "checkIfOutofStorageBounds")
	else:
		resetZ()
		global_position = freePos
		makeRigidBody()
		if addImpulse:
			dropImpulse(null, tweenBouncyness)



func checkIfOutofStorageBounds():
	Util.callNextFrame(self, "checkIfOutofStorageBounds2")

func checkIfOutofStorageBounds2():
	Util.callNextFrame(self, "checkIfOutofStorageBounds3")
	
func checkIfOutofStorageBounds3():
	if ownerType == Owner.PlayerStorageBox:
		Game.STORAGEBOX.checkIfItemIsInStorageArea(self)

const angleStep = 45

func findFreeSpace(startPos: Vector2) -> Vector2:
	var spaceState = get_world_2d().get_direct_space_state()
	var query: Physics2DShapeQueryParameters = Physics2DShapeQueryParameters.new()
	var shape
	
	if collisionShape is CollisionShape2D:
		shape = collisionShape.shape
	else:
		
		
		shape = ConvexPolygonShape2D.new()
		shape.points = collisionShape.polygon
	
	query.set_shape(shape)
	query.collide_with_bodies = true
	if ownerType == Owner.Title:
		query.collision_layer = 4 + 1
	else:
		query.collision_layer = 1
	query.collide_with_areas = false
	query.transform = get_global_transform()
	query.exclude = [self]
	query.transform.origin = startPos
	var freePos = startPos
	var initialCollisions = spaceState.collide_shape(query, 1)
	if initialCollisions.empty():
		return freePos
	
	var tries = 0
	
	for offset in [20, 40, 70, 100, 150, 200, 250, 300, 400, 500, 600]:
		for angle in range(angleStep, 360 + angleStep, angleStep):
			freePos = startPos + (Vector2.UP * offset).rotated(deg2rad(angle))
			query.transform.origin = freePos
			var collisions = spaceState.collide_shape(query, 1)
			
			tries += 1
			if collisions.empty():
				
				return freePos
	
	
	return freePos

func unclip():
	global_position = findFreeSpace(global_position)

func onAddedToStorageBox():
	pass

func previewCellCollision():
	Game.PLAYER.INVENTORY.previewItem(self)

var rotationMomentum = 0
var bonusRotation = 0

const moveRotationMouseFactor = 0.015
const backforce = 5.0
const fric = 15.0
const maxAngle = 10
const moveRotationSpeed = 60.0



func _process(delta: float) -> void :
	
	
	
	if Game.state != Game.State.Combat and animation.current_animation == "":
		sprite.modulate = Color.white
	
	if focus and Game.tooltipsEnabled():
		if placed:
			inventory.previewAffectedCells(self)
		
		
		else:
			if affectedCellsActive:
				Game.PLAYER.INVENTORY.previewAffectedCells(self)
	
	if dragged:
		var pos = global_position
		global_position = Util.getMousePosInWindow()
		global_position.y -= Settings.getVal(Settings.Setting.pick_offset) * Settings.PICK_OFFSET
		
		var dif = global_position - pos
		var speed = dif.length() / delta
		var direction = dif.normalized()
		momentumStrength = lerp(momentumStrength, speed / 60, 20 * delta)
		
		momentumStrength = min(momentumStrength, 150.0)
		momentum = direction * momentumStrength
		
		if momentumStrength > Util.rng.randf_range(5, 15):
			dragParticles.activate()
		else:
			dragParticles.deactivate()
		
		Sound.itemMovePlayer.volume_db = linear2db(clamp((momentumStrength - 20) / 100.0, 0, 1) * (0.5 + 0.1 * getNumCells()))
		
		if draggedInsideItems.empty():
			var mainDif
			if abs(dif.x) > abs(dif.y):
				mainDif = dif.length() * sign(dif.x)
			else:
				mainDif = - dif.length() * sign(dif.y)
			
			rotationMomentum += mainDif * moveRotationMouseFactor
			
			rotationMomentum -= bonusRotation * backforce * delta
			
			rotationMomentum *= max(0, 1 - (fric * delta))
			
			bonusRotation += rotationMomentum * moveRotationSpeed * delta
			bonusRotation = clamp(bonusRotation, - maxAngle, maxAngle)
			
			sprite.rotation_degrees = bonusRotation
			
			
		
		
		if Util.isActionJustPressed("rotate_right_button"):
			rotateRight()
		elif Util.isActionJustPressed("rotate_left_button"):
			rotateLeft()
		
		if Util.time >= mouseWheelRotationReadyTime:
			if Util.isActionJustPressed("rotate_right", false):
				rotateRight()
				mouseWheelRotationReadyTime = Util.time + 0.1
			elif Util.isActionJustPressed("rotate_left", false):
				rotateLeft()
				mouseWheelRotationReadyTime = Util.time + 0.1
		
		previewCellCollision()
	
	elif placed and Game.state != Game.State.Combat and not Game.SELECTING:
		var focusItem = Game.getFocusItem()
		if (focusItem != null and 
			focusItem != self and 
			(focusItem.placed or focusItem == Game.draggedItem) and 
			not focusItem.isBag()):
			var affectedPrimary = canAffectDraggedItem(focusItem, Affected.Primary)
			var affectedSecondary = canAffectDraggedItem(focusItem, Affected.Secondary)
			var affectedTertiary = canAffectDraggedItem(focusItem, Affected.Tertiary)
			var affectedLightning = canAffectDraggedItem(focusItem, Affected.Lightning)
			
			var sum = int(affectedPrimary) + int(affectedSecondary) + int(affectedTertiary)
			if sum > 1:
				sprite.modulate = Color(1.3, 1.3, 1.3, 1)
			elif affectedPrimary:
				
				sprite.modulate = Color(1.3, 1.3, 0.8, 1)
			elif affectedSecondary:
				sprite.modulate = Color(1.0, 1.3, 0.9, 1)
			elif affectedTertiary:
				sprite.modulate = Color(1.3, 0.9, 1.3, 1)
			elif affectedLightning:
				sprite.modulate = Color(1.35, 1.25, 1.0, 1)
				
	updateShadow()
	if lock.visible:
		lock.global_rotation = 0
		
	if mode == RigidBody2D.MODE_RIGID and visible:
		averagedPosition = lerp(averagedPosition, global_position, 1.5 * delta)
		var posDif = (averagedPosition - global_position).length()
		
		
		var curVelocity = get_linear_velocity()
		var acceleration = (lastVelocity - curVelocity).length()
		
		if posDif > 30 and acceleration > 50:
			
			if Util.time >= impactSoundReadyTime:
				playDropSound(Util.rng.randf_range( - 15, - 10))
				impactSoundReadyTime = Util.time + 0.5
			
			var particles = ObjectPool.particleOneShot(dustParticles, get_parent().get_parent())
			if acceleration > 200:
				particles.amount = 12
			else:
				particles.amount = 6
			
			particles.z_index = get_parent().z_index - 1
			
			var dir = lastVelocity.normalized()
			particles.process_material.direction = Vector3(dir.x, dir.y, 0)
			particles.process_material.initial_velocity = lastVelocity.length() * 0.4 + 120.0
			particles.global_position = lastCollisionPos
			
			
			
			
			if (is_instance_valid(lastCollider) and not Util.isItem(lastCollider) and 
				lastCollisionPos.y > 770):
				var impulse = acceleration * totalWeight
				if impulse > 2000:
					Game.STORAGEBOX.shake(lastCollisionPos, true)
				elif impulse > 800:
					Game.STORAGEBOX.shake(lastCollisionPos, false)
			
			particles.scale = Vector2(0.3, 0.3) * sqrt(getNumCells()) + Vector2(0.1, 0.1)
			
		lastVelocity = curVelocity


func _integrate_forces(state: Physics2DDirectBodyState) -> void :
	if state.get_contact_count() > 0:
		lastCollisionPos = state.get_contact_local_position(0)
		lastCollider = state.get_contact_collider_object(0)
	else:
		lastCollider = null

func updateShadow():
	
	
	for i in shadows.size():
		var shadow = shadows[i]
		var node = spritesWithShadows[i]
		shadow.global_position = node.global_position + shadowOffset
		shadow.global_rotation = node.global_rotation
		shadow.global_scale = node.global_scale
		shadow.offset = node.offset








func lerpAngle_local(interpolationPoint, from, to):
	sprite.rotation = lerp_angle(from, to, interpolationPoint)
	updateInsideRotationNode()
	updateShadow()

func updateInsideRotationNode():
	if insideRotationNode != null:
		insideRotationNode.global_rotation = sprite.global_rotation

func rotateRight():
	faceDirection += 1
	faceDirection = faceDirection % FaceDirection.size()
	setFaceDirection(faceDirection)
	Sound.playSound(rotateSound, - 6, Util.rng.randf_range(0.8, 1.3))
	spawnRotationSparks(true)
	Game.onItemRotated()


func rotateLeft():
	faceDirection -= 1
	faceDirection += FaceDirection.size()
	faceDirection = faceDirection % FaceDirection.size()
	setFaceDirection(faceDirection)
	Sound.playSound(rotateSound, - 6)
	spawnRotationSparks(false)
	Game.onItemRotated()

	

func spawnRotationSparks(rotateRight):
	var rotationSparks = createParticles(rotationSparksScene)
	rotationSparks.modulate = Game.rarityColors[getRarity()].lightened(0.2)
	
	if rotateRight:
		rotationSparks.scale.x = - abs(rotationSparks.scale.x)
	else:
		rotationSparks.scale.x = abs(rotationSparks.scale.x)


func setFaceDirection(_faceDirection):
	rotateTo(_faceDirection * PI * 0.5)

func rotateTo(targetRotation, duration = 0.15):
	rotationTween = Util.refreshTween(rotationTween)
	rotationTween.set_process_mode(Tween.TWEEN_PROCESS_IDLE)
	
	
	
	
	var curRotation = sprite.global_rotation
	global_rotation = targetRotation
	faceDirection = getGlobalFaceDirection()
	sprite.global_rotation = curRotation
	updateInsideRotationNode()
	
	rotationTween.tween_method(self, "lerpAngle_local", 0.0, 1.0, duration, 
		[sprite.rotation, 0.0])
	







	
	updateShaderRotation()
	updateShadow()
	
	
	
	if isMovingBack():
		rotationTween.tween_callback(self, "reparentItemsInside")
	else:
		rotationTween.tween_callback(self, "correctInsideItemFacedirection")
	
	call_deferred("rotateToDeferred", targetRotation)

func rotateToDeferred(targetRotation):
	
	setRotation(targetRotation)

func rotationFromFaceDirection(_faceDirection):
	return _faceDirection * PI * 0.5

func getGlobalFaceDirection():
	return (int((2 * global_rotation) / PI + 2.25 * PI) + 5) % 4

func setFaceDirectionInstant(_faceDirection):
	
	Util.finishTween(rotationTween)
	faceDirection = _faceDirection
	rotation = rotationFromFaceDirection(faceDirection)

func setRotation(_rotation):
	global_rotation = _rotation


func getFaceDirection():
	return (int((2 * rotation) / PI + 2.25 * PI) + 5) % 4

func highlight():
	sprite.position = Vector2.ZERO
	animation.play("Highlight")
	
func unhighlight():
	resetSprite()

var brightColor = Color(1.3, 1.3, 1.3, 1)
var defaultColor = Color.white

func setBright():
	modulate = brightColor

func resetBright():
	modulate = defaultColor

func getHoverPriority():
	if dragged: return DRAG_PRIORITY
	else: return 0

func canGainFocus():
	return ( not Game.SELECTING and 
		( not Game.draggedItem or Game.draggedItem == self) and 
		focusEnabled and 
		not focus)

func gainFocus():
	if not canGainFocus(): return
	
	
	if (ownerType == Owner.PlayerInventory or 
		ownerType == Owner.Socket or 
		ownerType == Owner.Opponent):
		Game.combatLog.highlightItem(self, false)
	
	
	focus = true
	respondToHover()

func respondToHover():
	if hoverResponseEnabled and Game.hoverResponseEnabled():
		if ( not isBag() or ownerType == Owner.Shop) and Engine.time_scale > 0:
			
			var particles = createParticles(hoverSparksScene, Vector2(0.7, 0.7))
			particles.modulate = Game.rarityColors[getRarity()].lightened(0.2)
			
			Sound.playSound_process(hoverSound, 0, Util.rng.randf_range(0.9, 1.2))
			
			if dragParticlesEnabled:
				activateDragParticles()
		
		setBright()
		previewFusions()
		
		if isOwnable() or isOwnedByOpponent():
			if has_method("canAffect_global"):
				var inv = inventory if inventory != null else Game.PLAYER.INVENTORY
				for item in inv.getItems():
					if me.canAffect_global(item):
						var visual = ObjectPool.instance(globalAffectVisual)
						globalAffectVisuals.push_back(visual)
						item.add_child(visual)
	
	if not Game.tooltipsEnabled():
		return
	
	if ownerType == Owner.Shop:
		if not dragged:
			previewCells()
		z_index = max(z_index, 2)
		for shadow in shadows:
			shadow.z_index = - 2
	
	elif ownerType == Owner.RecipeBook or ownerType == Owner.ItemLibrary:
		z_index = max(z_index, 2)
		previewCells()
	
	if ownerType == Owner.ItemLibrary:
		showSockets()
	
	if tooltipEnabled:
		if not tooltip and not dragged:
			if ownerType == Owner.RecipeBook:
				tooltipMargin.x = 60
			
			var texSize = Util.absv((sprite.global_scale * sprite.texture.get_size()).rotated(rotation))
			var tooltipPos = global_position - texSize * 0.5 - tooltipMargin * 0.5
			var toolsize = tooltipMargin
			
			var ownerType_ = getEffectiveOwnerType()
			var inventory_ = getInventory()
			
			match ownerType_:
				Owner.Shop:
					tooltipPos.x = 550
				
				Owner.PlayerInventory:
					tooltipPos.x = inventory_.getRightBorder() + 30
				
				Owner.PlayerStorageBox:
					tooltipPos.x = 1800
				
				Owner.GridStorage:
					tooltipPos.x = 1800
				
				Owner.Opponent:
					tooltipPos.x = inventory_.getLeftBorder() - 700
				
				Owner.RecipeBook:
					toolsize += texSize
				
				Owner.ItemLibrary:
					tooltipPos.x = 1950
					
					
				
				Owner.BuildViewer:
					var leftBorder = inventory_.getLeftBorder()
					if leftBorder > 800:
						tooltipPos.x = leftBorder - 700
					else:
						tooltipPos.x = 450
				
				Owner.BuildViewerIcon:
					tooltipPos.x -= 50
					toolsize.x += 100
				
				Owner.Tooltip:
					if owningBuildIntoRecipesTooltip != null:
						match Game.lockedTooltipItem.getEffectiveOwnerType():
							Owner.Shop:
								tooltipPos.x = 610
							Owner.PlayerInventory:
								tooltipPos.x = Game.lockedTooltipItem.tooltip.rect_position.x - 108
							Owner.PlayerStorageBox:
								tooltipPos.x = 610
							Owner.ItemLibrary:
								toolsize.x += 50
					else:
						tooltipPos.x -= 50
						toolsize.x += 150
				
			if ownerType != Owner.RecipeBook:
				
				
				tooltip = ObjectPool.instance(tooltipScenes[getRarity()])
			else:
				tooltip = recipeTooltip.instance()

			Game.tooltipsNode.add_child(tooltip)
			tooltip.setItem(self)
			tooltip.forceUpdatePosition(tooltipPos, toolsize)
			
			if Game.showHintsIsPressed:
				if isOwnable() or isOwnedByOpponent():
					previewCanAffect()
				Game.clearAffectedLines()
				
				if (Game.RECIPE_TOOLTIPS_ENABLED and 
					canShowBuildIntoRecipesTooltip()):
					
					showBuildIntoRecipesTooltip()

const buildIntoRecipesTooltipScene = preload("res://Interface/Tooltips/BuildIntoRecipesTooltip.tscn")
var buildIntoRecipesTooltip = null
var owningBuildIntoRecipesTooltip = null
var ownerTypesWithBuildTooltip = {
	Owner.BuildViewer: true, 
	Owner.PlayerStorageBox: true, 
	Owner.PlayerInventory: true, 
	Owner.Opponent: true, 
	Owner.GridStorage: true
}

func canShowBuildIntoRecipesTooltip() -> bool:
	if dragged: return false
	
	var effectiveOwner = getEffectiveOwnerType()
	
	if ownerType == Owner.Tooltip and owningBuildIntoRecipesTooltip != null:
		if not canShowSubBuildIntoRecipesTooltip():
			return false
	elif not (ownerType == Owner.Shop or 
			ownerType == Owner.ItemLibrary or 
			effectiveOwner in ownerTypesWithBuildTooltip):
		return false
	
	var descr = getRecipeDescriptor()
	if descr.getNumRecipes() > 0:
		return true
	
	if getRelatedItems().size() > 0:
		return true
		
	return false

func canShowSubBuildIntoRecipesTooltip():
	var ownerType_ = Game.lockedTooltipItem.getEffectiveOwnerType()
	return (ownerType_ == Owner.Shop or 
			ownerType_ == Owner.PlayerInventory or 
			ownerType_ == Owner.PlayerStorageBox)

func showBuildIntoRecipesTooltip():
	if buildIntoRecipesTooltip != null: return
	
	var descr = getRecipeDescriptor()
	if (descr.getNumRecipes() > 0 or 
		getRelatedItems().size() > 0):
		
		buildIntoRecipesTooltip = buildIntoRecipesTooltipScene.instance()
		
		if ownerType == Owner.Tooltip:
			Game.tooltipsNode.add_child(buildIntoRecipesTooltip)
		else:
			Game.recipeTooltipsNode.add_child(buildIntoRecipesTooltip)
		
		var ownerType_ = getEffectiveOwnerType()
		var inventory_ = getInventory()
		
		var tooltipPos = Vector2(0, 0)
		
		match ownerType_:
			Owner.Shop:
				tooltipPos.x = 180
				buildIntoRecipesTooltip.growToRight = false
			
			Owner.PlayerInventory:
				tooltipPos.x = inventory_.getRightBorder() + 680
				buildIntoRecipesTooltip.growToRight = true
			
			Owner.PlayerStorageBox:
				tooltipPos.x = 260
				buildIntoRecipesTooltip.growToRight = false
			
			Owner.ItemLibrary:
				
				if position.x < 900:
					tooltipPos.x = 870
					buildIntoRecipesTooltip.growToRight = false
				else:
					tooltipPos.x = 0
					buildIntoRecipesTooltip.growToRight = true
				
			Owner.Opponent:
				tooltipPos.x = inventory_.getLeftBorder() - 1080
				buildIntoRecipesTooltip.growToRight = false
			
			Owner.BuildViewer:
				tooltipPos.x = inventory_.getLeftBorder() - 1080
				buildIntoRecipesTooltip.growToRight = false
			
			Owner.GridStorage:
				tooltipPos.x = 260
				buildIntoRecipesTooltip.growToRight = false
			
			Owner.Tooltip:
				match Game.lockedTooltipItem.getEffectiveOwnerType():
					Owner.Shop:
						tooltipPos.x = 1250
						buildIntoRecipesTooltip.growToRight = true
					Owner.PlayerInventory:
						tooltipPos.x = Game.lockedTooltipItem.getInventory().getRightBorder() - 350
						if tooltipPos.x < - 100:
							tooltipPos.x = owningBuildIntoRecipesTooltip.rect_position.x + owningBuildIntoRecipesTooltip.rect_size.x - 50
							buildIntoRecipesTooltip.growToRight = true
						else:
							buildIntoRecipesTooltip.growToRight = false
					Owner.PlayerStorageBox:
						tooltipPos.x = 1250
						buildIntoRecipesTooltip.growToRight = true
		
		buildIntoRecipesTooltip.rect_position = tooltipPos
		buildIntoRecipesTooltip.setItem(self, ownerType_ == Owner.Tooltip)
		
		
		var recipeTop = buildIntoRecipesTooltip.rect_position.y
		
		var recipeCenter = recipeTop + 0.5 * buildIntoRecipesTooltip.rect_size.y
		var tooltipCenter = tooltip.rect_position.y + 0.5 * tooltip.rect_size.y
		
		var targetTop
		if spotlight:
			targetTop = Game.itemLibrary.SPOTLIGHT_POS.y - 0.5 * buildIntoRecipesTooltip.rect_size.y
		else:
			targetTop = recipeTop + tooltipCenter - recipeCenter
		
		targetTop = max(0, targetTop)
		
		var bottom = targetTop + buildIntoRecipesTooltip.rect_size.y
		if bottom > 1100:
			targetTop -= bottom - 1100
		
		buildIntoRecipesTooltip.rect_position.y = targetTop
		
		Game.setTutorialDone(Game.TutorialSteps.ShowRecipes)

func getRelatedItems() -> Array:
	return descriptor.gatedItems

func getRelatedItemColumns() -> int:
	return 5

func getRelatedItemHeight() -> int:
	return 150

func getRecipeDescriptor():
	return descriptor


func hideBuildIntoRecipesTooltip():
	if buildIntoRecipesTooltip != null:
		buildIntoRecipesTooltip.discard()
		buildIntoRecipesTooltip = null

func loseFocus():
	if dragged: return
	
	if not focus: return
	
	
	
	respondToHoverEnd()
	focus = false

func respondToHoverEnd():
	collisionMap.hide()
	if tooltipEnabled:
		
		resetBright()
		if Game.showHintsIsPressed:
			Game.showAffectedLines()
		if Game.lockedTooltipItem != self:
			clearTooltip()
	
	CraftingManager.hideFusionPreviews(isMovingBack())
	Game.combatLog.unhighlightItem(false)
	
	if dragParticlesEnabled:
		deactivateDragParticles()
	
	for visual in globalAffectVisuals:
		ObjectPool.returnInstance(visual)
	globalAffectVisuals.clear()
	
	if ownerType == Owner.Shop:
		resetZ()
		for shadow in shadows:
			shadow.z_index = - 1
	elif ownerType == Owner.RecipeBook or ownerType == Owner.ItemLibrary:
		resetZ()
	
	if ownerType == Owner.ItemLibrary:
		hideSockets()

func activateDragParticles():
	for specificParticles in specificDragParticles:
		specificParticles.activate()

func deactivateDragParticles():
	for specificParticles in specificDragParticles:
		specificParticles.deactivate()


func updateTooltip():
	tooltipUpdateQueued = false
	if tooltip != null:
		tooltip.updateTooltip()

func queueTooltipUpdate():
	if tooltip != null and not tooltipUpdateQueued:
		tooltipUpdateQueued = true
		call_deferred("updateTooltip")

func clearTooltip():
	if tooltip != null:
		tooltip.discard()
		tooltip = null
	
	hideBuildIntoRecipesTooltip()
	clearCanAffectVisuals()

func mouseEntered():
	Game.onItemUnderMouse(self)
	if Game.itemsUnderMouse.size() > 10:
		Util.eprint("items under mouse: ", Game.itemsUnderMouse)
	
	hover()

const hoverableWhenMenuOpen = {
	Owner.ItemLibrary: true, 
	Owner.InfoPanelIcon: true, 
	Owner.Tooltip: true, 
	Owner.RecipeBook: true
}

func hover():
	
	if hovered:
		
		return

	if not tooltipEnabled: return
	if InputBlocker.isActive(): return
	
	
	if Game.lockedTooltipItem != null:
		if Game.lockedTooltipItem.buildIntoRecipesTooltip != owningBuildIntoRecipesTooltip:
			return
		if Game.lockedTooltipItem.isA(descriptor):
			return
	
	if spotlight: return
	
	if (Game.state == Game.State.Shop and 
		Game.isMenuOpen() and 
		not ownerType in hoverableWhenMenuOpen):
		return
	
	hovered = true
	
	Game.itemHovered(self)
	if Game.hasHoverFocus(self):
		gainFocus()
	
	emit_signal("hovered")

func mouseExited():
	Game.onItemUnderMouseExited(self)
	hoverEnd()


func hoverEnd():
	if not tooltipEnabled: return
	if spotlight: return
	if self == Game.lockedTooltipItem: return
	
	
	hovered = false
	loseFocus()
	
	Game.itemHoverEnd(self)
	
	emit_signal("unhovered")

func isHovered():
	return hovered or dragged

func getScaleProp() -> String:
	if hasSquishySprite:
		return "baseScale"
	else:
		return "scale"

func setSpriteScale(newScale: Vector2):
	if hasSquishySprite:
		sprite.baseScale = newScale
	sprite.scale = newScale

func resetZ():
	
	z_index = 1

func pickup(pickupType = PickupType.Grabbed):
	
	pickupFrame = Util.frameCounter
	resetSprite()
	
	if ownerType == Owner.Shop:
		Util.reparent(self, Game.playerNode)
		collisionMap.hide()
	
	elif ownerType == Owner.PlayerStorageBox:
		Util.reparent(self, Game.playerNode)
		
		if isInGridStorage():
			setFaceDirectionInstant(FaceDirection.UP)
		else:
			setFaceDirection(FaceDirection.UP)
		onStorageLeft()
	
	elif inventory != null and ownerType == Owner.PlayerInventory:
		pickupTopLeftCell = getTopLeftCell()
		pickupFaceDirection = getFaceDirection()
		
		inventory.removeItem(self)
		setBright()
		if pickupType == PickupType.MultiSelect:
			draggedInsideItems = inventory.getMultiSelectItems()
			for item in draggedInsideItems:
				if item.draggingParent:
					
					item.draggingParent.finishMoveback()
					
				
				item.onDraggedWithParentStart(self)
				
				inventory.removeItem(item)
				Util.reparent(item, insideRotationNode)
				item.resetBright()
		
		
		elif isBag():
			var hotswapBagWithDraggedItems = not Settings.getVal(Settings.Setting.bag_hotswapping)
			if Game.hotswapBehaviorModified:
				hotswapBagWithDraggedItems = not hotswapBagWithDraggedItems
			
			if (Game.inventoryEditMode == Game.InventoryEditMode.Default and 
				(pickupType == PickupType.Grabbed or hotswapBagWithDraggedItems)):
				if draggingParent == null:
					draggedInsideItems = me.getItemsInside()
					for item in draggedInsideItems:
						if item.draggingParent:
							
							item.draggingParent.finishMoveback()
							
							
						item.onDraggedWithParentStart(self)
						
						inventory.removeItem(item)
						Util.reparent(item, insideRotationNode)
				
				
	
	Game.itemPickedUp(self)
	dragged = true
	clearTooltip()
	Sound.playSound(grabSound, - 12)
	playPickupSound()
	Sound.itemMovePlayer.play()
	Sound.itemMovePlayer.pitch_scale = 1.3 - 0.1 * getNumCells()
	
	for shadow in shadows:
		shadow.z_index = - 1
	Util.killTween(shadowTween)
	shadowTween = create_tween().set_parallel(true)
	shadowTween.tween_property(self, "shadowOffset", shadowOffset_dragged, 0.1)
	if not isBag():
		shadowTween.tween_property(sprite, getScaleProp(), spriteScale * 1.1, 0.1)

	z_index = 20
	
	if not isMovingBack():
		pickupPosition = global_position
		pickupRotation = fmod(global_rotation + 2 * PI, 2 * PI)
	else:
		killMovebackTween()
	
	previewFusions()
	
	InputBlocker.disableAllControls(InputBlocker.Source.ItemDragging, Game.mainNode)
	
	emit_signal("picked_up")

func onDraggedWithParentStart(parentItem):
	draggingParent = parentItem
	finishMoveback()

func finishMoveback():
	if isMovingBack():
		movebackTween.custom_step(10)
		call_deferred("resetZ")
	
	Util.finishTween(rotationTween)


func onDraggedWithParentEnd():
	draggingParent = null

func canSnap() -> bool:
	return draggedInsideItems.empty() and draggingParent == null

func reactToDropResult(result):
	if result == DropResult.Failed:
		dragged = true
		return
	
	dragged = false
	dropFrame = Util.frameCounter
	Util.killTween(shadowTween)
	shadowTween = create_tween().set_parallel(true)
	shadowTween.tween_property(self, "shadowOffset", getShadowOffset(), 0.1)
	shadowTween.tween_property(sprite, getScaleProp(), spriteScale, 0.1)
	for shadow in shadows:
		shadowTween.tween_property(shadow, "scale", spriteScale, 0.1)
	
	Game.itemDropped(self, result)
	
	loseFocus()
	Game.recalcHoverPriority()
	
	
	
	playDropSound()
	Sound.itemMovePlayer.stop()
	
	sprite.rotation = 0
	bonusRotation = 0
	rotationMomentum = 0
	
	createParticles(dropParticlesScene, Vector2(0.6, 0.6))
	dragParticles.deactivate()
	
	if result != DropResult.Hotswap:
		InputBlocker.restoreAllControls(InputBlocker.Source.ItemDragging)
		
	emit_signal("dropped", result)


func drop() -> int:
	var previousOwnerType = ownerType
	var result = 0
	dragged = false
	resetSprite()
	
	if Game.STORAGEBOX.isHovered():
		lastCollisionPos = global_position
		addToStorageBox()
		result = DropResult.AddedToStorageBox
		if not draggedInsideItems.empty():
			Game.STORAGEBOX.pushItemsToStorage(draggedInsideItems)
			clearDraggedInsideItems()
		
	elif Game.SELLBOX.isHovered():
		sold = true
		result = DropResult.Sold
		onSold()
		animation.play("Sell")
		ItemBook.onOwnableItemRemoved(self)
		prepareDiscard()

		clickArea.hide()


		pushGemsToStorage()
		Game.SELLBOX.sellItem(self)
		Game.itemHoverEnd(self)
		if not draggedInsideItems.empty():
			Game.STORAGEBOX.pushItemsToStorage(draggedInsideItems)
			clearDraggedInsideItems()
	else:
		
		
		
		finishInsideItemsRotation()
		
		result = Game.PLAYER.INVENTORY.tryAddItem(self)
		if wasAddedToInventory(result):
			dropIntoInventory(result == DropResult.Hotswap)
		else:
			
			
			if (ownerType == Owner.PlayerInventory and 
				isBag() and 
				not inventory.allCellsPotentialSpace(occupiedCells)):
				
				pushDraggedItemsToStorage()
				pushToStorage()
				return DropResult.AddedToStorageBox
			
			
			var dif = (pickupPosition - global_position)
			var movebackDur = clamp(dif.length() / 1000, 0.1, 0.5)
			
			
			killMovebackTween()
			
			var curPosition = global_position
			var insidePositions = []
			for item in draggedInsideItems:
				insidePositions.push_back(item.global_position)
			
			if Game.state == Game.State.Shop and ownerType == Owner.PlayerInventory:
				
				if not draggedInsideItems.empty():
					
					
					for itemI in draggedInsideItems.size():
						var item = draggedInsideItems[itemI]
						Util.reparent(item, Game.playerNode)
						var insideRes = inventory.tryAddItem(item, false)



							
						if not wasAddedToInventory(insideRes):
							item.global_position = insidePositions[itemI]
							item.pushToStorage()
						
					correctInsideItemFacedirection()
					clearDraggedInsideItems()
					




					pickup(PickupType.Hotswap)
					
					return DropResult.Failed
				else:
					pushToStorage()
					return DropResult.AddedToStorageBox
			
			ownerType = previousOwnerType
			
			if ownerType == Owner.Socket:
				returnToSocket(movebackDur)
			else:
				clickArea.hide()
				movebackTween = create_tween()


				global_position = pickupPosition
				rotateTo(pickupRotation, movebackDur)
			
				if ownerType == Owner.PlayerInventory:
					result = inventory.tryAddItem(self)
					
					if not wasAddedToInventory(result):
						global_position = curPosition
						
	
	
	
							
						pushToStorage()
						return DropResult.AddedToStorageBox
					
					if not draggedInsideItems.empty():
						for itemI in draggedInsideItems.size():
							var item = draggedInsideItems[itemI]
							var insideRes = inventory.tryAddItem(item)
							if not wasAddedToInventory(insideRes):
								item.global_position = insidePositions[itemI]
								item.pushToStorage()
								
				
				global_position = curPosition
				movebackTween.tween_property(self, "global_position", pickupPosition, 
					movebackDur).set_ease(Tween.EASE_IN)
				
				if ownerType == Owner.PlayerStorageBox:
					Game.STORAGEBOX.addItem(self)
					Util.reparent(self, Game.STORAGEBOX)
					
					movebackTween.tween_callback(self, "moveToFreeSpaceInStorage", [])
					movebackTween.tween_callback(self, "apply_impulse", [
						Vector2(0, - 3), dif * 1.0, 
					])
				
				if ownerType == Owner.Shop:
					Util.reparent(self, Game.shopItemYSort)
				
				
				set_deferred("z_index", 32)
				movebackTween.tween_callback(self, "resetZ")
				movebackTween.tween_callback(self, "showClickArea")
	
	sameOrientationAsPickup = true
	if previousOwnerType != ownerType:
		sameOrientationAsPickup = false
	elif ownerType == Owner.PlayerInventory:
		if getFaceDirection() != pickupFaceDirection:
			sameOrientationAsPickup = false
		if getTopLeftCell() != pickupTopLeftCell:
			sameOrientationAsPickup = false
	
	
	return result

func showClickArea():
	clickArea.show()

func cancelDrag():
	var movebackDur = 0.2
	
	
	
	match ownerType:
		Owner.PlayerInventory:
			var insideStartPositions = {}
			for item in draggedInsideItems:
				insideStartPositions[item] = item.global_position
			
			finishInsideItemsRotation()
			var curTransform: Transform2D = get_global_transform()
			inventory.orientItem(self, pickupTopLeftCell, pickupFaceDirection)
			if inventory.canAddItemOrBag(self):
				inventory.addItemByTopLeft(self, pickupTopLeftCell)
				
				dropIntoInventory(false)
				
				set_global_transform(curTransform)
				moveTo(global_position, pickupPosition, movebackDur)
				rotateTo(pickupRotation, movebackDur)
				
				for item in insideStartPositions:
					item.moveTo(insideStartPositions[item], item.global_position, movebackDur)
				
				reactToDropResult(DropResult.AddedToInventory)
			else:
				
				set_global_transform(curTransform)
				pushDraggedItemsToStorage()
				addToStorageBox(false, false, true)
				reactToDropResult(DropResult.AddedToStorageBox)
			
		Owner.PlayerStorageBox:
			addToStorageBox(false, false, true)
			reactToDropResult(DropResult.AddedToStorageBox)
		
		Owner.Shop:
			moveTo(global_position, pickupPosition, movebackDur)
			rotateTo(pickupRotation, movebackDur)
			Util.reparent(self, Game.shopItemYSort)
			reactToDropResult(DropResult.OutsideInventory)
		
		Owner.Socket:
			if self.movebackSocket != null:
				if self.movebackSocket.isEmpty():
					returnToSocket(movebackDur)
					reactToDropResult(DropResult.Socketed)
				else:
					addToStorageBox(false, false, true)
					reactToDropResult(DropResult.AddedToStorageBox)
		
func hasSameOrientationAsPickup() -> bool:
	return sameOrientationAsPickup

func emptyTweenCallback():
	pass

func killMovebackTween():
	sprite.position = Vector2.ZERO
	Util.killTween(movebackTween)
	movebackTween = null
	showClickArea()

func moveTo(fromPos, newPos, duration = 0.2, transitionType = Tween.TRANS_QUAD):
	killMovebackTween()
	global_position = newPos
	sprite.global_position = fromPos
	movebackTween = create_tween()
	movebackTween.tween_method(self, "setSpriteGlobalPos", fromPos, newPos, 
		duration).set_ease(Tween.EASE_OUT).set_trans(transitionType)





func setSpriteGlobalPos(pos):
	sprite.global_position = pos
	updateShadow()

func dropIntoInventory(hotswap):
	resetZ()
	var hotswapped = hotswap
	
	for item in draggedInsideItems:
		if inventory.canAddItemOrBag(item):
			
			Util.reparent(item, Game.playerNode)
			correctInsideItemFacedirection()
			var res = inventory.tryAddItem(item)
			
		else:
			
			if not hotswapped:
				Util.reparent(item, Game.playerNode)
				
				item.pickup(PickupType.Hotswap)
				hotswapped = true
			else:
				item.pushToStorage()
	clearDraggedInsideItems()
	
	if hotswapped:
		resetBright()
	
	
	for color in Affected.values():
		var affectedPoints = inventory.getAffectedPoints(self, color)
		for point in affectedPoints:
			var star = ObjectPool.instance(affectedAnis[color])
			Game.playerNode.add_child(star)
			star.global_position = point
		if affectedPoints.size() > 0:

			Sound.playSound(affectedSounds[color], affectedSoundsVolume[color], 0.9 + 0.05 * affectedPoints.size())

func finishInsideItemsRotation():
	if not draggedInsideItems.empty():
		Util.finishTween(rotationTween)

func pushDraggedItemsToStorage():
	for item in draggedInsideItems:
		Util.reparent(item, Game.playerNode)
		item.pushToStorage()
	correctInsideItemFacedirection()
	clearDraggedInsideItems()


func pushItemsInsideToStorage():
	pass

func reparentItemsInside():
	for item in draggedInsideItems:
		Util.reparent(item, Game.playerNode)
	correctInsideItemFacedirection()
	clearDraggedInsideItems()

func correctInsideItemFacedirection():
	for item in draggedInsideItems:
		item.faceDirection = item.getGlobalFaceDirection()
		
		item.updateShaderRotation()


func clearDraggedInsideItems():
	for item in draggedInsideItems:
		item.onDraggedWithParentEnd()
	draggedInsideItems.clear()

func initSockets():
	for socket in sockets:
		socket.item = self

func hasSockets() -> bool:
	return not sockets.empty()

func getNumSockets() -> int:
	return sockets.size()

func showSockets():
	for s in sockets:
		s.showSocket()

func hideSockets():
	for s in sockets:
		s.hideSocket()

func hasGems() -> bool:
	for socket in sockets:
		if socket.getGem():
			return true
	return false

func pushGemsToStorage():
	for socket in sockets:
		var gem = socket.getGem()
		if gem != null:
			if not gem.fusing:
				gem.pushToStorage(Game.STORAGEBOX.center)



func returnToSocket(movebackDur):
	pass


func getGems() -> Array:
	var gems = []
	for socket in sockets:
		gems.push_back(socket.getGem())
	return gems

func getGemsNoNull() -> Array:
	return Util.filterNull(getGems())

func getGemData():
	var gemData = []
	for gem in getGems():
		if gem != null:
			gemData.push_back([
				ItemBook.getGemIndex(gem), 
				gem.getFaceDirection(), 
				gem.isLocked()
				])
		else:
			gemData.push_back(null)
	return gemData

func setGem(socketId: int, gem):
	if socketId >= sockets.size():
		print("ohnonononononno")
	else:
		gem.ownerType = Owner.Socket
		sockets[socketId].add_child(gem)
		gem.addToSocket(sockets[socketId])
		gem.global_position = sockets[socketId].global_position
		gem.rotation = rotation

func setGemData(gemData):
	for i in gemData.size():
		var data = gemData[i]
		if data != null:
			var index = data[0]
			var gem = ItemBook.instanciateGemFromIndex(index)
			setGem(i, gem)
			var faceDir = data[1]
			gem.setFaceDirectionInstant(faceDir)
			if data.size() >= 3:
				gem.setLocked(data[2], false)

func getTouchedBags():
	if isBag() or not placed:
		return []
	else:
		return inventory.getBagsInCells(occupiedCells)


func getTouchedBagsCounted():
	if isBag() or not placed:
		return null
	else:
		var touchedBags = inventory.getBagsInCells(occupiedCells)
		var bagCounter = Dictionary()
		for bag in touchedBags:
			var found = false
			
			
			for countedBag in bagCounter:
				if countedBag.descriptor == bag.descriptor:
					bagCounter[countedBag] += bag.getBagMultiplicity(self)
					found = true
			
			if not found:
				bagCounter[bag] = bag.getBagMultiplicity(self)
		
		return bagCounter

const defaultSounds = [
	preload("res://Assets/Sound/Thud1.wav")]
const woodSounds = [
	preload("res://Assets/Sound/Wood1.wav"), 
	preload("res://Assets/Sound/Wood2.wav")]
const metalSounds = [
	preload("res://Assets/Sound/Metal1.wav"), 
	preload("res://Assets/Sound/Metal2.wav")]
const leatherSounds = [
	preload("res://Assets/Sound/Cloth1.wav"), 
	preload("res://Assets/Sound/Cloth2.wav")]
const glassSounds = [
	preload("res://Assets/Sound/Glass1.wav"), 
	preload("res://Assets/Sound/Glass2.wav")]
const stoneSounds = [
	preload("res://Assets/Sound/Stone1.wav"), 
	preload("res://Assets/Sound/Stone2.wav")]
const squishySounds = [
	preload("res://Assets/Sound/Squishy1.wav"), 
	preload("res://Assets/Sound/Bite1.wav")]
const jewelrySounds = [
	preload("res://Assets/Sound/Thud6.wav"), 
	preload("res://Assets/Sound/Jewelry2.wav")]
const sandSounds = [
	preload("res://Assets/Sound/Sand2.ogg"), 
	preload("res://Assets/Sound/Sand3.ogg")]
const paperSounds = [
	preload("res://Assets/Sound/TurningPage3.wav"), 
	preload("res://Assets/Sound/ClosingBook1.wav")]
const slimeSounds = [
	preload("res://Assets/Sound/Slime3.mp3"), 
	preload("res://Assets/Sound/Slime2.wav")]
const birdSounds = [
	preload("res://Assets/Sound/Jynx1.ogg"), 
	preload("res://Assets/Sound/Jynx2.ogg")]
const fireSounds = [
	preload("res://Assets/Sound/Fire1.wav"), 
	preload("res://Assets/Sound/Fire2.wav")]
const iceSounds = [
	preload("res://Assets/Sound/Ice2.wav"), 
	preload("res://Assets/Sound/Ice1.wav")]
const dragonSounds = [
	preload("res://Assets/Sound/Dragon1.wav"), 
	preload("res://Assets/Sound/Dragon2.wav")]
const leafSounds = [
	preload("res://Assets/Sound/Leaf1.wav"), 
	preload("res://Assets/Sound/Leaf2.wav")]

func playPickupSound():
	var pitch = Util.rng.randf_range(0.9, 1.1)
	match descriptor.material:
		Mat.Default:
			Sound.playSound_process(defaultSounds[0], 0, pitch)
		Mat.Wood:
			Sound.playSound_process(woodSounds[0], - 5, pitch)
		Mat.Metal:
			Sound.playSound_process(metalSounds[0], 3, pitch)
		Mat.Leather:
			Sound.playSound_process(leatherSounds[0], 0, pitch)
		Mat.Stone:
			Sound.playSound_process(stoneSounds[0], - 5, pitch)
		Mat.Glass:
			Sound.playSound_process(glassSounds[0], 0, pitch)
		Mat.Squishy:
			Sound.playSound_process(squishySounds[0], 6, pitch)
		Mat.Jewelry:
			Sound.playSound_process(jewelrySounds[1], - 5, pitch)
		Mat.Sand:
			Sound.playSound_process(sandSounds[0], 3, pitch)
		Mat.Paper:
			Sound.playSound_process(paperSounds[0], - 1, pitch)
		Mat.Slime:
			Sound.playSound_process(slimeSounds[0], 0, pitch + 0.2)
		Mat.Fire:
			Sound.playSound_process(fireSounds[0], 0, pitch)
		Mat.Ice:
			Sound.playSound_process(iceSounds[0], 3, pitch)
		Mat.Bird:
			Sound.playSound_process(birdSounds[0], 0, pitch)
		Mat.Dragon:
			Sound.playSound_process(dragonSounds[1], - 6, pitch + 0.3)
		Mat.Leaf:
			Sound.playSound_process(leafSounds[0], 0, pitch)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = Util.rng.randf_range(0.9, 1.1)
	
	match descriptor.material:
		Mat.Default:
			Sound.playSound(defaultSounds[0], volume, pitch)
		Mat.Wood:
			Sound.playSound(woodSounds[1], volume - 5, pitch)
		Mat.Metal:
			Sound.playSound(metalSounds[1], volume, pitch)
		Mat.Leather:
			Sound.playSound(leatherSounds[1], volume, pitch)
		Mat.Stone:
			Sound.playSound(stoneSounds[1], volume, pitch)
		Mat.Glass:
			Sound.playSound(glassSounds[1], volume, pitch)
		Mat.Squishy:
			Sound.playSound(squishySounds[1], volume - 4, pitch)
		Mat.Jewelry:
			Sound.playSound(jewelrySounds[0], volume - 3, pitch)
		Mat.Sand:
			Sound.playSound(sandSounds[1], volume, 3 * pitch)
		Mat.Paper:
			Sound.playSound(paperSounds[1], volume + 2, pitch)
		Mat.Slime:
			Sound.playSound(slimeSounds[1], volume, pitch + 0.2)
		Mat.Fire:
			Sound.playSound(fireSounds[1], volume - 3, pitch)
		Mat.Ice:
			Sound.playSound(iceSounds[1], volume, pitch)
		Mat.Bird:
			Sound.playSound(birdSounds[1], volume, pitch)
		Mat.Dragon:
			Sound.playSound(dragonSounds[0], volume - 3, pitch + 0.3)
		Mat.Leaf:
			Sound.playSound(leafSounds[1], volume, pitch)

func canBeSold() -> bool:
	return (ownerType == Owner.PlayerInventory or 
		ownerType == Owner.PlayerStorageBox or 
		ownerType == Owner.Socket)

func isPickingPossible() -> bool:
	return (pickingEnabled and 
			not dragged and 
			not Game.draggedItem and 
			not Util.isTweenRunning(movebackTween) and 
			not draggingParent and 
			not InputBlocker.isActive() and 
			Game.lockedTooltipItem == null and 
			not Game.replacementPending)



func canBePicked() -> bool:
	return focus and isPickingPossible() and Util.frameCounter > dropFrame

func canBeDraggedWithBag() -> bool:
	return (pickingEnabled and 
			not Util.isTweenRunning(movebackTween) and 
			not draggingParent)

func canBeDropped() -> bool:
	return dragged and Util.frameCounter > pickupFrame

func _input(event: InputEvent) -> void :
	if InputBlocker.isActive(): return
	if event is InputEventMouseMotion or event is InputEventJoypadMotion: return
	if event.is_echo(): return
	
	if (event.is_action_pressed("options") and 
		dragged and 
		Game.state == Game.State.Shop):
		cancelDrag()
		Game.cancelSwitch()
		get_tree().set_input_as_handled()
		return
	
	if Util.isActionPressed_event(event, "push_to_storage"):
		if canBeDropped() and isBag():
			Game.hotswapBehaviorModified = true
			var result = drop()
			Game.hotswapBehaviorModified = false
			reactToDropResult(result)
			Game.cancelSwitch()
			get_tree().set_input_as_handled()
			return
			
	var isTouchEvent = event is InputEventScreenTouch
	
	
	if (Util.isAction_event(event, "grab_item") or 
		isTouchEvent):
		
		if event.is_pressed():
			if canBePicked():
				if (Game.state == Game.State.Shop and 
					Util.isActionPressed("push_to_storage")):
						if ownerType == Owner.PlayerInventory:
							
							if Game.inventoryEditMode == Game.InventoryEditMode.Default:
								pushItemsInsideToStorage()
							inventory.removeItem(self)
							pushToStorage(Game.STORAGEBOX.center)
							reactToDropResult(DropResult.AddedToStorageBox)
							
						elif ownerType == Owner.Shop:
							
							Util.reparent(self, Game.playerNode)
							collisionMap.hide()
							pushToStorage(Game.STORAGEBOX.center)
							reactToDropResult(DropResult.AddedToStorageBox)
						elif ownerType == Owner.Socket:
							
							pushToStorage(Game.STORAGEBOX.center)
							reactToDropResult(DropResult.AddedToStorageBox)
						
						Game.cancelSwitch()
						get_tree().set_input_as_handled()
						Game.setTutorialDone(Game.TutorialSteps.SendToStorage)

				else:
					
					if isTouchEvent:
						Game.draggingFinger = event.index
					pickup()
			
			elif hovered and not pickingEnabled and ownerType == Owner.Shop:
				if Util.time >= notEnoughGoldLabelReadyTime:
					Game.shopSceneNode.notEnoughGold(global_position)
					notEnoughGoldLabelReadyTime = Util.time + 1
					get_tree().set_input_as_handled()
			
			elif focus and ownerType == Owner.ItemLibrary:
				if Game.lockedTooltipItem == null:
					Game.itemLibrary.setSpotlightItem(self)
				
			
			elif focus and ownerType == Owner.InfoPanelIcon:
				emit_signal("info_panel_clicked")
			
		elif canBeDropped():
			if not isTouchEvent or Game.draggingFinger == event.index:
				
				var result = drop()
				reactToDropResult(result)
				
			
	elif Util.isActionPressed_event(event, "lock_combining"):
		if canBeLocked():
			if locked:
				unlockCombining()
				Game.cancelSwitch()
			else:
				lockCombining()
				Game.onItemLocked()
				Game.cancelSwitch()
			get_tree().set_input_as_handled()
	
	if (dragged and 
		isTouchEvent and 
		event.pressed and 
		Game.draggingFinger != event.index and 
		Game.draggingFinger != - 1):
			
			
			rotateRight()

func cacheAffectedItemsForCombat():
	for color in Affected.values():
		cachedAffectedItems[color] = currentAffectedItems[color].keys()


func prepare():
	cacheAffectedItemsForCombat()
	
	disablePicking()
	chanceRng.reset()
	damageRangeRng.reset()
	for gem in getGemsNoNull():
		gem.prepare()
	onPrepare()
	

func onPrepare():
	pass

func preCombatStart():
	for gem in getGemsNoNull():
		gem.preCombatStart()
	
	if hasCooldown():
		iterationCooldown = adjustCooldown()
		triggerTime = iterationCooldown
		activateCooldown()
		Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)
	
	onPreCombatStart()

func onPreCombatStart():
	pass

func hasStartofBattle() -> bool:
	return has_method("onCombatStart")

func combatStart():
	updateShaderRotation()
	
	for gem in getGemsNoNull():
		gem.combatStart()
	
	if hasStartofBattle():
		me.onCombatStart()




func postCombatStart():
	for gem in getGemsNoNull():
		gem.postCombatStart()


	onPostCombatStart()

func onPostCombatStart():
	pass


func repeatCombatStart():
	onPreCombatStart()
	me.onCombatStart()
	onPostCombatStart()


func resetSprite():
	Util.finishTween(shadowTween)
	animation.advance(100)
	animation.play("RESET")
	animation.advance(1)
	sprite.position = Vector2.ZERO
	sprite.rotation = 0
	sprite.scale = spriteScale

func combatEnd():
	
	set_physics_process(false)
	disconnectCombat()
	for gem in getGemsNoNull():
		gem.combatEnd()
	onCombatEnd()

func onCombatEnd():
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
	if isGem(): return CraftingPriority.Gem
	
	for bonded in bondedIngredients:
		if bonded.isGem():
			return CraftingPriority.Mixed
	
	return CraftingPriority.NonGem
	
func addToCraftingQueue():
	if readyToFuse():
		Game.craftingPriorities[self] = getCraftingPriority()

func combatToTitle():
	if isOwnedByOpponent():
		disableTooltip()

func readyToFuse() -> bool:
	return curRecipe and curRecipe.getProgress(bondedIngredients) == 1

func startFusing(delay = PRE_FUSE_DUR):
	if readyToFuse():
		willBeConsumed = true
		fusing = true
		Util.callDelayed(self, "fuse", delay)
		disablePicking()
		for bonded in bondedIngredients:
			if curRecipe == null or not curRecipe.isNeighborCatalyst(bonded):
				bonded.call_deferred("disablePicking")
				bonded.willBeConsumed = true

func readyToTransform() -> bool:
	return false

func giveGold(amount: int):
	Game.gainGold(amount)
	var coinParticles = Game.shootGold(global_position, Game.PLAYER.getGoldPos(), getP1())
	coinParticles.z_index = Util.getGlobalZ(Game.UINode)
	activate(null, false)
	Game.saveRunState()

func empowerEnd():
	pass



func affectsEmpty(color) -> bool:
	return false


func canAffect(item) -> bool:
	return false

func canAffect_secondary(item) -> bool:
	return false

func canAffect_tertiary(item) -> bool:
	return false

func canAffect_lightning(item) -> bool:
	return false

func canAffect_color(item, color):
	if color == Affected.Primary:
		return canAffect(item)
	elif color == Affected.Secondary:
		return canAffect_secondary(item)
	elif color == Affected.Tertiary:
		return canAffect_tertiary(item)
	else:
		return canAffect_lightning(item)

func isAffectingDistinct(color = Affected.Primary) -> bool:
	return false













func getNumDistinctAffectedItems(color = Affected.Primary) -> int:
	var distinctAffectedDescriptors = {}
	for item in getAffectedItems(color):
		distinctAffectedDescriptors[item.descriptor] = true
	return distinctAffectedDescriptors.size()

func getMainType() -> int:
	return descriptor.types[0]


func getTypes() -> Array:
	return dynamicTypes.keys() + descriptor.types

func hasType(type: int) -> bool:
	return type in descriptor.types or type in dynamicTypes

func getNumStaticTypes() -> int:
	return descriptor.getTypes().size()

func getTypeMultiplicity(type: int) -> int:
	return 1 if hasType(type) else 0

func addDynamicType(type: int, byItem: Item):
	if not type in descriptor.types:
		Util.dictAppend(dynamicTypes, type, byItem.get_instance_id())
		
		if dynamicTypes[type].size() == 1:
			if placed:
				inventory.onItemTypeChanged(self)
			if type in typeTransformationParticles:
				ObjectPool.particleOneShot(typeTransformationParticles[type], self)
			

func removeDynamicType(type: int, byItem: Item):
	if hasDynamicType(type, byItem):
		Util.dictErase(dynamicTypes, type, byItem.get_instance_id())
		
		if not type in dynamicTypes:
			if placed:
				inventory.onItemTypeChanged(self)

func hasDynamicType(type: int, fromItem: Item):
	if type in dynamicTypes:
		if fromItem.get_instance_id() in dynamicTypes[type]:
			return true
	
	return false

func clearDynamicTypes():
	dynamicTypes.clear()

func getTranslatedTypeName(type) -> String:
	return descriptor.getTranslatedTypeName(type)

func getTypeDescription(type) -> String:
	return Util.tra("TYPE_" + Type.keys()[type] + "_DESCR")

func getRarity() -> int:
	return descriptor.rarity

func getTranslatedRarity() -> String:
	return getRarityName(getRarity())

static func getRarityName(_rarity: int) -> String:
	return Util.tr("RARITY_" + Rarity.keys()[_rarity])

func getBaseMinDamage() -> int:
	return descriptor.minDam

func getBaseMaxDamage() -> int:
	return descriptor.maxDam

func getBaseAverageDamage() -> float:
	return (getBaseMinDamage() + getBaseMaxDamage()) / 2.0

func canBeEmpowered() -> bool:
	return isWeapon() and canDamage()

func canActivate() -> bool:
	return descriptor.canActivate

func canBlock() -> bool:
	return getBlock() > 0

func getTypedDamageFactor(damSource) -> float:
	var typedDmgFactor = 1.0
	for type in damSource.types:
		typedDmgFactor += character().typedDamageFactors[type]
		
		
		
		
	return typedDmgFactor


func getMinDamage(damSource = damageSource) -> int:
	var override = statDisplayOverrides[Stat.MinDamage]
	if override: return override
	
	var minDam = ceil(descriptor.minDam + bonusMinDam)
	if hasCharacter():
		if canBeEmpowered():
			minDam = minDam + character().getBuffDamageMod()
		
		minDam *= getTypedDamageFactor(damSource)
	
	minDam = round(minDam * bonusDamageFactor)
	minDam = max(minDam, 0)
	
	return minDam


func getMaxDamage(damSource = damageSource) -> int:
	var override = statDisplayOverrides[Stat.MaxDamage]
	if override: return override
	
	var maxDam = ceil(descriptor.maxDam + bonusMaxDam)
	if hasCharacter():
		if canBeEmpowered():
			maxDam = maxDam + character().getBuffDamageMod()
		
		maxDam *= getTypedDamageFactor(damSource)
	
	maxDam = round(maxDam * bonusDamageFactor)
	maxDam = max(maxDam, 0)
	
	return maxDam

func getAverageDamage() -> float:
	return (getMinDamage() + getMaxDamage()) / 2.0

func getDamageRange() -> String:
	if getMinDamage() == getMaxDamage():
		return String(getMinDamage())
	else:
		return String(getMinDamage()) + "-" + String(getMaxDamage())

func randDamage() -> int:
	return Util.rng.randi_range(getMinDamage(), getMaxDamage())

func isStatModified(statVal) -> int:
	if statVal == 0:
		return StatModified.No
	elif statVal > 0:
		return StatModified.Positive
	else:
		return StatModified.Negative

func isDamageModified() -> int:
	var bonusDam = getAverageDamage() - getBaseAverageDamage()
	return isStatModified(bonusDam)

func getDPS() -> float:
	return ((getMinDamage() + getMaxDamage()) * 0.5) / getModifiedCooldown()

func isDPSModified() -> int:
	var baseDPS = getBaseAverageDamage() / getCooldown()
	var modifiedDPS = getAverageDamage() / getModifiedCooldown()
	return isStatModified(modifiedDPS - baseDPS)
	

func getSpeed() -> float:
	var override = statDisplayOverrides[Stat.Speed]
	if override: return override
	
	if hasCharacter():
		var speed_ = speed() + getStackSpeedMods()
		var modifiedSpeed: float
		if speed_ >= 0:
			modifiedSpeed = 1.0 + speed_
		else:
			modifiedSpeed = 1.0 / (1.0 - speed_)
		
		modifiedSpeed = clamp(modifiedSpeed, 0.1, 10.0)
		return modifiedSpeed
	else:
		return 1.0

func getStackSpeedMods():
	return (character().getHeat() - character().getCold()) * 0.02

func hasCooldown() -> bool:
	return descriptor.cd != 0

func isCooldownActive() -> bool:
	return is_physics_processing()

func logCooldown() -> bool:
	return hasCooldown()

func getBaseCooldown() -> float:
	return baseCooldownOverride

func getBaseCooldownIndex(index: int) -> float:
	if index == 0:
		return descriptor.cd
	else:
		return descriptor.extraCds[index - 1]



func getCooldown() -> float:
	var override = statDisplayOverrides[Stat.BaseCooldown]
	if override: return override
	
	return baseCooldownOverride


func getCooldownIndex(index: int) -> float:
	return getBaseCooldownIndex(index)

func isCooldownModified() -> int:
	var baseCd = getBaseCooldown()
	var curCd = getModifiedCooldown()
	return isStatModified(baseCd - curCd)
	

func getModifiedCooldown() -> float:
	return getCooldown() / getSpeed()

func getModifiedCooldownIndex(index: int):
	return getCooldownIndex(index) / getSpeed()


func adjustCooldown():
	var adjustedCooldown = getCooldown()
	if ownerType == Owner.Opponent and (Game.isBelowLeague(Game.Leagues.Master) or Game.curMode == Game.Mode.Lobbies):
		adjustedCooldown *= Util.rng.randf_range(0.975, 1.05)
	else:
		adjustedCooldown *= Util.rng.randf_range(0.95, 1.05)
	
	return adjustedCooldown

func getBaseAccuracy() -> float:
	return descriptor.accuracy

func getAccuracy() -> float:
	var override = statDisplayOverrides[Stat.Accuracy]
	if override: return override
	
	var acc = getBaseAccuracy()
	acc += bonusAccuracy
	if hasCharacter():
		acc += character().getBuffAccuracyMod()
	return acc

func getCombatDisplayAccuracy() -> String:
	var acc = getAccuracy()
	if acc > 100:
		return ">100"
	elif acc < 0:
		return "<0"
	else:
		return String(acc)

func isAccuracyModified() -> int:
	return isStatModified(getAccuracy() - getBaseAccuracy())

func getDisplayCritChance() -> String:
	var c = getCritChancePercent()
	if c > 100:
		return ">100"


	else:
		return String(stepify(c, 0.1))
	
	
func getBaseChance() -> float:
	return descriptor.chance

func isChance1Modified() -> int:
	return isStatModified(getChance() - getBaseChance())

func getBaseChance2() -> float:
	return descriptor.chance2

func isChance2Modified() -> int:
	return isStatModified(getChance2() - getBaseChance2())

func applyBonusChance(toChance, index) -> float:
	if index == 1:
		return (toChance + bonusChancePercent_additive1) * ((100 + bonusChancePercent_mult) / 100.0)
	else:
		return (toChance + bonusChancePercent_additive2) * ((100 + bonusChancePercent_mult) / 100.0)

func getChance() -> float:
	var override = statDisplayOverrides[Stat.Chance]
	if override: return override
	
	return clamp(applyBonusChance(getBaseChance(), 1), 0, 100)

func getChance2() -> float:
	var override = statDisplayOverrides[Stat.Chance2]
	if override: return override
	
	return clamp(applyBonusChance(getBaseChance2(), 2), 0, 100)

func getShopChance() -> float:
	return descriptor.getShopChance()

func canModifyChance() -> bool:
	return getBaseChance() > 0

func getP(index) -> float:
	return descriptor.getP(index)

func getP_check(index) -> float:
	assert (descriptor.params[index] != 0)
	return descriptor.params[index]

func getP1() -> float:
	return getP_check(0)

func getP2() -> float:
	return getP_check(1)

func getP3() -> float:
	return getP_check(2)

func getP4() -> float:
	return getP_check(3)

func getP5() -> float:
	return getP_check(4)

func getP6() -> float:
	return getP_check(5)

func getP7() -> float:
	return getP_check(6)

func getP8() -> float:
	return getP_check(7)

func getP9() -> float:
	return getP_check(8)

func getP10() -> float:
	return getP_check(9)

func getP_m(paramName: String) -> float:
	var baseVal = getP(paramName)
	return getParamModified(paramName, baseVal)

func getParamModified(paramName: String, baseVal) -> float:
	var baseParam = descriptor.paramBases[paramName]
	return (baseVal + paramAdd.get(baseParam, 0)) * paramMult.get(baseParam, 1.0)
	



func modifyParam(paramName: String, amount: float):
	Util.dictAdd(paramMult, paramName, amount, 1.0)

func modifyParam_add(paramName: String, amount: float):
	Util.dictAdd(paramAdd, paramName, amount)

func hasCharacter() -> bool:
	return placed and character() != null

func character():
	if placed:
		return inventory.character
	else:
		return Game.PLAYER

func opponent():
	return character().opponent

func hasOpponent() -> bool:
	return hasCharacter() and opponent() != null

func getPrice():
	return descriptor.getPrice()

func getBaseSellPrice():
	return descriptor.getSellPrice()

func getSellPrice():
	return descriptor.getSellPrice()

func getSalePrice():
	return descriptor.getSalePrice()

func getSalesMultiplier():
	return 1.0

func getBlock() -> int:
	return descriptor.block

func getBaseStaminaCost() -> float:
	return descriptor.staminaCost

func getStaminaCost() -> float:
	var override = statDisplayOverrides[Stat.StaminaCost]
	if override: return override
	
	return getBaseStaminaCost() * staminaFactor

func isStaminaModified() -> int:
	return isStatModified(getBaseStaminaCost() - getStaminaCost())

func getBaseStaminaPerSecond() -> float:
	return getBaseStaminaCost() / getCooldown()

func getStaminaPerSecond() -> float:
	return getStaminaCost() / getModifiedCooldown()

func isStaminaPerSecondModified() -> int:
	var baseSPS = getBaseStaminaPerSecond()
	var modifiedSPS = getStaminaPerSecond()
	return isStatModified(baseSPS - modifiedSPS)

func getCritChancePercent() -> float:
	var override = statDisplayOverrides[Stat.CritChance]
	if override != null: return override
	
	return clamp(critChancePercent, 0, 100)

func addCritChancePercent(amount):
	critChancePercent += amount
	Game.combatLog.snapshotItemTooltipStat(self, Stat.CritChance)

func reduceCritChancePercent(amount):
	critChancePercent -= amount
	Game.combatLog.snapshotItemTooltipStat(self, Stat.CritChance)


func changeCritChancePercent(amount):
	critChancePercent += amount
	Game.combatLog.snapshotItemTooltipStat(self, Stat.CritChance)

func getCritTokens() -> int:
	return critTokens

func addCritTokens(amount):
	critTokens += amount

func useCritToken():
	critTokens -= 1

func addCritSeverity(amount):
	critSeverity += amount

func getCritSeverity() -> float:
	return critSeverity


func addBonusChance(amount):
	bonusChancePercent_mult += amount
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Chance)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Chance2)

func addBonusChance_additive(amount1, amount2 = null):
	bonusChancePercent_additive1 += amount1
	
	if amount2 == null:
		bonusChancePercent_additive2 += amount1
	else:
		bonusChancePercent_additive2 += amount2
	
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Chance)
	
	if amount2 != 0:
		Game.combatLog.snapshotItemTooltipStat(self, Stat.Chance2)

func addAccuracy(amount):
	bonusAccuracy += amount
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Accuracy)

func addBonusDamage(damage, removable: bool = true):
	if damage != 0:
		bonusMinDam += damage
		bonusMaxDam += damage
		if removable:
			Util.eassert(damage > 0)
			removableDam += damage
		Game.combatLog.snapshotItemTooltipStat(self, Stat.MinDamage)
		Game.combatLog.snapshotItemTooltipStat(self, Stat.MaxDamage)
		
		if removable:
			spawnLabel(Game.EventType.DamageBuff, damage)

func changeVaryingDamage(damage):
	addBonusDamage(damage, false)

func addMinDamage(damage):
	bonusMinDam += damage
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MinDamage)

func addMaxDamage(damage):
	bonusMaxDam += damage
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MaxDamage)

func reduceBonusDamage(damage, showLabel: bool = true, removable: bool = true):
	bonusMinDam -= damage
	bonusMaxDam -= damage
	if removable:
		removableDam -= damage
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MinDamage)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MaxDamage)
	
	if showLabel:
		spawnLabel(Game.EventType.DamageBuff, - damage)

func purgeDamage(damage):
	var purgable = min(damage, removableDam)
	if purgable > 0:
		removableDam -= purgable
		bonusMinDam -= purgable
		bonusMaxDam -= purgable
		Game.combatLog.snapshotItemTooltipStat(self, Stat.MinDamage)
		Game.combatLog.snapshotItemTooltipStat(self, Stat.MaxDamage)
		
		spawnLabel(Game.EventType.DamageBuff, - purgable)

func reduceMinDamage(damage):
	bonusMinDam -= damage
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MinDamage)

func reduceMaxDamage(damage):
	bonusMaxDam -= damage
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MaxDamage)

func addBonusDamageFactor(factor):
	bonusDamageFactor += factor
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MinDamage)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MaxDamage)

func reduceBonusDamageFactor(factor):
	bonusDamageFactor -= factor
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MinDamage)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.MaxDamage)
	

func changeStaminaFactor(amount):
	staminaFactor += amount / 100.0
	staminaFactor = max(0, staminaFactor)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.StaminaCost)

func giveDoubleActivationChance(_chance):
	doubleActivationChance += _chance / 100.0

func giveDoubleAttackEffectChance(_chance):
	doubleAttackEffectChance += _chance / 100.0

func rollDoubleAttackEffect() -> int:
	return int(Util.flip(doubleAttackEffectChance))


func dealDamage(triggerEvent = null):
	damageSource.updateItem(self)
	var damageRes = character().dealDamage(damageSource, triggerEvent)
	EventBus.emitSignal(self, "attacked", [damageRes])
	return damageRes

func dealEffectDamage(damage, triggerEvent = null, _damageSource = damageSource):
	_damageSource.updateEffect(self, damage)
	var damageRes = opponent().takeDamage(_damageSource, triggerEvent)
	return damageRes

func hasAttackEffect() -> bool:
	return (hasPreDealDamageEarlyEffect or 
			hasPreDealDamageLateEffect or 
			hasDealtDamageEffect)


func preDealDamage_early(damageRes):
	EventBus.emitSignal(self, "pre_deal_damage_early", [damageRes])
	
	








func preDealDamage_late(damageRes):
	EventBus.emitSignal(self, "pre_deal_damage_late", [damageRes])
	




func dealtDamage(damageRes):
	if damageRes.hasHit():
		countDamage(damageRes.damage)
	else:
		addMetric(Game.ItemMetrics.Misses)




func countDamage(damage):
	addMetric(Game.ItemMetrics.Damage, damage)



func inflictFatigueDamage(fatigueIncrease = 1):
	opponent().addFatigueDamage(fatigueIncrease)
	opponent().takeFatigueDamage(self)

func addMetric(metricsIndex, amount = 1, playerId = null, withNextEvent = false):
	itemMetrics[metricsIndex] += amount
	Game.combatLog.snapshotItemMetric(self, metricsIndex, playerId, withNextEvent)

func getMetric(metricsIndex: int):
	return itemMetrics[metricsIndex]

func giveStamina(amount = 1, triggerEvent = null):
	character().gainStamina(amount, self, triggerEvent)

func fillUpStamina():
	character().fillUpStamina()

const outOfStaminaLabelScene = preload("res://Interface/OutOfStaminaLabel.tscn")
const outOfStaminaSound = preload("res://Assets/Sound/Fanfare_sadtoot.ogg")

func playOutOfStaminaAnimation():
	animation.play("NoStamina")
	var label = ObjectPool.instance(outOfStaminaLabelScene)
	Game.UINode.add_child(label)
	label.global_position = global_position
	if ownerType == Owner.PlayerInventory:
		Game.numTimesOutOfStamina += 1
		Sound.playSound(outOfStaminaSound, - 3, 1.0)
	else:
		Sound.playSound(outOfStaminaSound, - 4, 1.4)

func useStamina(amount = getStaminaCost()):
	var res = character().useStamina(amount)
	if res == character().StaminaResult.Insufficient:
		addMetric(Game.ItemMetrics.OutOfStamina, 1, null, true)
		var event = Game.combatLog.createEvent_OutOfStamina(self, character().playerId)
		EventBus.logEvent(event)
		Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)
		playOutOfStaminaAnimation()
	else:
		EventBus.emitSignal(self, "used_stamina", [amount])
		staminaChanged(amount, StackChangeType.Used_Player, true)
	return res
	
func drainStamina(amount, triggerEvent = null):
	return opponent().drainStamina(amount, self, triggerEvent)

func giveMaxStamina(amount):
	character().giveMaxStamina(amount)

func giveMaxStaminaTemporary(amount, triggerEvent = null, filled: bool = true):
	character().gainMaxStaminaTemporary(amount, self, triggerEvent, filled)

func giveMaxHealth(amount = getP_m("maxhealth"), triggerEvent = null):
	amount = character().applyTemporaryMaxHealthGain(amount)
	if amount > 0:
		addMetric(Game.ItemMetrics.MaxHealth, amount, null, true)
		character().changeMaxHealthTemporary(amount, self, triggerEvent)
		spawnLabel(Game.EventType.TemporaryMaxHealth, amount)

func getAffectedGoldValue() -> int:
	var gold = 0
	for item in getAffectedItems_nocache():
		gold += item.getPrice()
	return gold

func prepareReplacement():
	Game.replacementPending = true
	prepareDiscard()


func finishReplacement():
	Game.replacementPending = false


func prepareDiscard():
	if hovered:
		hoverEnd()
	clearTooltip()
	disableTooltip()
	disablePicking()
	disableFocus()
	Game.onItemUnderMouseExited(self)

func discard(discardGems = true):
	if discardGems:
		for gem in getGemsNoNull():
			gem.discard()
	
	if hovered:
		hoverEnd()
	clearTooltip()
	disableTooltip()
	disablePicking()
	disableFocus()
	Game.onItemUnderMouseExited(self)
	Util.disconnectAll(self)
	
	if isOwnable():
		ItemBook.onOwnableItemRemoved(self)
	
	if pooled:
		clearDynamicTypes()
		Util.killTween(shadowTween)
		resetSprite()
		
		if placed:
			cleanCachedAffectedItems()
			placed = false
		
		ObjectPool.returnInstance(self, descriptor.scene)
	else:
		
		clickArea.hide()
		queue_free()
		

func popIn(withParticles: bool = true, speed = 1.0, jump = false):
	shadowTween = Util.refreshTween(shadowTween)
	setSpriteScale(Vector2.ZERO)
	updateShadow()
	
	var scaledUp = spriteScale * 1.1
	var totalScaleDur = 0.5 / speed
	var scaleDur1 = 0.3 / speed
	
	shadowTween.set_process_mode(Tween.TWEEN_PROCESS_PHYSICS)
	shadowTween.set_parallel()
	
	shadowTween.tween_property(sprite, getScaleProp(), scaledUp, 
		scaleDur1).set_ease(Tween.EASE_IN_OUT)
	shadowTween.tween_property(sprite, getScaleProp(), spriteScale, 
		totalScaleDur - scaleDur1).from(scaledUp).set_ease(
			Tween.EASE_IN_OUT).set_delay(scaleDur1)
	
	if jump:
		var yPos = sprite.position.y
		var yOffset = Util.rng.randf_range( - 90.0, - 40.0)
		var totalJumpDur = 0.3 / speed

		var jumpDur1 = 0.15 / speed
		shadowTween.tween_property(sprite, "position:y", yOffset, 
			jumpDur1).set_ease(Tween.EASE_OUT)
		shadowTween.tween_property(sprite, "position:y", yPos, 
			totalJumpDur - jumpDur1).set_ease(Tween.EASE_IN).from(yOffset).set_delay(jumpDur1)

	
	
	
	if withParticles:
		var particles = createParticles(sparksScene, Vector2(0.9, 0.9))
		particles.modulate = Game.rarityColors[getRarity()]

func disappear():
	shadowTween = Util.refreshTween(shadowTween)
	shadowTween.tween_property(self, "scale", Vector2.ZERO, 0.3).set_ease(Tween.EASE_IN_OUT)
	shadowTween.tween_callback(self, "discard")


func appearInLibrary():
	show()
	scale = Vector2.ZERO
	animation.stop()
	if isBag():
		animation.play("AppearInLibrarySmall")
	else:
		animation.play("AppearInLibrary")


func createParticles(scene, baseScale = Vector2.ONE):
	var particles = ObjectPool.instance(scene)
	Game.mainNode.add_child(particles)
	particles.global_position = global_position
	particles.z_index = Util.getGlobalZ(self) - 1
	var numCells = getNumOccupiedCells()
	numCells += getNumBagCells()
	particles.scale = baseScale * sqrt(numCells)
	particles.restart()
	ObjectPool.returnAfter(1.0, particles)
	return particles

func deactivateParticles():
	for particles in specificDragParticles:
		if particles is Particles2D and not particles.emitting:
			particles.restart()
			particles.emitting = false

func makeRigidBody():
	mode = RigidBody2D.MODE_RIGID
	if ownerType == Owner.Title:
		set_collision_layer_bit(2, true)
		set_collision_mask_bit(2, true)
	else:
		set_collision_layer_bit(0, true)
		set_collision_mask_bit(0, true)

func dropImpulse(direction = null, tweenBouncyness: bool = true):
	
	if tweenBouncyness:
		var bouncynessTween = create_tween().set_parallel()
		bouncynessTween.tween_property(physics_material_override, 
			"bounce", 0.0, frictionTime).from(baseBounce)
		bouncynessTween.tween_property(physics_material_override, 
			"friction", 1.0, frictionTime).from(baseFriction)
	
	var impulseOffset = Vector2(Util.rng.randf_range( - offset, offset), 
								Util.rng.randf_range( - offset, offset))
	if direction == null:
		direction = (Vector2(
					Util.rng.randf_range( - impulse, impulse), 
					Util.rng.randf_range( - impulse, impulse))
					+ momentum * momentumFactor)
	
	
	var impulse2: Vector2 = direction * (0.5 + 0.5 * mass)
	
	apply_impulse(impulseOffset, impulse2)

func makeNonRigidBody():
	mode = RigidBody2D.MODE_STATIC
	set_collision_layer_bit(0, false)
	set_collision_mask_bit(0, false)
	sleeping = true


func rollChance(chance = getBaseChance()) -> bool:
	return chanceRng.rollPercent(applyBonusChance(chance, 1))
	
func rollChance2() -> bool:
	return chanceRng.rollPercent(applyBonusChance(descriptor.chance2, 2))

func rollShopChance(shopChance = descriptor.shopChance) -> bool:
	return chanceRng.rollPercent(shopChance)

func checkTriggerCount(limit: int) -> bool:
	if Util.time > triggersThisFrame:
		triggersThisFrame = 1
		lastTriggerTime = Util.time
	else:
		triggersThisFrame += 1
		if triggersThisFrame > limit:
			return false
	return true

func trigger():
	iterationCooldown = adjustCooldown()
	triggerTime += iterationCooldown
	
	doCooldownEffect()
	
	if doubleActivationChance > 0 and Util.flip(doubleActivationChance):
		doCooldownEffect()

func doCooldownEffect():
	pass

func setBaseCooldown(newBaseCd):
	baseCooldownOverride = newBaseCd
	updateBaseCooldown()

func resetBaseCooldown():
	setBaseCooldown(descriptor.cd)


func updateBaseCooldown():
	var cdProgress = triggerTime / iterationCooldown
	iterationCooldown = adjustCooldown()
	triggerTime = cdProgress * iterationCooldown
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.BaseCooldown)

func _physics_process(delta: float):
	if not character().isStunned():
		triggerTime -= delta * getSpeed()
		showCooldown(1.0 - (triggerTime / iterationCooldown))
		if triggerTime <= 0:
			trigger()




func getCooldownEncoded():
	if iterationCooldown == 0:
		return - 1
	var relProgress = 1.0 - triggerTime / iterationCooldown
	var progressPerSecond: float
	if is_physics_processing():
		progressPerSecond = getSpeed() / iterationCooldown
	else:
		progressPerSecond = 0
	var value = int(relProgress * cdEncodingFactor) << 32
	value += int(progressPerSecond * cdEncodingFactor)
	return value

func reconstructCooldown(encodedCd, timeSinceEntry):
	if encodedCd == - 1:
		showCooldown(0)
	else:
		var progressPerSecond: float = (encodedCd % int(pow(2, 32))) / cdEncodingFactor
		var relProgress = (encodedCd >> 32) / cdEncodingFactor
		var curProgress = relProgress + progressPerSecond * timeSinceEntry
		showCooldown(curProgress)


func advanceCooldownPercent(amount):
	if not isCooldownActive(): return
	
	var reduction = amount / 100.0 * iterationCooldown
	triggerTime -= reduction
	
	while triggerTime <= 0:
		trigger()
		if not isCooldownActive(): return
	
	Util.spawnLabelOnItem(Game.EventType.CooldownAdvance, self, reduction)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)

func advanceCooldownSeconds(amount):
	if not isCooldownActive(): return
	
	triggerTime -= amount * getSpeed()
	
	while triggerTime <= 0:
		trigger()
		if not isCooldownActive(): return
	
	Util.spawnLabelOnItem(Game.EventType.CooldownAdvance, self, amount)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)

func miniActivate():
	if animation.current_animation == "":
		if consumed:
			animation.play("MiniActivate_consumed")
		else:
			animation.play("MiniActivate")

func playActivationAnimation_Scale(maxScale: float):
	shadowTween = Util.refreshTween(shadowTween)
	shadowTween.set_process_mode(Tween.TWEEN_PROCESS_PHYSICS)
	shadowTween.tween_property(sprite, "scale", spriteScale * maxScale, 0.2).set_ease(Tween.EASE_IN_OUT)
	shadowTween.tween_property(sprite, "scale", spriteScale, 0.3).set_ease(Tween.EASE_IN_OUT)

func playActivationAnimation_Jump(height, maxScale: float = 1.0):
	shadowTween = Util.refreshTween(shadowTween)
	shadowTween.set_process_mode(Tween.TWEEN_PROCESS_PHYSICS)
	
	var startPos = sprite.global_position.y
	shadowTween.tween_property(sprite, getScaleProp(), spriteScale * maxScale, 0.1).set_ease(Tween.EASE_IN_OUT)
	shadowTween.parallel().tween_property(sprite, "global_position:y", 
		startPos - height, 0.1).set_ease(Tween.EASE_OUT).set_trans(Tween.TRANS_QUAD)
	
	shadowTween.tween_property(sprite, getScaleProp(), spriteScale, 0.2).set_ease(Tween.EASE_IN_OUT)
	shadowTween.parallel().tween_property(sprite, "global_position:y", 
		startPos, 0.2).set_ease(Tween.EASE_IN).set_trans(Tween.TRANS_QUAD).set_delay(0.05)

func playActivationAnimation_JumpSquash(height, intensity = 0.2):
	shadowTween = Util.refreshTween(shadowTween)
	shadowTween.set_process_mode(Tween.TWEEN_PROCESS_PHYSICS)
	var startPos = sprite.global_position.y
	
	var longScale = 1.0 + intensity
	var shortScale = 1.0 / longScale
	var scaling: Vector2
	if faceDirection == FaceDirection.UP or faceDirection == FaceDirection.DOWN:
		scaling = Vector2(shortScale, longScale)
	else:
		scaling = Vector2(longScale, shortScale)
	
	shadowTween.tween_property(sprite, getScaleProp(), spriteScale * scaling, 0.1).set_ease(Tween.EASE_IN_OUT)
	shadowTween.parallel().tween_property(sprite, "global_position:y", 
		startPos - height, 0.1).set_ease(Tween.EASE_OUT).set_trans(Tween.TRANS_QUAD)
	
	shadowTween.tween_property(sprite, getScaleProp(), spriteScale, 0.2).set_ease(Tween.EASE_IN_OUT).set_delay(0.05)
	shadowTween.parallel().tween_property(sprite, "global_position:y", 
		startPos, 0.2).set_ease(Tween.EASE_IN).set_trans(Tween.TRANS_QUAD)

func playActivationAnimation(aniType = descriptor.activationAni, 
	consume: bool = false):
	
	resetSprite()
	
	if aniType == ActivationAni.Jump:
		animation.play("Activate")
		playActivationAnimation_Jump(40)
	
	elif aniType == ActivationAni.SquishyJump:
		animation.play("Activate")
		playActivationAnimation_JumpSquash(40, 0.1)
	
	elif aniType == ActivationAni.VerySquishyJump:
		animation.play("Activate")
		playActivationAnimation_JumpSquash(40, 0.2)
	
	elif aniType == ActivationAni.Slash:
		animation.play("Activate_Slash")
	
	elif aniType == ActivationAni.Stab:
		animation.play("Activate_Stab")
	
	elif aniType == ActivationAni.ReverseStab:
		animation.play("Activate_Reverse_Stab")
	
	elif aniType == ActivationAni.Bonk:
		animation.play("Activate_Bonk")
	
	elif aniType == ActivationAni.ReverseBonk:
		animation.play("Activate_ReverseBonk")
	
	elif aniType == ActivationAni.Sweep:
		animation.play("Activate_Sweep")
	
	elif aniType == ActivationAni.Block:
		animation.play("Activate")
		playActivationAnimation_Jump(30, 1.3)
		shadowTween.set_speed_scale(1.2)
	
	elif aniType == ActivationAni.Chop:
		animation.play("Activate_Chop")
	
	elif aniType == ActivationAni.Wave:
		animation.play("Activate_Wave")
	
	elif aniType == ActivationAni.Throw:
		animation.play("Activate_Throw")
	
	elif aniType == ActivationAni.Scale:
		animation.play("Activate")
		playActivationAnimation_Scale(1.5)
	
	elif aniType == ActivationAni.Squish:
		animation.play("Activate")
		
		if hasSquishySprite:
			sprite.addMomentum(0.1)
		else:
			shadowTween = Util.refreshTween(shadowTween)
			shadowTween.set_process_mode(Tween.TWEEN_PROCESS_PHYSICS)
			shadowTween.tween_property(sprite, "scale", 
				Vector2(spriteScale.x * 1.2, spriteScale.y * 0.8), 
				0.07).set_ease(Tween.EASE_IN_OUT)
			shadowTween.tween_property(sprite, "scale", 
				Vector2(spriteScale.x * 0.8, spriteScale.y * 1.2), 
				0.2).set_ease(Tween.EASE_IN_OUT)
			shadowTween.tween_property(sprite, "scale", 
				Vector2(spriteScale.x * 1.1, spriteScale.y * 0.9), 
				0.13).set_ease(Tween.EASE_IN_OUT)
			shadowTween.tween_property(sprite, "scale", 
				spriteScale, 0.1).set_ease(Tween.EASE_IN_OUT)
	
	elif aniType == ActivationAni.Potion:
		animation.play("Activate_Potion")
	
	elif aniType == ActivationAni.Hiss:
		animation.play("Activate_Snake")
		shadowTween = Util.refreshTween(shadowTween)
		shadowTween.set_process_mode(Tween.TWEEN_PROCESS_PHYSICS)
		shadowTween.tween_property(sprite, "scale", 
			Vector2(spriteScale.x, spriteScale.y * 0.8), 
			0.1).set_ease(Tween.EASE_OUT)
		shadowTween.tween_property(sprite, "scale", 
			Vector2(spriteScale.x, spriteScale.y * 1.2), 
			0.18).set_ease(Tween.EASE_IN).set_delay(0.08)
		shadowTween.tween_property(sprite, "scale", 
			spriteScale, 
			0.14).set_ease(Tween.EASE_IN_OUT)
	
	elif aniType == ActivationAni.Spin:
		animation.play("Activate_Spin")
	
	elif aniType == ActivationAni.Tackle:
		animation.play("Activate_Tackle")
	
	elif aniType == ActivationAni.DoubleSlash:
		animation.play("Activate_DoubleSlash")
	
	elif aniType == ActivationAni.Struggle:
		animation.play("Activate_Struggle")
		playActivationAnimation_Jump(30)
	
	elif aniType == ActivationAni.Shoot:
		animation.play("Activate_Shoot")
		shadowTween = Util.refreshTween(shadowTween)
		shadowTween.set_process_mode(Tween.TWEEN_PROCESS_PHYSICS)
		shadowTween.tween_property(sprite, "scale", 
			Vector2(spriteScale.x * 1.3, spriteScale.y * 0.8), 
			0.2).set_ease(Tween.EASE_IN_OUT)
		shadowTween.tween_property(sprite, "scale", 
			Vector2(spriteScale.x * 0.8, spriteScale.y * 1.0), 
			0.1).set_ease(Tween.EASE_IN_OUT).set_delay(0.1)
		shadowTween.tween_property(sprite, "scale", 
			Vector2(spriteScale.x * 1.1, spriteScale.y * 0.9), 
			0.05).set_ease(Tween.EASE_IN_OUT)
		shadowTween.tween_property(sprite, "scale", 
			spriteScale, 0.1).set_ease(Tween.EASE_IN_OUT)
	
	elif aniType == ActivationAni.Flash:
		animation.play("Activate")
	
	if consume:
		animation.queue("Consume")

func playActivationSound():
	playDropSound( - 6)

func activate(damageRes = null, playCombatAni = true, consume = false, 
	animationOverride = descriptor.activationAni):
	
	if dragged: return
	if Util.isTweenRunning(movebackTween): return
	




	
	if Util.time > lastActivationTime:
		activationsThisFrame = 1
		lastActivationTime = Util.time
	else:
		activationsThisFrame += 1
		if activationsThisFrame > 3: return
	
	
	var event = null
	
	if not Game.fightEnded:
		if not isBag():
			event = Game.combatLog.createEvent_Activation(self)
			EventBus.emitEvent(self, "activated", event, [event])
			addMetric(Game.ItemMetrics.Activations)
		if hasCooldown():
			Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown, null, 
				false, event)
	
	if not isBag():
		z_index = 3
		Util.callDelayed(self, "resetZ", 0.4)
	
	if animationOverride != null:
		playActivationAnimation(animationOverride, consume)
	playActivationSound()
	
	if playCombatAni:
		if damageRes and not damageRes.hasHit():
			playAnimation(false)
		else:
			playAnimation()
		
	
	if damageRes:
		character().playActivateAnimation()
	



	return event


func activateFromEvent(event):
	
	if event.type == Game.EventType.Activation:
		if not isBag():
			z_index = 2
			Util.callDelayed(self, "resetZ", 0.5)
		playActivationAnimation()
		playActivationSound()
	
	elif Game.isStack(event.type):
		var appliedToOpponent = (event.target != character().playerId)
		var amount = event.getAmount()
		var target = opponent() if appliedToOpponent else character()
		if event.getParam("resisted", false):
			Util.spawnResistedLabel(event.type, target.randBuffLabelPos(), amount)
		elif event.getParam("protected", false):
			Util.spawnProtectedLabel(event.type, character().randBuffLabelPos(), amount)
		elif event.getParam("reflected", false):
			target = character() if appliedToOpponent else opponent()
			Util.spawnReflectLabel(event.type, target.randBuffLabelPos(), amount)
		else:
			Util.spawnBuffLabel_item(event.type, self, amount, appliedToOpponent)
	
	elif event.type == Game.EventType.DealDamage:
		character().playAttackAnimation()
		var damage = event.getParam("damage", 0)
		opponent().spawnLabel(event.type, damage, self)
		opponent().damageAnimation.play("Hit")
		playAnimation()
	
	elif event.type == Game.EventType.CriticalDamage:
		character().playAttackAnimation()
		var damage = event.getParam("damage", 0)
		opponent().spawnLabel(event.type, damage, self)
		opponent().damageAnimation.play("Hit")
		playAnimation()
	
	elif event.type == Game.EventType.MissedAttack:
		character().playAttackAnimation()
		opponent().spawnLabel(event.type, 0, self)
		playAnimation(false)
	
	elif event.type == Game.EventType.OutofStamina:
		playOutOfStaminaAnimation()
	
	elif event.type == Game.EventType.Health:
		var healAmount = event.getAmount()
		character().spawnLabel(event.type, healAmount, self, character().randHealNumberPos())
	
	elif event.type == Game.EventType.LoseHealth:
		var lostHealth = - event.getAmount()
		character().spawnLabel(event.type, lostHealth, self)
	
	elif (event.type in [Game.EventType.Stamina, 
		Game.EventType.TemporaryMaxStamina]):
		
		var amount = event.getParam("stamina", 0)
		spawnLabel_other(event.type, amount)
	
	elif event.type == Game.EventType.TemporaryMaxHealth:
		var amount = event.getAmount()
		spawnLabel_other(event.type, amount)


func spawnLabel(type, amount):
	var setting = Settings.getVal(Settings.Setting.damage_numbers)
	if setting == Settings.DMG_NR_ALL or setting == Settings.DMG_NR_ITEMS:
		Util.spawnLabelOnItem(type, self, amount)


func spawnLabel_other(type, amount):
	if Settings.getVal(Settings.Setting.buff_labels):
		Util.spawnLabelOnItem(type, self, amount)


func consume(damageRes = null, playCombatAni = true):
	activate(damageRes, playCombatAni, true)
	consumed = true

func setState(newState, withNextEvent: bool = false, event = null):
	Game.combatLog.snapshotItemState(self, newState, withNextEvent, event)
	onStateChanged(newState)

func onStateChanged(newState):
	pass

func heal(amount: int = getP_m("heal"), triggerEvent = null):
	var healed = character().heal(amount, self, triggerEvent)

func stun(duration, triggerEvent = null):
	opponent().stun(duration, self, triggerEvent)

func speed() -> float:
	return speedScale


func getStat(stat):
	match stat:
		Stat.MaxDamage:
			if getBaseMaxDamage() > 0:
				return getMaxDamage()
			else:
				return 0
		Stat.MinDamage:
			if getBaseMinDamage() > 0:
				return getMinDamage()
			else:
				return 0
		Stat.Accuracy:
			return getAccuracy()
		Stat.CritChance:
			return getCritChancePercent()
		Stat.Speed:
			return getSpeed()
		Stat.Cooldown:
			return getCooldownEncoded()
		Stat.StaminaCost:
			return getStaminaCost()
		Stat.Chance:
			return getChance()
		Stat.Chance2:
			return getChance2()
		Stat.BaseCooldown:
			return getCooldown()




func setStat(stat, value):
	statDisplayOverrides[stat] = value
	queueTooltipUpdate()

func addSpeed(amount):
	speedScale += amount
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Speed)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)

func reduceSpeed(amount):
	speedScale -= amount
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Speed)
	Game.combatLog.snapshotItemTooltipStat(self, Stat.Cooldown)

func giveBuffPower(buffType, power):
	buffPowers[buffType] += power

func changeHealAmp(amount):
	modifyParam("heal", amount)
	modifyParam("lifesteal", amount)

func getAmplificationChancePercent(buffType):
	return buffAmplificationChances[buffType]

func changeAmplificiationChancePercent(buffType, chance):
	buffAmplificationChances[buffType] += chance

func changeAmplificiationChancePercent_allBuffs(chance):
	for buff in Game.getBuffs():
		changeAmplificiationChancePercent(buff, chance)

func changeAmplificiationChancePercent_allDebuffs(chance):
	for buff in Game.getDebuffs():
		changeAmplificiationChancePercent(buff, chance)

func changeNullifyChancePercent(buffType, chance):
	buffAmplificationChances[buffType] -= chance

func giveReflectStacks(amount):
	character().changeDebuffReflectStacks(amount)

func stackChanged(stackType: int, amount: int, onPlayer: bool, used: bool = false):
	var changeType: int
	if amount > 0:
		changeType = StackChangeType.Added_Player
	else:
		if used:
			changeType = StackChangeType.Used_Player
		else:
			changeType = StackChangeType.Removed_Player
	
	if not onPlayer:
		changeType += 1
	
	var index = getStackMetricIndex(changeType, stackType)
	var playerId = 0 if onPlayer else 1
	addMetric(index, abs(amount), playerId, true)
	
	
	


func staminaChanged(amount: float, changeType: int, withNextEvent: bool = false):
	var index = getMultiMetricIndex(changeType, Game.ItemMetrics.Stamina)
	
	addMetric(index, amount, character().playerId, withNextEvent)


func giveBlock(amount = getBlock(), canTriggerEffects = true, triggerEvent = null):
	if amount > 0:
		var event = giveStacks(character(), Game.EventType.Block, amount, triggerEvent)
		if event != null:
			if canTriggerEffects:
				EventBus.emitSignal(self, "gave_block", [event.getAmount(), event])
			else:
				EventBus.logEvent(event)
			return event
	return null

func removeBlock(amount, triggerEvent = null):
	var event = opponent().loseBlock(amount, self, triggerEvent)
	if event:
		countDamage( - event.getAmount())

func loseBlock(amount, triggerEvent = null):
	character().loseBlock(amount, self, triggerEvent)

func useBlock(amount, triggerEvent = null):
	return character().useStacks(Game.EventType.Block, amount, self, triggerEvent)

func giveStacks(target, type: int, amount, triggerEvent = null):
	if amount > 0:
		return target.gainStacks(type, round(amount * buffPowers[type]), self, triggerEvent)
	return null

func giveStacksTemporary(target, type: int, amount, duration, triggerEvent = null):
	if amount > 0:
		return target.gainStacksTemporary(type, round(amount * buffPowers[type]), duration, self, triggerEvent)
	return null
	
func onTemporaryStacksTimeout(buffType):
	pass

func stealStack(type: int, amount, triggerEvent = null):
	var removeEvent = opponent().loseStacks(type, amount, self, triggerEvent)
	var giveEvent = giveStacks(character(), type, amount, removeEvent)
	return giveEvent





func giveSpikes(amount, triggerEvent = null):
	giveStacks(character(), Game.EventType.Spikes, amount, triggerEvent)

func removeSpikes(amount, triggerEvent = null):
	opponent().loseSpikes(amount, self, triggerEvent)

func loseSpikes(amount, triggerEvent = null):
	character().loseSpikes(amount, self, triggerEvent)

func useSpikes(amount, triggerEvent = null):
	return character().useStacks(Game.EventType.Spikes, amount, self, triggerEvent)

func giveVampirism(amount, triggerEvent = null):
	return giveStacks(character(), Game.EventType.Vampirism, amount, triggerEvent)

func removeVampirism(amount, triggerEvent = null):
	opponent().loseVampirism(amount, self, triggerEvent)

func useVampirism(amount, triggerEvent = null):
	return character().useStacks(Game.EventType.Vampirism, amount, self, triggerEvent)

func loseVampirism(amount, triggerEvent = null):
	character().loseVampirism(amount, self, triggerEvent)

func inflictPoison(amount, triggerEvent = null):
	return giveStacks(opponent(), Game.EventType.Poison, amount, triggerEvent)

func selfInflictPoison(amount, triggerEvent = null):
	return giveStacks(character(), Game.EventType.Poison, amount, triggerEvent)

func cleansePoison(amount: int, triggerEvent = null) -> int:
	var curPoison = character().getPoison()
	if curPoison == 0:
		return 0
	
	amount = min(curPoison, amount)
	character().losePoison(amount, self, triggerEvent)
	return amount

func inflictBlind(amount, triggerEvent = null):
	giveStacks(opponent(), Game.EventType.Blind, amount, triggerEvent)

func selfInflictBlind(amount, triggerEvent = null):
	return giveStacks(character(), Game.EventType.Blind, amount, triggerEvent)

func cleanseBlind(amount: int, triggerEvent = null) -> int:
	var curBlind = character().getBlind()
	if curBlind == 0:
		return 0
	
	amount = min(curBlind, amount)
	character().loseBlind(amount, self, triggerEvent)
	return amount

func giveRegeneration(amount, triggerEvent = null):
	return giveStacks(character(), Game.EventType.Regeneration, amount, triggerEvent)

func removeRegeneration(amount, triggerEvent = null):
	return opponent().loseRegeneration(amount, self, triggerEvent)

func useRegeneration(amount, triggerEvent = null):
	return character().useStacks(Game.EventType.Regeneration, amount, self, triggerEvent)

func giveLucky(amount, triggerEvent = null):
	return giveStacks(character(), Game.EventType.Lucky, amount, triggerEvent)

func tryUseLucky(amount, triggerEvent = null):
	if character().getLucky() >= amount:
		useLucky(amount, triggerEvent)
		return true
	else:
		return false

func loseLucky(amount, triggerEvent = null):
	character().loseLucky(amount, self, triggerEvent)

func removeLucky(amount, triggerEvent = null):
	opponent().loseLucky(amount, self, triggerEvent)

func useLucky(amount, triggerEvent = null):
	return character().useStacks(Game.EventType.Lucky, amount, self, triggerEvent)

func giveMana(amount, triggerEvent = null):
	giveStacks(character(), Game.EventType.Mana, amount, triggerEvent)


func giveMana_capped(amount, maximum, triggerEvent = null):
	amount = round(amount * buffPowers[Game.EventType.Mana])
	var curMana = character().getMana()
	if maximum > curMana:
		var missingMana = maximum - curMana
		var manaGiven = min(amount, missingMana)
		character().gainMana(manaGiven, self, triggerEvent)
		return amount - manaGiven
	else:
		return amount

func checkMana(amount) -> bool:
	return character().getMana() >= amount

func useMana(amount, triggerEvent = null):
	return character().useMana(amount, self, triggerEvent)


func tryUseMana(amount, triggerEvent = null):
	var curMana = character().getMana()
	if curMana < amount:
		return null
	else:
		return useMana(amount, triggerEvent)

func removeMana(amount, triggerEvent = null):
	opponent().loseMana(amount, self, triggerEvent)

func inflictCold(amount, triggerEvent = null):
	giveStacks(opponent(), Game.EventType.Cold, amount, triggerEvent)

func cleanseCold(amount: int, triggerEvent = null) -> int:
	var curCold = character().getCold()
	if curCold == 0:
		return 0
	
	amount = min(curCold, amount)
	character().loseCold(amount, self, triggerEvent)
	return amount
	

func giveHeat(amount, triggerEvent = null):
	giveStacks(character(), Game.EventType.Heat, amount, triggerEvent)

func loseHeat(amount, triggerEvent = null):
	character().loseHeat(amount, self, triggerEvent)

func useHeat(amount, triggerEvent = null):
	return character().useStacks(Game.EventType.Heat, amount, self, triggerEvent)

func giveEmpower(amount, triggerEvent = null):
	giveStacks(character(), Game.EventType.Empower, amount, triggerEvent)

func loseEmpower(amount, triggerEvent = null):
	character().loseEmpower(amount, self, triggerEvent)

func healthToBlock(health: float, block, triggerEvent = null):
	var clampedHealth = min(health, character().getCurrentHealth() - 1)
	if clampedHealth > 0:
		character().loseHealth(clampedHealth, self, triggerEvent)
		
		block = ceil((clampedHealth / health) * block)
		giveBlock(block, true, triggerEvent)

func getModifiedEffectDamage(baseDamage):
	var modifiedDamage = baseDamage
	modifiedDamage *= (1.0 + character().typedDamageFactors[Game.stealLifeDamageSource.Type.Effect])
	modifiedDamage *= bonusDamageFactor
	return modifiedDamage

func stealLife(damage, lifestealFactor: float = 1.0, triggerEvent = null):
	Game.stealLifeDamageSource.updateEffect(self, damage)
	var damageRes = opponent().takeDamage(Game.stealLifeDamageSource, triggerEvent)
	heal(damageRes.damage * lifestealFactor, damageRes.event)
	return damageRes

func giveCritTokens(amount):
	character().gainCritTokens(amount)

const chargeSound = preload("res://Assets/Sound/Electricity1.ogg")

func sendCharge(durPerTile: float, cells: Array, speedFactor: float, event):
	var chargeDuration = durPerTile * (cells.size() - 1)
	var charge = ObjectPool.instance(Game.electricalChargeScene)
	Game.playerNode.add_child(charge)
	charge.start(self, cells, chargeDuration / speedFactor)
	charge.logEvent(event)
	Sound.playSound(chargeSound, Util.rng.randf_range( - 12, - 5), Util.randPitch(0.3))

func chargeReceived(charge):
	numCharges += 1
	if hasOnChargeReceivedEffect:
		me.onChargeReceived(charge)

func chargeLeft(charge):
	numCharges -= 1
	if hasOnChargeLeftEffect:
		me.onChargeLeft(charge)

func reactsToCharges() -> bool:
	return hasOnChargeReceivedEffect or hasOnChargeLeftEffect

func changeChargedItemStat(charge, cellIndex, flatVal, valPerTile):
	
	var previousVal = flatVal + (cellIndex - 2) * valPerTile
	var newVal = previousVal + valPerTile
	
	if charge.lastChargedItem != null:
		if charge.curChargedItem == null:
			me.chargedItemStatChange(charge.lastChargedItem, - previousVal)
		elif charge.curChargedItem == charge.lastChargedItem:
			me.chargedItemStatChange(charge.curChargedItem, valPerTile)
		else:
			me.chargedItemStatChange(charge.lastChargedItem, - previousVal)
			me.chargedItemStatChange(charge.curChargedItem, newVal)
	
	elif charge.curChargedItem != null:
		me.chargedItemStatChange(charge.curChargedItem, newVal)


func clearSpriteMaterial():
	sprite.set_material(null)
	
func giveProgressMaterial():
	sprite.set_material(progressMaterial)

func getSizeInCells() -> Vector2:
	var topLeft = Vector2(100, 100)
	var bottomRight = Vector2( - 100, - 100)
	var cells = getCollisionCells()
	if cells.empty():
		return Vector2.ZERO
	
	for cell in cells:
		if cell.x < topLeft.x:
			topLeft.x = cell.x
		if cell.y < topLeft.y:
			topLeft.y = cell.y
		
		if cell.x > bottomRight.x:
			bottomRight.x = cell.x
		if cell.y > bottomRight.y:
			bottomRight.y = cell.y
	
	return bottomRight - topLeft + Vector2(1, 1)

func getTextureSize() -> Vector2:
	return sprite.texture.get_size() * sprite.global_scale

func scaleToFit(maxSize: Vector2, maxScale: float):
	var size = getTextureSize()
	var fill = size / maxSize
	scale /= max(1.0 / maxScale, max(fill.x, fill.y))

func getSpriteOffset() -> Vector2:
	return - sprite.offset * sprite.global_scale * 0.5

func getGlobalCenter() -> Vector2:
	return global_position - getSpriteOffset().rotated(global_rotation) * 2.0

func getTextureSize_local() -> Vector2:
	return sprite.texture.get_size() * sprite.scale * scale

func scaleToFit_local(maxSize: Vector2, maxScale: float):
	var size = getTextureSize_local()
	var fill = size / maxSize
	scale /= max(1.0 / maxScale, max(fill.x, fill.y))

func getSpriteOffset_local() -> Vector2:
	return - sprite.offset * sprite.scale * scale * 0.5


func setTexture(newTex):
	sprite.texture = newTex
	initSpriteMaterial()

func updateShadowTexture():
	shadows[0].texture = sprite.texture

func initSpriteMaterial():
	if sprite.texture is AtlasTexture:
		var atlasTranslation = sprite.texture.region.position
		var subTexSize = sprite.texture.region.size
		var atlasSize = sprite.texture.atlas.get_size()
		progressMaterial.set_shader_param("atlasTranslation", atlasTranslation / atlasSize)
		progressMaterial.set_shader_param("atlasScaling", subTexSize / atlasSize)
	else:
		
		progressMaterial.set_shader_param("atlasTranslation", Vector2.ZERO)
		progressMaterial.set_shader_param("atlasScaling", Vector2.ONE)


func updateShaderRotation():
	if nonRotatedProgress != 0:
		if not sprite.material:
			giveProgressMaterial()
		sprite.material.set_shader_param("direction", Vector2.DOWN.rotated( - global_rotation))
		showCooldown(nonRotatedProgress)
		var size = getSizeInCells()
		if size.x > 0 and size.y > 0:
			var scaling = Vector2(1.0, 0.8).rotated( - global_rotation)
			sprite.material.set_shader_param("scale", size * scaling)
			
			var rotatedSize = size.rotated( - global_rotation)
			
			
			
			
			var thickness = 0.1 / abs(rotatedSize.y)
			sprite.material.set_shader_param("thickness", thickness)

var shaderTween
var canCancelShaderTween = true
var nonRotatedProgress = 0.0

func allowCancelShaderTween():
	canCancelShaderTween = true

func rotateProgress(progress: float):
	
	
	match faceDirection:
		FaceDirection.UP:
			progress = 1.0 - progress
		FaceDirection.RIGHT:
			progress = 1.0 - progress
		FaceDirection.LEFT:
			progress = - progress
		FaceDirection.DOWN:
			progress = - progress
	return progress

func showCooldownSmooth(progress: float, fill: bool = false):
	if not canCancelShaderTween:
		return
	
	Util.killTween(shaderTween)
	shaderTween = create_tween()
	
	if fill:
		canCancelShaderTween = false
		shaderTween.tween_method(self, "showCooldown", nonRotatedProgress, 1.0, 0.1)
		shaderTween.tween_callback(self, "allowCancelShaderTween")
		shaderTween.tween_method(self, "showCooldown", 0.0, progress, 0.1)
	else:
		shaderTween.tween_method(self, "showCooldown", nonRotatedProgress, progress, 0.2)

func showCooldown(progress: float):

	nonRotatedProgress = progress
	if progress != 0:
		if not sprite.material:
			updateShaderRotation()
		progress = rotateProgress(progress * 1.0 + 0.05)
		sprite.material.set_shader_param("progress", progress)
	else:
		clearSpriteMaterial()

func activateCooldown():
	set_physics_process(true)

func deactivateCooldown():
	set_physics_process(false)

func onAfterEffectFinished(_consume = true):
	deactivateCooldown()
	showCooldownSmooth(0, true)
	if _consume:
		consume()

func getRelativeOpponentHealth():
	return opponent().getRelativeHealth()

func getRelativeHealth():
	return character().getRelativeHealth()

const MISS_OFFSET = 100.0

func createAnimation():
	var ani = ObjectPool.instance(descriptor.animationScene)
	Game.combatAnimationsNode.add_child(ani)
	
	if ownerType != Owner.Opponent:
		ani.scale.x = 1
	else:
		ani.scale.x = - 1
		
	if ani.showOnSelf:
		ani.position = character().position
		ani.scale.x *= - 1
	else:
		ani.position = opponent().position
	
	return ani

func playAnimation(hit: bool = true):
	if not descriptor.animationScene: return
	
	var ani = createAnimation()
	ani.intialize(hit)

func isGem():
	return false

func hasTag(tag) -> bool:
	return descriptor.hasTag(tag)

func canDamage() -> bool:
	return getBaseMinDamage() > 0 or hasTag(Tag.Lifesteal)

func canUseStamina() -> bool:
	return getBaseStaminaCost() > 0

func canHealOrLifesteal() -> bool:
	return descriptor.hasParam("heal") or descriptor.hasParam("lifesteal")

func gainsStack(stackType) -> bool:
	return descriptor.gainedStacks & stackType

func removesStack(stackType) -> bool:
	return descriptor.removedStacks & stackType

func usesStack(stackType) -> bool:
	return descriptor.usedStacks & stackType


func gainsBuffs() -> bool:
	return descriptor.gainedStacks & Stack.Buff

func usesBuffs() -> bool:
	return descriptor.usedStacks & Stack.Buff

func inflictsDebuffs() -> bool:
	return descriptor.gainedStacks & Stack.Debuff

func isBattleRageItem() -> bool:
	return descriptor.hasBattleRageEffect


func connectToCharacterBuffs(methodName):
	for buff in Game.getBuffs():
		connectForCombat(character(), character().buffs[buff].signalName, methodName)

func connectToCharacterDebuffs(methodName):
	for debuff in Game.getDebuffs():
		connectForCombat(character(), character().buffs[debuff].signalName, methodName)

func connectToOpponentDebuffs(methodName):
	for debuff in Game.getDebuffs():
		connectForCombat(opponent(), opponent().buffs[debuff].signalName, methodName)

func connectToOpponentBuffs(methodName):
	for buff in Game.getBuffs():
		connectForCombat(opponent(), opponent().buffs[buff].signalName, methodName)


func pickRandomStacks(stackTypes, numStacks, target, priorityStack = null):
	var stacks = Dictionary()
	for stackType in stackTypes:
		var numTargetStacks = target.getStacks(stackType)
		if numTargetStacks > 0:
			stacks[stackType] = numTargetStacks
	
	var pickedStacks = Dictionary()
	
	if priorityStack != null:
		var pickedPriorityStacks = min(numStacks, stacks.get(priorityStack, 0))
		if pickedPriorityStacks > 0:
			pickedStacks[priorityStack] = pickedPriorityStacks
			numStacks -= pickedPriorityStacks
			Util.dictSub(stacks, priorityStack, pickedPriorityStacks)
	
	for i in numStacks:
		if not stacks.empty():
			var stackType = Util.pickRandomElement(stacks.keys())
			Util.dictAdd(pickedStacks, stackType, 1)
			Util.dictSub(stacks, stackType, 1)
	
	return pickedStacks


func pickRandomStacksToGive(stackTypes, numStacks):
	var pickedStacks = Dictionary()
	for i in numStacks:
		var stackType = Util.pickRandomElement(stackTypes)
		Util.dictAdd(pickedStacks, stackType, 1)
		
	return pickedStacks

func giveRandomBuffs(numBuffs: int, triggerEvent = null, availableBuffs = Game.getBuffs(), 
	target = character()):
		
	var pickedBuffs = pickRandomStacksToGive(availableBuffs, numBuffs)
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for buff in pickedBuffs:
		giveStacks(target, buff, pickedBuffs[buff], triggerEvent)
	EventBus.flushLoggingQueue()

func giveAllBuffs(numBuffs = 1, triggerEvent = null):
	for buff in Game.getBuffs():
		giveStacks(character(), buff, numBuffs)


func useRandomBuffs(numBuffs, triggerEvent = null, availableBuffs = Game.getBuffs()):
	var pickedBuffs = pickRandomStacks(availableBuffs, numBuffs, character())
	if pickedBuffs.empty():
		return null
	
	var events = []
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for buff in pickedBuffs:
		var event = character().useStacks(buff, pickedBuffs[buff], self, triggerEvent)
		events.push_back(event)
	EventBus.flushLoggingQueue()
	return events

func inflictRandomDebuffs(numDebuffs, triggerEvent = null, availableDebuffs = Game.getDebuffs()):
	var pickedDebuffs = pickRandomStacksToGive(availableDebuffs, numDebuffs)
	
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for debuff in pickedDebuffs:
		giveStacks(opponent(), debuff, pickedDebuffs[debuff], triggerEvent)
		
		
		
	EventBus.flushLoggingQueue()
	

func removeRandomBuffs(numBuffs, triggerEvent = null):
	var removedStacks = pickRandomStacks(Game.getBuffs(), numBuffs, opponent())
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for buff in removedStacks:
		opponent().loseStacks(buff, removedStacks[buff], self, triggerEvent)
	EventBus.flushLoggingQueue()

func stealRandomBuff(numBuffs, triggerEvent = null, 
	possibleBuffs = Game.getBuffs(), priorityBuff = null):
	
	
	var removedStacks = pickRandomStacks(possibleBuffs, numBuffs, opponent(), priorityBuff)
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for buff in removedStacks:
		opponent().loseStacks(buff, removedStacks[buff], self, triggerEvent)
		
		
		
		giveStacks(character(), buff, removedStacks[buff], triggerEvent)
	EventBus.flushLoggingQueue()
	

func cleanseRandomDebuffs(numDebuffs, triggerEvent = null):
	var cleansedDebuffs = pickRandomStacks(Game.getDebuffs(), numDebuffs, character())
	
	
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for debuff in cleansedDebuffs:
		character().loseStacks(debuff, cleansedDebuffs[debuff], self, triggerEvent)
		
		
		
	EventBus.flushLoggingQueue()
	
	

func getLeastStacks(numStacks, target, availableStacks):
	var priorStacks: = {}
	for stackType in availableStacks:
		priorStacks[stackType] = target.getStacks(stackType)
	
	var pickedStacks: = {}
	
	
	while numStacks > 0:
		var leastStacksCount: int = 10000
		var leastStacks = []
		for stackType in priorStacks:
			if priorStacks[stackType] < leastStacksCount:
				leastStacksCount = priorStacks[stackType]
				leastStacks.clear()
				leastStacks.push_back(stackType)
			elif priorStacks[stackType] == leastStacksCount:
				leastStacks.push_back(stackType)
		var stackToGive = Util.pickRandomElement(leastStacks)
		Util.dictAdd(pickedStacks, stackToGive, 1)
		Util.dictAdd(priorStacks, stackToGive, 1)
		numStacks -= 1
	
	return pickedStacks

func giveLeastBuffs(numBuffs, target = character(), triggerEvent = null, 
	availableBuffs = Game.getBuffs()):
	
	var pickedStacks = getLeastStacks(numBuffs, target, availableBuffs)
	
	for buffType in pickedStacks:
		giveStacks(target, buffType, pickedStacks[buffType], triggerEvent)

func getMostStacks(target, availableStacks):
	var buffs = Dictionary()
	for buff in availableStacks:
		buffs[buff] = target.getStacks(buff)

	var maxBuffs = []
	var maxStacks = 0
	for buff in buffs:
		if buffs[buff] == maxStacks:
			maxBuffs.push_back(buff)
		elif buffs[buff] > maxStacks:
			maxBuffs.clear()
			maxBuffs.push_back(buff)
			maxStacks = buffs[buff]
	
	return maxBuffs

func giveMostBuffs(numBuffs, triggerEvent = null, availableBuffs = Game.getBuffs()):
	var maxBuffs = getMostStacks(character(), availableBuffs)
	var buffToGive = Util.pickRandomElement(maxBuffs)
	giveStacks(character(), buffToGive, numBuffs, triggerEvent)


func removeMostBuffs(numBuffs, triggerEvent = null, use: bool = false, availableBuffs = Game.getBuffs()):
	var target
	
	var buffs = Dictionary()
	if use:
		target = character()
	else:
		target = opponent()
	
	var maxBuffs = getMostStacks(target, availableBuffs)
	var buffToRemove = Util.pickRandomElement(maxBuffs)
	
	var toRemove = min(numBuffs, target.getStacks(buffToRemove))
	if toRemove == 0:
		return null
	
	var event
	if use:
		event = character().useStacks(buffToRemove, toRemove, self, triggerEvent)
	else:
		event = opponent().loseStacks(buffToRemove, toRemove, self, triggerEvent)
	return event


func getStackFraction(target, fraction: float, 
	limit: int, availableStacks):
	
	var sum: = 0.0
	var stacksUnlimited: = {}
	
	for buff in availableStacks:
		var prior = target.getStacks(buff)
		
		var withBonus = prior * fraction
		stacksUnlimited[buff] = withBonus
		sum += withBonus
	
	var sumRounded = round(sum)
	if sumRounded == 0: return null
	
	var totalToGive: float = min(limit, sumRounded)
	var limitFactor = totalToGive / sumRounded
	
	var buffsToGive: = {}
	var overflow: = {}
	var totalGiven: = 0
	
	for buff in stacksUnlimited:
		var limited = stacksUnlimited[buff] * limitFactor
		var guaranteed = int(limited)
		buffsToGive[buff] = guaranteed
		overflow[buff] = limited - guaranteed
		totalGiven += guaranteed
		
	
	var overflowBuffs: = totalToGive - totalGiven
	var sortedOverflow: Array = Util.sortDict(overflow, true)
	
	for buff in sortedOverflow:
		if overflowBuffs == 0:
			break
		
		buffsToGive[buff] += 1
		overflowBuffs -= 1
	
	return buffsToGive

func multiplyBuffsLimit(bonus: float, limit: int, 
	availableBuffs = Game.getBuffs()):
	
	var buffsToGive = getStackFraction(character(), bonus, limit, availableBuffs)
	if buffsToGive == null: return
	
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for buff in buffsToGive:
		giveStacks(character(), buff, buffsToGive[buff])
	EventBus.flushLoggingQueue()

func removeBuffsFraction(fraction: float, limit: int, 
	triggerEvent = null, availableBuffs = Game.getBuffs()):
	
	var buffsToRemove = getStackFraction(opponent(), fraction, limit, availableBuffs)
	if buffsToRemove == null: return
	
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for buff in buffsToRemove:
		opponent().loseStacks(buff, buffsToRemove[buff], self, triggerEvent)
	EventBus.flushLoggingQueue()

func stealBuffsFraction(fraction: float, limit: int, 
	triggerEvent = null, availableBuffs = Game.getBuffs()):
	
	var buffsToSteal = getStackFraction(opponent(), fraction, limit, availableBuffs)
	if buffsToSteal == null: return
	
	EventBus.setLoggingMode(EventBus.LoggingMode.Delayed)
	for buff in buffsToSteal:
		stealStack(buff, buffsToSteal[buff], triggerEvent)
	EventBus.flushLoggingQueue()

func changeAllItemsCritRate(amount):
	for item in inventory.getItems():
		if item.canBeEmpowered():
			item.changeCritChancePercent(amount)

func hasInventoryDuration() -> bool:
	return descriptor.hasParam("dur")

func connectForCombat(emitter, signalName, methodName, binds = []):
	EventBus.connectEvent(emitter, signalName, self, methodName)

func connectForCombat_signal(emitter, signalName, methodName, binds = []):
	var newConnection = SignalConnection.new(emitter, signalName, 
		self, methodName, binds)
	combatConnections.push_back(newConnection)

func disconnectCombat():
	for connection in combatConnections:
		connection.destroy()
	combatConnections.clear()


func placeGeneratedItem(item, candidateCells):
	var foundSpace = false
	for cell in candidateCells:
		if inventory.isCellEmpty(cell):
			inventory.orientAndAddItem(item, cell, FaceDirection.UP)
			
			foundSpace = true
			item.moveTo(global_position, item.global_position, 0.2)
			item.locked = true
			if Game.itemsAreFusing:
				Util.callDelayed(item, "unlockCombining", PRE_FUSE_DUR, [false])
			else:
				item.call_deferred("unlockCombining", false)
			break
	
	if not foundSpace:
		Game.playerNode.add_child(item)
		item.global_position = global_position
		item.pushToStorage(Game.STORAGEBOX.center + Util.randInBox(100, 100))

func reveal():
	sprite.set_material(grayscaleMaterial)
	animation.play("Reveal")

func setRevealed():
	reveal()
	animation.advance(1)

func isCrafted() -> bool:
	return descriptor.isCraftedItem()

func isTreasure() -> bool:
	return descriptor.randomUniquePool

func shift(direction: Vector2):
	if isBag():
		
		if Game.inventoryEditMode != Game.InventoryEditMode.Default:
			CraftingManager.itemShifted(self)
			
		
		if Game.inventoryEditMode == Game.InventoryEditMode.ItemLayer:
			return
	else:
		if Game.inventoryEditMode == Game.InventoryEditMode.BagLayer:
			return
	
	finishMoveback()
	resetSprite()
	
	var pixelShift = direction * inventory.cellSize
	
	if dragged:
		pickupPosition += pixelShift
	else:
		position += pixelShift

	for i in occupiedCells.size():
		occupiedCells[i] = occupiedCells[i] + direction
	
	cacheAffectedCells()
	
	for gem in getGemsNoNull():
		gem.shift(direction)

func isMovingBack() -> bool:
	return Util.isTweenRunning(movebackTween)

func _notification(what: int) -> void :
	if what == NOTIFICATION_PREDELETE:
		Game.itemHoverEnd(self)
		if is_instance_valid(tooltip):
			clearTooltip()
		for visual in bondVisuals:
			if is_instance_valid(visual):
				visual.breakInstant()

func isShowCaseItem() -> bool:
	return character() == null

func getAllInInventoryOfType(descr) -> Array:
	if isOwnedByOpponent():
		return ItemBook.getItemsInInventoryOfType_opponent(descr)
	else:
		return ItemBook.getItemsInInventoryOfType(descr)

func countAllInInventoryOfType(descr) -> int:
	if isOwnedByOpponent():
		return ItemBook.countItemsInInventoryOfType_opponent(descr)
	else:
		return ItemBook.countItemsInInventoryOfType(descr)

func countAllPlacedOfType(descr) -> int:
	if isOwnedByOpponent():
		return ItemBook.countItemsInInventoryOfType_opponent(descr)
	else:
		return ItemBook.countPlacedItemsInInventoryOfType(descr)

func isTypeInInventory(descr) -> bool:
	if isOwnedByOpponent():
		return ItemBook.isItemInInventory_opponent(descr)
	else:
		return ItemBook.isItemInInventory(descr)



func isRecipeFinished():
	return curRecipe.getProgress(bondedIngredients) == 1

func getNeighborItemsAndGems():
	var neighbors = inventory.getAdjacentItems(self)
	neighbors.append_array(getGemsNoNull())
	for neighbor in neighbors:
		var neighborGems = neighbor.getGemsNoNull()
		neighbors.append_array(neighborGems)
	return neighbors

func getCraftableNeighbors():
	var craftableNeighbors = []
	
	for neighbor in getNeighborItemsAndGems():
		if neighbor.isAvailableForCrafting():
			craftableNeighbors.push_back(neighbor)
		
	for bag in getTouchedBags():
		if bag.isAvailableForCrafting():
			craftableNeighbors.push_back(bag)
	
	return craftableNeighbors


func getBusyNeighbors():
	var busyNeighbors = []
	
	for neighbor in getNeighborItemsAndGems():
		if neighbor.isBusy():
			busyNeighbors.push_back(neighbor)
		
	for bag in getTouchedBags():
		if bag.isBusy():
			busyNeighbors.push_back(bag)
	
	return busyNeighbors
	
	

func canCombine() -> bool:
	return placed

func canStartNewRecipe() -> bool:
	return not isBaseItem() and isAvailableForCrafting()

func isAvailableForCrafting() -> bool:
	return not isBoundAsIngredient() and not isLocked() and not fusing


func isBusy() -> bool:
	return curRecipe != null or isBoundAsIngredient()

func getRecipes(checkClassAvailability = true):
	var recipes = []
	for recipe in descriptor.recipes:
		
		recipes.push_back(recipe)
	return recipes
	

func isBaseItem():
	return not bondedIngredients.empty()

func breakBondVisual(toItem):
	var bondIndex = bondedIngredients.find(toItem)
	if bondIndex != - 1:
		bondVisuals[bondIndex].breakBond()
		bondVisuals.erase(bondVisuals[bondIndex])


func removeBondedBaseItem():
	bondedBaseItem = null
	setBoundAsIngredient(false)

func removeBondedIngredient(item):
	
	breakBondVisual(item)
	bondedIngredients.erase(item)
	
	
	if fusing:
		return
	
	showProgressLabel()
	
	if bondedIngredients.empty():
		curRecipe = null
		
	else:
		updateBondVisuals()

func removeAllIngredients():


	bondedIngredients.clear()
	for visual in bondVisuals:
		visual.breakBond()
	bondVisuals.clear()
	
	showProgressLabel()
	curRecipe = null
	
	









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
		curRecipe = forRecipe
	
	bondedIngredients.push_back(neighbor)
	createBondVisual(neighbor)
	updateBondVisuals()
	playBondAnimation()
	
	if neighbor.placedByPlayer or placedByPlayer:
		showProgressLabel()

func addToBaseItem(baseItem):
	bondedBaseItem = baseItem
	setBoundAsIngredient(true)
	playBondAnimation()

func playBondAnimation():
	animation.advance(10)
	
	var catalyst: = false
	if bondedBaseItem != null:
		if bondedBaseItem.curRecipe != null:
			catalyst = bondedBaseItem.curRecipe.isCatalystRecipe()
	else:
		if curRecipe != null:
			catalyst = curRecipe.isCatalystRecipe()
	
	if catalyst:
		animation.play("CatalystBondCreated")
	else:
		animation.play("BondCreated")

func playBondFailedAnimation():
	animation.advance(10)
	animation.play("BondFailed")

func isCatalystBond(bondedItem) -> bool:
	if curRecipe == null:
		return false
	
	return curRecipe.isNeighborCatalyst(bondedItem)

func isLocked() -> bool:
	return locked

func canLockBag():
	return false

func canBeLocked() -> bool:
	if (ownerType == Owner.PlayerInventory or 
		ownerType == Owner.PlayerStorageBox or 
		(ownerType == Owner.Socket and character() == Game.PLAYER)):
		
		if Game.state == Game.State.Combat:
			return focus
		else:
			return canBePicked()
		
	return false

func setLocked(_locked, showLabel = true):
	
	if locked == _locked: return
	
	if _locked:
		lockCombining(showLabel)
	else:
		unlockCombining()
	lockAnimation.advance(1)

func unlockCombining(playAni: bool = true):
	
	locked = false
	if playAni:
		lockAnimation.play("Unlock")
	if canCombine():
		CraftingManager.itemAdded(self)
	previewFusions()
	Sound.playSound(unlockSound, 0, Util.rng.randf_range(0.95, 1.05))
	
	
	
func lockCombining(showLabel = true):
	
	
	locked = true
	lockAnimation.play("Lock")
	if canCombine():
		CraftingManager.itemRemoved(self)
	previewFusions()
	if showLabel:
		showLockLabel()
		Sound.playSound(lockSound, 0, Util.rng.randf_range(0.95, 1.05))

func showLockLabel():
	var label = ObjectPool.instance(lockLabelScene)
	Game.labelsNode.add_child(label)
	if locked:
		label.lock()
	else:
		label.unlock()
		
	label.global_position = Util.clampToScreen(global_position
		+ label.label.rect_position) - label.label.rect_position

func getLockPosition() -> Vector2:
	return lock.global_position

func isBoundAsIngredient():
	return bound

func setBoundAsIngredient(_bound: bool):
	bound = _bound


func canPreviewFusions():
	return ((ownerType == Owner.Shop or 
		ownerType == Owner.PlayerInventory or 
		ownerType == Owner.PlayerStorageBox) and 
		Game.state == Game.State.Shop)

func getGemsOfItems(items):
	var gems = []
	for item in items:
		gems.append_array(item.getGemsNoNull())
	return gems

func getCraftingPreviewPosition():
	return getGridStorageProxy().global_position

func previewFusions():
	if canPreviewFusions():
		CraftingManager.hideFusionPreviews()
		call_deferred("previewRecipeIngredients")
		CraftingManager.call_deferred("previewFusionToItem", self)

func previewRecipeIngredients():
	var ingredients = Dictionary()
	var nonDescriptorIngredients = Array()
	
	for recipe in getRecipes(false):
		for ingredient in recipe.ingredients:
			if Util.isItemDescriptor(ingredient):
				ingredients[ingredient] = true
			else:
				nonDescriptorIngredients.push_back(ingredient)
		
	if ingredients.empty() and nonDescriptorIngredients.empty(): return
	
	var candidateItems = ItemBook.getInventoryStorageShopItems()
	
	for candidate in candidateItems:
		if candidate != self and (candidate.descriptor in ingredients
				or typeInIngredients(candidate, nonDescriptorIngredients)):
			if ( not candidate in bondedIngredients and 
				not self in candidate.bondedIngredients):
				CraftingManager.call_deferred("createFusionPreview", 
					self, candidate, getGridStorageProxy())

func previewFusionToItem(hoveredIngredient):
	for recipe in getRecipes(false):
		for ingredient in recipe.ingredients:
			if (recipe.fitsIngredient(hoveredIngredient, ingredient) and 
				not hoveredIngredient in bondedIngredients and 
				not self in hoveredIngredient.bondedIngredients):
				CraftingManager.call_deferred("createFusionPreview", 
					self, hoveredIngredient, hoveredIngredient.getGridStorageProxy())
				break

func hasShopItemCraftCandidates() -> bool:
	
	var candidates: Array = ItemBook.getInventoryStorageShopItems()
	
	var ingredients = Dictionary()
	var nonDescriptorIngredients = Array()
	
	for recipe in getRecipes(false):
		for ingredient in recipe.ingredients:
			if Util.isItemDescriptor(ingredient):
				ingredients[ingredient] = true
			else:
				nonDescriptorIngredients.push_back(ingredient)
		
	if not ingredients.empty() or not nonDescriptorIngredients.empty():
		for candidate in candidates:
			if candidate != self and (candidate.descriptor in ingredients
					or typeInIngredients(candidate, nonDescriptorIngredients)):
				return true
	
	
	for item in candidates:
		if item != self and item.isBaseItemForShopItem(self):
			return true
	
	return false

func isBaseItemForShopItem(item) -> bool:
	for recipe in getRecipes(false):
		for ingredient in recipe.ingredients:
			if recipe.fitsIngredient(item, ingredient):
				return true
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
	if not curRecipe: return
	
	var curNum = bondedIngredients.size() + 1
	if curNum == 1:
		if craftingLabel:
			craftingLabel.fade()
		return
	
	var outOf = curRecipe.getNumIngredients() + 1
	var fusionName = getFusionItemName()
	var counter = curRecipe.getCurIngredientsCounter(bondedIngredients)










	
	if craftingLabel:
		craftingLabel.updateProgress(fusionName, curNum, outOf, 
			counter)
	else:
		craftingLabel = ObjectPool.instance(craftingLabelScene)
		
		craftingLabel.connect("returned_to_pool", self, 
			"onCraftingLabelReturned", [], CONNECT_ONESHOT)
		Game.labelsNode.add_child(craftingLabel)
		craftingLabel.showProgress(fusionName, curNum, outOf, 
			counter)
	
	var topLeftLimit = Vector2(30, 25)
	var itemTopY = getTopLeftGlobal().y - global_position.y
	var counterOffset = counter.size() * 40
	var labelTopLeft = global_position + Vector2(0, itemTopY - counterOffset + 20) + craftingLabel.label.rect_position
	labelTopLeft.x = max(labelTopLeft.x, topLeftLimit.x)
	labelTopLeft.y = max(labelTopLeft.y, topLeftLimit.y)
	craftingLabel.global_position = labelTopLeft - craftingLabel.label.rect_position
	
	if curNum == outOf:
		Game.onCraftingReady(self)
		if Util.time >= craftingAniReadyTime:
			craftingAniReadyTime = Util.time + 0.3
			var ani
			var pitch = Util.rng.randf_range(0.97, 1.03)
			if curRecipe.isCatalystRecipe():
				ani = ObjectPool.instance(catalystReadyAnimation)
				pitch += 0.1
			else:
				ani = ObjectPool.instance(craftingReadyAnimation)
				pitch -= 0.05
				
			Game.UINode.add_child(ani)
			ani.global_position = global_position
			var scaling = 0.2 + (0.4 * sqrt(getNumOccupiedCells()))
			ani.scale = Vector2(scaling, scaling)
			ani.get_node("AnimationPlayer").play("Shockwave")
			Sound.playSound(craftingReadySound, 3, pitch)

func onCraftingLabelReturned():
	craftingLabel = null

func createBondVisual(bondNeighbor):
	var visual
	if curRecipe == null:
		visual = ObjectPool.instance(craftingBondScene)
	elif curRecipe.isNeighborCatalyst(bondNeighbor):
		visual = ObjectPool.instance(catalystBondScene)
	else:
		visual = ObjectPool.instance(craftingBondScene)
	
	if isGem() and self.socket:
		self.socket.getItem().get_parent().add_child(visual)
	else:
		get_parent().add_child(visual)
	
	visual.create(self, bondNeighbor)
	bondVisuals.push_back(visual)
	

func updateBondVisuals():
	for visual in bondVisuals:
		if curRecipe == null or curRecipe.getProgress(bondedIngredients) == 1:
			visual.setStrong()
		else:
			visual.setWeak()

const PRE_FUSE_DUR = 1.0
const PRE_FUSE_DUR_COG = 0.2
const FUSE_DUR = 1.0
const TRANSFORMATION_DUR = 1.0
const fuseMaterial = preload("res://Shader/ItemFuseMaterial.tres")
const fuseParticlesScene1 = preload("res://Shader/ItemsFusingParticles.tscn")
const fuseParticlesScene2 = preload("res://Shader/ItemFuseParticles.tscn")
const fuseSound1 = preload("res://Assets/Sound/Boil.ogg")
const fuseSound2 = preload("res://Assets/Sound/Hammer2.ogg")
const fuseSound3 = preload("res://Assets/Sound/Craft.ogg")
const craftingReadySound = preload("res://Assets/Sound/Hammer4.mp3")

var fusing = false
var willBeConsumed = false
var fuseParticles1 = null
var fuseParticles2 = null
var fuseTween = null
var fusingBonds: Array

func fuse():
	
	

	var catalystBonds: Array
	var nonCatalystBonds: Array
	if curRecipe != null:
		catalystBonds = curRecipe.getCatalystBonds(bondedIngredients)
		nonCatalystBonds = curRecipe.getNonCatalystBonds(bondedIngredients)
	else:
		nonCatalystBonds = bondedIngredients
	
	for visual in bondVisuals:
		visual.breakBond()
	bondVisuals.clear()
	
	Sound.playSound(fuseSound1, 4)
	
	var fusedRarity: int
	if curRecipe != null:
		fusedRarity = curRecipe.fusedItem.rarity
		Util.callDelayed(self, "createCraftedShockwave", 0.8, [curRecipe.fusedItem])
	else:
		fusedRarity = getRarity()
	
	fuseTween = Util.refreshTween(fuseTween)
	fuseTween.set_parallel(true)
	var mat = fuseMaterial.duplicate()
	var catalystMat = null
	
	if not catalystBonds.empty():
		catalystMat = fuseMaterial.duplicate()
	
	for neighbor in bondedIngredients:
		neighbor.fusing = true
		neighbor.onFusingAsIngredient()
	
	for neighbor in nonCatalystBonds:
		neighbor.sprite.set_material(mat)
	
	for neighbor in catalystBonds:
		neighbor.sprite.set_material(catalystMat)
	
	var GROW_DUR = 0.17
	var SHRINK_DUR = 0.25
	var GROW_FACTOR = 1.1
	var timeUsed = 0.0
	while timeUsed <= FUSE_DUR:
		fuseTween.tween_property(sprite, getScaleProp(), 
			spriteScale * GROW_FACTOR, GROW_DUR).from(spriteScale).set_delay(timeUsed)
		fuseTween.tween_property(sprite, getScaleProp(), 
			spriteScale, SHRINK_DUR).from(spriteScale * GROW_FACTOR).set_delay(timeUsed + GROW_DUR)
		timeUsed += GROW_DUR + SHRINK_DUR
		
		GROW_FACTOR += 0.2
	
	var maxScale = Vector2(1.2, 1.2)
	var scaleDur = 0.7
	
	for neighbor in nonCatalystBonds:
		neighbor.z_index += 1
		fuseTween.tween_property(neighbor, "global_position", global_position, FUSE_DUR).set_trans(Tween.TRANS_QUAD).set_ease(Tween.EASE_IN)
		fuseTween.tween_property(neighbor, "scale", maxScale, scaleDur)
		fuseTween.tween_property(neighbor, "scale", Vector2(0.7, 0.7), FUSE_DUR - scaleDur).from(maxScale).set_delay(scaleDur)
	






	
	for neighbor in catalystBonds:
		fuseTween.tween_callback(neighbor, "onFusingAsCatalystFinished").set_delay(FUSE_DUR)
		
	sprite.set_material(mat)
	
	fuseTween.tween_property(mat, "shader_param/flashState", 1.0, FUSE_DUR).from(0.0)
	var flashColor = rarityColors[fusedRarity].lightened(0.4) * 4
	fuseTween.tween_property(mat, "shader_param/flashColor", flashColor, FUSE_DUR).from(Color(1, 1, 1, 1))
	
	
	if catalystMat != null:
		var undoFlashDur = 0.1
		fuseTween.tween_property(catalystMat, "shader_param/flashState", 1.0, FUSE_DUR - undoFlashDur).from(0.0)
		fuseTween.tween_property(catalystMat, "shader_param/flashState", 0.0, undoFlashDur).from(1.0).set_delay(FUSE_DUR - undoFlashDur)
		fuseTween.tween_property(catalystMat, "shader_param/flashColor", flashColor, FUSE_DUR).from(Color(1, 1, 1, 1))
	
	var particleNode = get_parent()
	
	var particleColor = rarityColors[fusedRarity].lightened(0.3) * 2.5
	fuseParticles1 = ObjectPool.instance(fuseParticlesScene1)
	particleNode.add_child(fuseParticles1)
	fuseParticles1.global_position = global_position
	fuseParticles1.self_modulate = particleColor
	fuseParticles1.modulate.a = 1
	fuseParticles1.scale = Vector2.ONE
	fuseParticles1.speed_scale = 1.0
	fuseParticles1.restart()
	
	fuseTween.tween_property(fuseParticles1, "speed_scale", 2.2, FUSE_DUR).from(1.0)
	fuseTween.tween_property(fuseParticles1, "scale", Vector2(0.3, 0.3), FUSE_DUR - 0.2).set_delay(0.2)
	fuseTween.tween_property(fuseParticles1, "modulate:a", 0.0, 0.2).set_delay(FUSE_DUR - 0.2)
	
	fuseParticles2 = ObjectPool.instance(fuseParticlesScene2)
	particleNode.add_child(fuseParticles2)
	
	if curRecipe == null:
		fuseParticles2.amount = 45
	else:
		fuseParticles2.amount = 35 + 5 * Game.itemLibrary.getInstance(curRecipe.fusedItem).getNumOccupiedCells()
		
	fuseParticles2.global_position = global_position
	fuseParticles2.self_modulate = particleColor
	
	fusingBonds = bondedIngredients.duplicate()
	
	
	
	
	if placed:
		for neighbor in nonCatalystBonds:
			if neighbor.placed:
				inventory.clearItemCells(neighbor)
	
	
	if isGem():
		z_index += 3
	
	bondedIngredients.clear()

func onFusingAsIngredient():
	pass

func onFusingAsCatalystFinished():
	clearSpriteMaterial()
	setBoundAsIngredient(false)

func createCraftedShockwave(fusedItem):
	var ani = ObjectPool.instance(craftedAnimation)
	Game.UINode.add_child(ani)
	ani.global_position = global_position
	var scaling = 0.5 + (0.5 * sqrt(Game.itemLibrary.getInstance(fusedItem).getNumOccupiedCells()))
	ani.scale = Vector2(scaling, scaling)
	ani.get_node("Sprite/Light").self_modulate = rarityColors[fusedItem.rarity].lightened(0.4)
	ani.get_node("AnimationPlayer").play("Shockwave")

func finishFusing():
	Util.finishTween(fuseTween)
	Sound.playSound(fuseSound3, 6)
	
	fuseParticles1.emitting = false
	Util.callDelayed(fuseParticles1, "returnToObjectPool", 2.0)
	fuseParticles1 = null
	
	fuseParticles2.restart()
	Util.callDelayed(fuseParticles2, "returnToObjectPool", 7.0)
	fuseParticles2 = null
	
	
	var validBonds = []
	for bond in fusingBonds:
		if is_instance_valid(bond):
			validBonds.push_back(bond)
	
	fusingBonds.clear()
	
	
	
	var nonCatalystBonds: Array
	if curRecipe != null:
		nonCatalystBonds = curRecipe.getNonCatalystBonds(validBonds)
	else:
		nonCatalystBonds = validBonds
	
	if curRecipe != null:
		
		curRecipe.fuse(self, validBonds)
		
	else:
		onFusingFinished(validBonds)

func allowGeneratingFusionItem() -> bool:
	return true

func catalystFusingFinished():
	fusing = false
	bondedBaseItem = null
	updateShaderRotation()
	CraftingManager.itemAdded(self)

func onFusingFinished(validBonds):
	for item in validBonds:
		item.pushGemsToStorage()
		item.inventory.removeItem(item)
		item.discard()
	
	fusing = false
	clearSpriteMaterial()
	enablePicking()
	CraftingManager.itemAdded(self)

func onCraftedFrom(baseItem, ingredients):
	pass

func getCraftingOffset(_forDirection):
	return Vector2.ZERO


func playCraftedAnimation(originPosition: Vector2):
	moveTo(originPosition, global_position, 0.2)
	animation.advance(10)
	animation.play("Crafted")

const labelOffsets = [Vector2.ZERO, Vector2(30, 30), Vector2( - 30, 30), 
	Vector2(30, - 30), Vector2( - 30, - 30)]

func getNextFreeLabelPosition() -> Vector2:
	var pos = global_position
	for i in buffLabelPositionTimestamps.size():
		var time = buffLabelPositionTimestamps[i]
		if Util.time >= time:
			buffLabelPositionTimestamps[i] = Util.time + 0.5
			pos += labelOffsets[i]
			pos += Util.randInBox(10, 10)
			return pos
	return pos + Util.randInBox(30, 30)

func countTypes(ofItems: Array) -> Dictionary:
	var typesDict = {}
	for type in Type:
		typesDict[Type[type]] = 0
	
	for item in ofItems:
		for type in item.getTypes():
			typesDict[type] += 1
	
	return typesDict

func insertCounter(text: String, keyword: String, amount: int) -> String:
	var counter = Util.tra("Rainbow Orb_Counter").replace("$num", Util.highlight(amount))
	text = text.replace("$" + keyword, counter)
	return text

func onRestoreSnapshot():
	finishMoveback()
	animation.advance(10)
	animation.play("RestoreSnapshot")

func getShopPriority() -> int:
	return Priority.Normal



func findBondsWithAffectedItems():
	if ownerType != Owner.PlayerInventory:
		return
	
	if locked or not placed:
		for bonded in bondedIngredients:
			bonded.removeBondedBaseItem()
		removeAllIngredients()
		return
	
	if isBoundAsIngredient() or fusing:
		return
	
	for item in getAffectedItems():
		if item.canStartNewRecipe():
			
			bondedIngredients.push_back(item)
			createBondVisual(item)
			updateBondVisuals()
			item.addToBaseItem(self)

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
		Util.tryDisconnect(emitter, signalName, receiver, methodName)
		
