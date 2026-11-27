# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

    Color,
    Dictionary,
    EnumDict,
    FuncRef,
    GD_DEFAULT,
    INF,
    NAN,
    Node,
    Node2D,
    OS_has_feature,
    Object,
    PCG32,
    PI,
    PoolStringArray,
    RandomNumberGenerator,
    Reference,
    Resource,
    Signal,
    String,
    TAU,
    TYPE_VECTOR2,
    Vector2,
    Vector3,
    _HoistPending,
    _bind_battle,
    _div,
    _dup,
    _erase,
    _fill,
    _find,
    _gd_fmt,
    _gd_range,
    _gd_str,
    _get_slice,
    _gid,
    _has_behavior_cache_get,
    _has_behavior_cache_put,
    _hash,
    _invert,
    _iter,
    _join,
    _load,
    _mod,
    _os_environ_get,
    _pick_random,
    _pop_at,
    _resize,
    _shuffle,
    _sort_custom,
    _strv,
    _substr,
    ceil,
    clamp,
    deg2rad,
    f32,
    floor,
    fmod,
    gd_round,
    get_stack,
    inverse_lerp,
    is_equal_approx,
    is_instance_valid,
    lerp,
    move_toward,
    posmod,
    pow,
    rad2deg,
    randomize,
    round,
    sign,
    smoothstep,
    snapped,
    sqrt,
    stepify,
    tr,
    typeof,
    wrapf,
    wrapi
,
)

if "GodotObject" not in globals():
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_Item_2" not in globals():
	from ..gd_core.CoreItem import CoreItem as _base_cls_Item_2





class SignalConnection(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self.emitter = None
		self.signalName = None
		self.receiver = None
		self.methodName = None


	def _init(self, _emitter, _signalName, _receiver, _methodName, binds=[]):
		self.emitter = _emitter
		self.signalName = _signalName
		self.receiver = _receiver
		self.methodName = _methodName

		self.emitter.connect(self.signalName, self.receiver, self.methodName, binds)

	def destroy(self):
		pass


class Item_2(_base_cls_Item_2):

	resource_path = "res://gd_core_items/Item.gd"

	Owner = EnumDict("Owner", {"Shop": 0, "PlayerInventory": 1, "PlayerStorageBox": 2, "Opponent": 3, "Title": 4, "RecipeBook": 5, "Tooltip": 6, "Socket": 7, "ItemLibrary": 8, "InfoPanelIcon": 9, "BuildViewer": 10, "BuildViewerIcon": 11, "GridStorage": 12, "Undefined": 13})

	Type = EnumDict("Type", {"Bag": 0, "Consumable": 1, "Food": 2, "Pet": 3, "Weapon": 4, "Shield": 5, "Armor": 6, "Gloves": 7, "Shoes": 8, "Helmet": 9, "Accessory": 10, "Potion": 11, "Card": 12, "Gem": 13, "Scroll": 14, "Book": 15, "Skill": 16, "ChessPiece": 17, "Spell": 18, "Melee": 19, "Ranged": 20, "Effect": 21, "Holy": 22, "Magic": 23, "Vampiric": 24, "Dark": 25, "Nature": 26, "Fire": 27, "Ice": 28, "Musical": 29})

	Priority = EnumDict("Priority", {"Lowest": -10000, "Low": -1000, "Normal": 0, "High": 1000, "Highest": 10000})

	CraftingPriority = EnumDict("CraftingPriority", {"Gem": 3, "Mixed": 2, "NonGem": 1})

	Tag = EnumDict("Tag", {"None": 0, "Lifesteal": 1, "Stone": 2, "Scroll": 8, "Dragon": 16, "Staff": 32, "BattleRage": 64, "Singular": 128, "Transient": 256, "Bow": 512})

	Stack = EnumDict("Stack", {"None": 0, "Block": 1, "Lucky": 2, "Regeneration": 4, "Vampirism": 8, "Spikes": 16, "Mana": 32, "Empower": 64, "Heat": 128, "Poison": 256, "Blind": 512, "Cold": 1024, "Buff": 254, "Debuff": 1792, "BuffNoLuck": 252})

	Mat = EnumDict("Mat", {"Default": 0, "Wood": 1, "Metal": 2, "Leather": 3, "Glass": 4, "Stone": 5, "Squishy": 6, "Jewelry": 7, "Sand": 8, "Paper": 9, "Slime": 10, "Ice": 11, "Fire": 12, "Dragon": 13, "Bird": 14, "Leaf": 15})

	Physics = EnumDict("Physics", {"Default": 0, "Light": 1, "Slime": 2, "Dense": 3, "VeryDense": 4, "Floaty": 5, "Sand": 6, "Plush": 7, "BouncyDense": 8, "Ice": 9, "Ghost": 10, "BlackHole": 11})

	Rarity = EnumDict("Rarity", {"Common": 0, "Rare": 1, "Epic": 2, "Legendary": 3, "Godly": 4, "Unique": 5})

	FaceDirection = EnumDict("FaceDirection", {"UP": 0, "RIGHT": 1, "DOWN": 2, "LEFT": 3})

	StatModified = EnumDict("StatModified", {"No": 0, "Positive": 1, "Negative": 2})

	DropResult = EnumDict("DropResult", {"AddedToInventory": 0, "Hotswap": 1, "InventoryCollision": 2, "OutsideInventory": 3, "AddedToStorageBox": 4, "Sold": 5, "Socketed": 6, "SocketHotswap": 7, "Failed": 8})

	PickupType = EnumDict("PickupType", {"Grabbed": 0, "Hotswap": 1, "MultiSelect": 2})

	Affected = EnumDict("Affected", {"Primary": 0, "Secondary": 2, "Tertiary": 4, "Lightning": 7})

	Tiles = EnumDict("Tiles", {"Extension": 2, "Collision": 3, "Affected": 4, "AffectedDynamic": 5, "AffectedSecondary": 6, "AffectedSecondaryDynamic": 7, "AffectedExtension": 8, "AffectedTertiary": 10, "AffectedLightning": 11})

	ActivationAni = EnumDict("ActivationAni", {"Scale": 0, "Jump": 1, "SquishyJump": 2, "VerySquishyJump": 3, "Slash": 4, "Stab": 5, "Bonk": 6, "ReverseBonk": 7, "Chop": 8, "Squish": 9, "Block": 10, "Wave": 11, "Potion": 12, "Sweep": 13, "Spin": 14, "Throw": 15, "Shoot": 16, "Struggle": 17, "ReverseStab": 18, "Hiss": 19, "Tackle": 20, "DoubleSlash": 21, "Flash": 22})

	Stat = EnumDict("Stat", {"MinDamage": 0, "MaxDamage": 1, "StaminaCost": 2, "Speed": 3, "BaseCooldown": 4, "Accuracy": 5, "CritChance": 6, "Chance": 7, "Chance2": 8, "Cooldown": 9})

	StackChangeType = EnumDict("StackChangeType", {"Added_Player": 0, "Added_Opponent": 1, "Removed_Player": 2, "Removed_Opponent": 3, "Used_Player": 4, "Used_Opponent": 5})











	def _init_fields(self):
		super()._init_fields()
		self.numStackChangeTypes = len(_H_1)
		self.spriteScale = None
		self.hasSquishySprite = False
		self.specificDragParticles = []
		self.dragParticlesEnabled = True
		self.frictionTime = 15.0
		self.totalWeight = 0.0
		self.me = self
		self.mouseIsOverItem = False
		self.hovered = False
		self.focus = False
		self.spotlight = False
		self.collisionShape = None
		self.wasJustCrafted = False
		self.crafted_instance = -1
		self.pickupPosition = Vector2()
		self.pickupRotation = 0.0
		self.pickupTopLeftCell = Vector2()
		self._pickupFaceDirection = 0
		self.sameOrientationAsPickup = False
		self.movebackTween = None
		self.rotationTween = None
		self.pickingEnabled = True
		self.tooltipEnabled = True
		self.hoverResponseEnabled = True
		self.focusEnabled = True
		self.affectedCellsActive = True
		self.affordable = False
		self.momentumStrength = 0.0
		self.momentum = Vector2()
		self.tooltip = None
		self.tooltipMargin = Vector2(100, 0)
		self.tooltipUpdateQueued = False
		self.shadows = []
		self.spritesWithShadows = []
		self.shadowOffset = self.shadowOffset_dropped
		self.shadowTween = None
		self._dropFrame = 0
		self._pickupFrame = 0
		self.mouseWheelRotationReadyTime = 0.0
		self.notEnoughGoldLabelReadyTime = 0.0
		self.averagedPosition = Vector2()
		self.impactSoundVolume = 0.0
		self.progressMaterial = None
		self.insideRotationNode = None
		self.draggedInsideItems = []
		self.draggingParent = None
		self.sold = False
		self.lastVelocity = Vector2.ZERO
		self.lastCollisionPos = Vector2.ZERO
		self.lastCollider = None
		self.impactSoundReadyTime = 0.0
		self.globalAffectVisuals = []
		self.bondedBaseItem = None
		self.bondedIngredients = []
		self.locked = False
		self.bound = False
		self.curRecipe = None
		self.bondVisuals = []
		self.craftingLabel = None
		self.craftingAniReadyTime = 0.0
		self.pooled = False
		self.initialized = False
		self.canAffectVisuals = []
		self.rotationMomentum = 0
		self.bonusRotation = 0
		self.brightColor = Color(1.3, 1.3, 1.3, 1)
		self.defaultColor = Color.white
		self.buildIntoRecipesTooltip = None
		self.owningBuildIntoRecipesTooltip = None
		self.ownerTypesWithBuildTooltip = { _H_5: True, _H_6: True, _H_7: True, _H_8: True, _H_9: True }
		self.shaderTween = None
		self.canCancelShaderTween = True
		self.nonRotatedProgress = 0.0
		self.fusing = False
		self.willBeConsumed = False
		self.fuseParticles1 = None
		self.fuseParticles2 = None
		self.fuseTween = None
		self.fusingBonds = []
		self.collisionMap = None
		self.animation = None
		self.sprite = None
		self.clickArea = None
		self.dragParticles = None
		self.sockets = []
		self.lock = None
		self.lockAnimation = None
		self.baseBounce = 0.0
		self.baseFriction = 0.0

	@property
	def pickupFaceDirection(self):
		return self._pickupFaceDirection
	@pickupFaceDirection.setter
	def pickupFaceDirection(self, v):
		self._pickupFaceDirection = int(v)
	@property
	def dropFrame(self):
		return self._dropFrame
	@dropFrame.setter
	def dropFrame(self, v):
		self._dropFrame = int(v)
	@property
	def pickupFrame(self):
		return self._pickupFrame
	@pickupFrame.setter
	def pickupFrame(self, v):
		self._pickupFrame = int(v)
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
	affectedColorToTileId = {
		_R.C("CoreConst").Affected.Primary: Tiles.Affected, 
		_R.C("CoreConst").Affected.Secondary: Tiles.AffectedSecondary, 
		_R.C("CoreConst").Affected.Tertiary: Tiles.AffectedTertiary, 
		_R.C("CoreConst").Affected.Lightning: Tiles.AffectedLightning
	}
	rarityColors = [
		Color(0.460205, 0.874887, 0.90625), 
		Color(0.0737, 0.337874, 0.898438), 
		Color(0.828125, 0, 1), 
		Color(1, 0.609375, 0), 
		Color(0.980469, 0.946239, 0.582153), 
		Color(0.094223, 0.964844, 0.250663)
	]
	offset = 40
	impulse = 50
	momentumFactor = 20.0
	affectedSoundsVolume = {
		_R.C("CoreConst").Affected.Primary: - 8, 
		_R.C("CoreConst").Affected.Secondary: - 1, 
		_R.C("CoreConst").Affected.Tertiary: - 1, 
		_R.C("CoreConst").Affected.Lightning: - 1}
	cellSize = Vector2(80, 80)
	halfCellSize = 0.5 * cellSize
	shadowOffset_shop = Vector2(5, 1)
	shadowOffset_dropped = Vector2(5, 5)
	shadowOffset_dragged = Vector2(15, 15)
	DRAG_PRIORITY = 2
	# ★ np24：crafted 实例真值（语料 lineups snapshot；-1=未注入→退回类型级）。
	#   run871 定谳：实例 crafted ≠ 配方图（7 件无配方 crafted / 7 件有配方未
	#   crafted）——Anvil.onPreCombatStart 的 numCrafted 计数差根因。
	# ★ np25棋盘面重建回植：本适配层由 builder 从 decompiled Item.gd 再生，
	#   builder 无此手补 → 重建会冲掉（chessfix 重建实测），宿主 place_one
	#   的 it.crafted_instance 注入会 Invalid set index → 全场 assembly-fail。
	correction = [
		Vector2.ZERO, 
		Vector2( - cellSize.x, 0), 
		Vector2( - cellSize.x, - cellSize.y), 
		Vector2(0, - cellSize.y)
	]
	angleStep = 45
	moveRotationMouseFactor = 0.015
	backforce = 5.0
	fric = 15.0
	maxAngle = 10
	moveRotationSpeed = 60.0
	hoverableWhenMenuOpen = {
		_R.C("CoreConst").Owner.ItemLibrary: True, 
		_R.C("CoreConst").Owner.InfoPanelIcon: True, 
		_R.C("CoreConst").Owner.Tooltip: True, 
		_R.C("CoreConst").Owner.RecipeBook: True
	}
	MISS_OFFSET = 100.0
	PRE_FUSE_DUR = 1.0
	PRE_FUSE_DUR_COG = 0.2
	FUSE_DUR = 1.0
	TRANSFORMATION_DUR = 1.0
	labelOffsets = [Vector2.ZERO, Vector2(30, 30), Vector2( - 30, 30),
		Vector2(30, - 30), Vector2( - 30, - 30)]

	def _readyInit(self):
		super()._readyInit()
		self.hasPreDealDamageEarlyEffect = self.has_method("onPreDealDamage_early")
		self.hasPreDealDamageLateEffect = self.has_method("onPreDealDamage_late")
		self.hasDealtDamageEffect = self.has_method("onDealtDamage")
		self.hasOnChargeReceivedEffect = self.has_method("onChargeReceived")
		self.hasOnChargeLeftEffect = self.has_method("onChargeLeft")

	@staticmethod
	def getNumTooltipStats():
		return len(_H_2)


	@staticmethod
	def getNumStackChangeTypes():
		return len(_H_1)









	def preset(self):
		pass



	def initPhysicsMaterial(self):
		pass

	def getShadowOffset(self):
		if self.ownerType == _H_10:
			return self.shadowOffset_shop
		else:
			return self.shadowOffset_dropped





	def initRecipeBook(self):
		pass

	def initItemLibrary(self):
		pass

	def setSpotlight(self, _spotlight):
		self.hoverEnd()
		if self.spotlight:
			self.respondToHover()
		else:
			self.respondToHoverEnd()


	def initTitle(self):
		pass

	def initTooltip(self):
		pass

	def initBuildViewer(self):
		pass

	def initBuildViewerIcon(self):
		pass

	def initInfoPanelIcon(self):
		pass

	def initGridStorageIcon(self):
		self.initBuildViewerIcon()



	def getData(self):
		return None


	def setData(self, _data):
		pass



	def persistDataInShop(self):
		return False









	def getTranslatedName(self, removeLinebreaks=False):
		if removeLinebreaks:
			return self.descriptor.getTranslatedName().replace("\n", "")
		else:
			return self.descriptor.getTranslatedName()


	def getDescription(self, wrapInColor=True):
		descr = self.descriptor.getDescription()
		if self.descriptor.requiredItem != None:
			requiredStr = self.ctx.util.tra("TOOLTIP_Requires").format({
				"itemName": self.descriptor.requiredItem.getTranslatedName()
				})
			if descr.startswith("$t"):
				descr = requiredStr + descr
			else:
				descr = _strv(requiredStr, "\n\n", descr)

		return self.insertParameters(descr, wrapInColor)


	def insertParameters(self, descr, wrapInColor=True):
		_iter__loc = _iter
		if self.getBaseMinDamage() > 0 and wrapInColor:
			descr = descr.replace("$dam", self.ctx.util.wrapInColor_fixed(str(self.descriptor.minDam), self.ctx.util.paramColor))

		for i in _iter__loc(len(self.descriptor.extraCds) + 1):
			descr = self.insertParameter(descr, _strv("cd", i + 1), self.getModifiedCooldownIndex(i), 
				self.isCooldownModified(), True, wrapInColor)

		descr = self.insertParameter(descr, "cd", self.getModifiedCooldown(), self.isCooldownModified(), True, wrapInColor)
		descr = self.insertParameter(descr, "chance2", self.getChance2(), self.isChance2Modified(), True, wrapInColor)
		descr = self.insertParameter(descr, "chance", self.getChance(), self.isChance1Modified(), True, wrapInColor)
		descr = self.insertParameter(descr, "shopchance", self.getShopChance(), _H_11, True, wrapInColor)
		descr = self.insertParameter(descr, "stamina", self.getStaminaCost(), self.isStaminaModified(), True, wrapInColor)
		for i in _iter__loc(len(self.descriptor.params)):
			descr = self.insertParameter(descr, "p" + String(i + 1), self.getP(i), _H_11, True, wrapInColor)
		for paramName in (self.descriptor.sortedParamNames if self.descriptor.sortedParamNames.__class__ is list else _iter__loc(self.descriptor.sortedParamNames)):
			descr = self.insertParameter(descr, "p_" + paramName, self.getP(paramName), _H_11, True, wrapInColor)

		if wrapInColor:
			descr = descr.replace("$block", self.ctx.util.wrapInColor_fixed(String(self.getBlock()), self.ctx.util.paramColor))


		return descr


	def insertParameter(self, descr, paramName, value, modified=GD_DEFAULT, checkZero=True, wrapInColor=True):
		if modified is GD_DEFAULT:
			modified = _H_11
		value = stepify(value, 0.01)
		if value != 0 or not checkZero:
			replacedString = "$" + paramName
			startPos = _find(descr, replacedString)
			if startPos != - 1:
				refEndPos = self.ctx.util.findHighlightEnd(descr, startPos + 1)
				unit = _substr(descr, startPos + len(replacedString), refEndPos - (startPos + 1) - len(paramName))

				replacement = String(value) + unit
				if startPos > 0:
					if descr[startPos - 1] == "+":
						replacedString = "+" + replacedString
						replacement = "+" + replacement
					elif descr[startPos - 1] == "-":
						replacedString = "-" + replacedString
						replacement = "-" + replacement

				if wrapInColor:
					replacement = self.ctx.util.wrapInColor_fixed(replacement, self.ctx.util.statColors[modified])

				descr = descr.replace(replacedString + unit, replacement)

		return descr




	def getModeDescription(self, text, colors, center=True, wrapInColor=True):
		pass

	def getFlavorText(self):
		return self.descriptor.getFlavorText()


	def disablePicking(self):
		pass


	def enablePicking(self):
		pass


	def enableTooltip(self):
		pass


	def disableTooltip(self):
		pass


	def disableFocus(self):

		if self.focus:
			self.loseFocus()


	def enableFocus(self):
		pass


	def setEditMode(self, active):
		pass

	def setShadowAlpha(self, alpha):
		pass

	def getTopLeftGlobal(self):
		return Vector2.ZERO

	def getBottomRightGlobal(self):
		return Vector2.ZERO

	def getBottomCenter(self):
		return Vector2.ZERO

	def getInventory(self):
		if self.placed:
			return self.inventory
		else:
			return None


	@staticmethod
	def wasAddedToInventory(dropRes):
		return dropRes == Item_2.DropResult.AddedToInventory or dropRes == Item_2.DropResult.Hotswap



	@staticmethod
	def wasBought(dropRes):
		return (Item_2.wasAddedToInventory(dropRes) or 
				dropRes == Item_2.DropResult.AddedToStorageBox or 
				dropRes == Item_2.DropResult.Socketed or 
				dropRes == Item_2.DropResult.SocketHotswap)


	@staticmethod
	def wasHotSwap(dropRes):
		return dropRes == Item_2.DropResult.Hotswap or dropRes == Item_2.DropResult.SocketHotswap


	def removeFromInventory(self):
		pass

	def playAffectedPlacedAnimation(self, newItemIsAffected):
		sum = 0
		for color in (newItemIsAffected if newItemIsAffected.__class__ is list else _iter(newItemIsAffected)):
			sum += int(newItemIsAffected[color])

		if sum > 1:
			pass
		elif newItemIsAffected[_H_13]:
			pass
		elif newItemIsAffected[_H_19]:
			pass
		elif newItemIsAffected[_H_20]:
			pass
		elif newItemIsAffected[_H_22]:
			pass





	def clearCanAffectVisuals(self):
		pass




	def liesInStorage(self):
		return self.ownerType == _H_6 and not self.dragged


	def pushToStorage(self, targetPos=None):
		pass

	def addToStorageBox(self, addImpulse=True, tweenBouncyness=True, checkCollisions=True, targetPos=None, speed=1.0, secondCheck=False):
		pass

	def removeFromStorage(self):

		self.killMovebackTween()
		self.onStorageLeft()


	def onStorageLeft(self):
		pass

	def isInGridStorage(self):
		return False

	def getGridStorageProxy(self):
		pass

	def onAddedToGridStorage(self):
		pass

	def onRemovedFromGridStorage(self):
		pass

	def makeGrabbable(self, extended):
		pass

	def moveToFreeSpaceInStorage(self, targetPos=None, addImpulse=False, speed=1.0, secondCheck=False, tweenBouncyness=True):
		pass

	def checkIfOutofStorageBounds(self):
		self.ctx.util.callNextFrame(self, "checkIfOutofStorageBounds2")


	def checkIfOutofStorageBounds2(self):
		self.ctx.util.callNextFrame(self, "checkIfOutofStorageBounds3")


	def checkIfOutofStorageBounds3(self):
		pass

	def findFreeSpace(self, startPos):
		return Vector2.ZERO

	def unclip(self):
		pass

	def onAddedToStorageBox(self):
		pass


	def _process(self, delta):
		pass

	def _integrate_forces(self, state):
		if state.get_contact_count() > 0:
			pass
		else:
			pass


	def updateShadow(self):
		pass

	def lerpAngle_local(self, interpolationPoint, from_, to):
		self.updateInsideRotationNode()
		self.updateShadow()


	def updateInsideRotationNode(self):
		if self.insideRotationNode != None:
			pass


	def spawnRotationSparks(self, rotateRight):
		pass

	def highlight(self):
		pass


	def unhighlight(self):
		self.resetSprite()


	def setBright(self):
		pass

	def resetBright(self):
		pass

	def getHoverPriority(self):
		if self.dragged:
			return self.DRAG_PRIORITY
		else:
			return 0


	def canGainFocus(self):
		pass

	def gainFocus(self):
		if not self.canGainFocus():
			return


		if (self.ownerType == _H_7 or 
			self.ownerType == _H_14 or 
			self.ownerType == _H_8):
			self.ctx.combat_log.highlightItem(self, False)


		self.respondToHover()


	def respondToHover(self):
		pass

	def canShowBuildIntoRecipesTooltip(self):
		if self.dragged:
			return False

		effectiveOwner = self.getEffectiveOwnerType()

		if self.ownerType == _H_15 and self.owningBuildIntoRecipesTooltip != None:
			if not self.canShowSubBuildIntoRecipesTooltip():
				return False
		elif not (self.ownerType == _H_10 or 
				self.ownerType == _H_21 or 
				effectiveOwner in self.ownerTypesWithBuildTooltip):
			return False

		descr = self.getRecipeDescriptor()
		if descr.getNumRecipes() > 0:
			return True

		if len(self.getRelatedItems()) > 0:
			return True

		return False


	def canShowSubBuildIntoRecipesTooltip(self):
		pass

	def showBuildIntoRecipesTooltip(self):
		pass

	def getRelatedItemColumns(self):
		return 5


	def getRelatedItemHeight(self):
		return 150


	def getRecipeDescriptor(self):
		return self.descriptor



	def hideBuildIntoRecipesTooltip(self):
		if self.buildIntoRecipesTooltip != None:
			pass


	def loseFocus(self):
		if self.dragged:
			return

		if not self.focus:
			return



		self.respondToHoverEnd()


	def respondToHoverEnd(self):
		pass

	def activateDragParticles(self):
		for specificParticles in (self.specificDragParticles if self.specificDragParticles.__class__ is list else _iter(self.specificDragParticles)):
			specificParticles.activate()


	def deactivateDragParticles(self):
		for specificParticles in (self.specificDragParticles if self.specificDragParticles.__class__ is list else _iter(self.specificDragParticles)):
			specificParticles.deactivate()



	def updateTooltip(self):
		pass


	def queueTooltipUpdate(self):
		pass

	def clearTooltip(self):

		self.hideBuildIntoRecipesTooltip()
		self.clearCanAffectVisuals()


	def mouseEntered(self):
		pass

	def hover(self):
		pass

	def mouseExited(self):
		pass

	def hoverEnd(self):
		pass

	def isHovered(self):
		return self.hovered or self.dragged


	def getScaleProp(self):
		if self.hasSquishySprite:
			return "baseScale"
		else:
			return "scale"


	def setSpriteScale(self, newScale):
		if self.hasSquishySprite:
			pass


	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		pass

	def onDraggedWithParentStart(self, parentItem):
		self.finishMoveback()


	def finishMoveback(self):
		pass

	def onDraggedWithParentEnd(self):
		pass


	def canSnap(self):
		return (not self.draggedInsideItems) and self.draggingParent == None


	def reactToDropResult(self, result):
		pass

	def drop(self):
		return 0

	def showClickArea(self):
		pass


	def cancelDrag(self):
		pass

	def emptyTweenCallback(self):
		pass


	def killMovebackTween(self):
		self.showClickArea()


	def setSpriteGlobalPos(self, pos):
		self.updateShadow()


	def dropIntoInventory(self, hotswap):
		pass

	def finishInsideItemsRotation(self):
		pass

	def pushDraggedItemsToStorage(self):
		for item in (self.draggedInsideItems if self.draggedInsideItems.__class__ is list else _iter(self.draggedInsideItems)):
			item.pushToStorage()
		self.correctInsideItemFacedirection()
		self.clearDraggedInsideItems()



	def reparentItemsInside(self):
		for item in (self.draggedInsideItems if self.draggedInsideItems.__class__ is list else _iter(self.draggedInsideItems)):
			pass
		self.correctInsideItemFacedirection()
		self.clearDraggedInsideItems()


	def clearDraggedInsideItems(self):
		for item in (self.draggedInsideItems if self.draggedInsideItems.__class__ is list else _iter(self.draggedInsideItems)):
			item.onDraggedWithParentEnd()


	def showSockets(self):
		pass

	def hideSockets(self):
		pass

	def playPickupSound(self):
		pass

	def canBeSold(self):
		return (self.ownerType == _H_7 or 
			self.ownerType == _H_6 or 
			self.ownerType == _H_14)


	def isPickingPossible(self):
		return False

	def canBePicked(self):
		return self.focus and self.isPickingPossible() and self.ctx.frame_counter > self.dropFrame


	def canBeDraggedWithBag(self):
		return False

	def canBeDropped(self):
		return self.dragged and self.ctx.frame_counter > self.pickupFrame


	def _input(self, event):
		pass

	def resetSprite(self):
		pass

	def combatToShop(self):
		if self.isOwnedByOpponent():
			self.disableTooltip()
		else:
			self.resetSprite()
			self.cachedAffectedItems.clear()


	def shopEntered(self, craft):
		_iter__loc = _iter
		_fill__loc = _fill
		self.baseCooldownOverride = self.descriptor.cd
		self.speedScale = 0.0
		self.bonusMinDam = 0
		self.bonusMaxDam = 0
		self.removableDam = 0
		self.bonusDamageFactor = 1.0
		self.staminaFactor = 1.0
		for buff in (self.buffPowers if self.buffPowers.__class__ is list else _iter__loc(self.buffPowers)):
			self.buffPowers[buff] = 1.0
			self.buffAmplificationChances[buff] = 0.0

		self.critChancePercent = 0.0
		self.critTokens = 0
		self.critSeverity = self.BASE_CRIT_SEVERITY
		self.bonusChancePercent_mult = 0.0
		self.bonusChancePercent_additive1 = 0.0
		self.bonusChancePercent_additive2 = 0.0
		self.bonusAccuracy = 0.0
		self.doubleActivationChance = 0.0
		self.doubleAttackEffectChance = 0.0
		self.paramMult.clear()
		self.paramAdd.clear()
		self.numCharges = 0
		_fill__loc(self.statDisplayOverrides, None)
		_fill__loc(self.itemMetrics, 0)
		self.consumed = False
		self.showCooldownSmooth(0)


		self.enablePicking()
		for gem in _iter__loc(self.getGemsNoNull()):
			gem.shopEntered(craft)

		if craft:
			self.addToCraftingQueue()

		self.onShopEntered()


	def onShopEntered(self):
		pass


	def startFusing_inShop(self):
		self.startFusing(self.PRE_FUSE_DUR_COG)


	def getCraftingPriority(self):
		if self.isGem():
			return _H_12

		for bonded in (self.bondedIngredients if self.bondedIngredients.__class__ is list else _iter(self.bondedIngredients)):
			if bonded.isGem():
				return _H_16

		return _H_3


	def addToCraftingQueue(self):
		pass

	def combatToTitle(self):
		if self.isOwnedByOpponent():
			self.disableTooltip()


	def readyToFuse(self):
		return self.curRecipe and self.curRecipe.getProgress(self.bondedIngredients) == 1


	def startFusing(self, delay=GD_DEFAULT):
		if delay is GD_DEFAULT:
			delay = self.PRE_FUSE_DUR
		if self.readyToFuse():
			self.ctx.util.callDelayed(self, "fuse", delay)
			self.disablePicking()
			for bonded in (self.bondedIngredients if self.bondedIngredients.__class__ is list else _iter(self.bondedIngredients)):
				if self.curRecipe == None or not self.curRecipe.isNeighborCatalyst(bonded):
					self.ctx.defer(bonded, "disablePicking", [])
					bonded.willBeConsumed = True


	def readyToTransform(self):
		return False


	def giveGold(self, amount):
		amount = int(amount)
		pass

	def getTranslatedTypeName(self, type):
		return self.descriptor.getTranslatedTypeName(type)


	def getTypeDescription(self, type):
		return self.ctx.util.tra("TYPE_" + list(_H_23.keys())[type] + "_DESCR")


	def getTranslatedRarity(self):
		return self.getRarityName(self.getRarity())


	@staticmethod
	def getRarityName(_rarity):
		_rarity = int(_rarity)
		return ""

	def logCooldown(self):
		return self.hasCooldown()


	def getCombatDisplayAccuracy(self):
		acc = self.getAccuracy()
		if acc > 100:
			return ">100"
		elif acc < 0:
			return "<0"
		else:
			return String(acc)


	def getDisplayCritChance(self):
		c = self.getCritChancePercent()
		if c > 100:
			return ">100"


		else:
			return String(stepify(c, 0.1))



	def getSalesMultiplier(self):
		return 1.0


	def prepareDiscard(self):
		pass

	def discard(self, discardGems=True):
		pass

	def popIn(self, withParticles=True, speed=1.0, jump=False):
		pass

	def disappear(self):
		pass



	def appearInLibrary(self):
		pass

	def createParticles(self, scene, baseScale=GD_DEFAULT):
		if baseScale is GD_DEFAULT:
			baseScale = Vector2.ONE
		pass

	def deactivateParticles(self):
		pass

	def makeRigidBody(self):
		pass

	def dropImpulse(self, direction=None, tweenBouncyness=True):
		pass

	def makeNonRigidBody(self):
		pass

	def rollShopChance(self, shopChance=GD_DEFAULT):
		if shopChance is GD_DEFAULT:
			shopChance = self.descriptor.shopChance
		return False

	def _physics_process(self, delta):
		if not (self.character().stunnedDuration > 0):
			self.triggerTime -= delta * self.getSpeed()
			self.showCooldown(1.0 - _div(self.triggerTime, self.iterationCooldown))
			if self.triggerTime <= 0:
				self.trigger()





	def playActivationAnimation_Scale(self, maxScale):
		pass


	def playActivationAnimation_Jump(self, height, maxScale=1.0):
		pass




	def playActivationAnimation_JumpSquash(self, height, intensity=0.2):

		longScale = 1.0 + intensity
		shortScale = _div(1.0, longScale)
		scaling = None
		if self.faceDirection == _H_17 or self.faceDirection == _H_18:
			scaling = Vector2(shortScale, longScale)
		else:
			scaling = Vector2(longScale, shortScale)




	def playActivationAnimation(self, aniType=GD_DEFAULT, consume=False):
		if aniType is GD_DEFAULT:
			aniType = self.descriptor.activationAni

		self.resetSprite()

		if aniType == self.ActivationAni.Jump:
			self.playActivationAnimation_Jump(40)

		elif aniType == self.ActivationAni.SquishyJump:
			self.playActivationAnimation_JumpSquash(40, 0.1)

		elif aniType == self.ActivationAni.VerySquishyJump:
			self.playActivationAnimation_JumpSquash(40, 0.2)

		elif aniType == self.ActivationAni.Slash:
			pass

		elif aniType == self.ActivationAni.Stab:
			pass

		elif aniType == self.ActivationAni.ReverseStab:
			pass

		elif aniType == self.ActivationAni.Bonk:
			pass

		elif aniType == self.ActivationAni.ReverseBonk:
			pass

		elif aniType == self.ActivationAni.Sweep:
			pass

		elif aniType == self.ActivationAni.Block:
			self.playActivationAnimation_Jump(30, 1.3)

		elif aniType == self.ActivationAni.Chop:
			pass

		elif aniType == self.ActivationAni.Wave:
			pass

		elif aniType == self.ActivationAni.Throw:
			pass

		elif aniType == self.ActivationAni.Scale:
			self.playActivationAnimation_Scale(1.5)

		elif aniType == self.ActivationAni.Squish:

			if self.hasSquishySprite:
				pass
			else:
				pass

		elif aniType == self.ActivationAni.Potion:
			pass

		elif aniType == self.ActivationAni.Hiss:
			pass

		elif aniType == self.ActivationAni.Spin:
			pass

		elif aniType == self.ActivationAni.Tackle:
			pass

		elif aniType == self.ActivationAni.DoubleSlash:
			pass

		elif aniType == self.ActivationAni.Struggle:
			self.playActivationAnimation_Jump(30)

		elif aniType == self.ActivationAni.Shoot:
			pass

		elif aniType == self.ActivationAni.Flash:
			pass

		if consume:
			pass


	def playActivationSound(self):
		self.playDropSound( - 6)


	def clearSpriteMaterial(self):
		pass


	def giveProgressMaterial(self):
		pass


	def getTextureSize(self):
		return Vector2.ZERO

	def scaleToFit(self, maxSize, maxScale):
		pass

	def getSpriteOffset(self):
		return Vector2.ZERO

	def getGlobalCenter(self):
		return Vector2.ZERO

	def getTextureSize_local(self):
		return Vector2.ZERO

	def scaleToFit_local(self, maxSize, maxScale):
		pass

	def getSpriteOffset_local(self):
		return Vector2.ZERO

	def setTexture(self, newTex):
		self.initSpriteMaterial()


	def updateShadowTexture(self):
		pass


	def initSpriteMaterial(self):
		pass




	def updateShaderRotation(self):
		pass

	def allowCancelShaderTween(self):
		pass


	def showCooldownSmooth(self, progress, fill=False):
		if not self.canCancelShaderTween:
			return


		if fill:
			pass
		else:
			pass


	def showCooldown(self, progress):
		pass

	def createAnimation(self):
		pass

	def playAnimation(self, hit=True):
		if not self.descriptor.animationScene:
			return



	def hasInventoryDuration(self):
		return self.descriptor.hasParam("dur")


	def reveal(self):
		pass


	def setRevealed(self):
		self.reveal()


	def isCrafted(self):
		# ★ np24 实例真值优先（crafted_instance≥0=宿主已注入），-1 退回类型级。
		#   np25棋盘面重建回植（同 crafted_instance，builder 再生会冲掉）。
		if self.crafted_instance >= 0:
			return self.crafted_instance == 1
		return self.descriptor.isCraftedItem()


	def isMovingBack(self):
		return False

	def _notification(self, what):
		what = int(what)
		pass

	def getAllInInventoryOfType(self, descr):
		if self.isOwnedByOpponent():
			return self.ctx.item_book.getItemsInInventoryOfType_opponent(descr)
		else:
			return self.ctx.item_book.getItemsInInventoryOfType(descr)


	def countAllInInventoryOfType(self, descr):
		if self.isOwnedByOpponent():
			return self.ctx.item_book.countItemsInInventoryOfType_opponent(descr)
		else:
			return self.ctx.item_book.countItemsInInventoryOfType(descr)


	def isTypeInInventory(self, descr):
		if self.isOwnedByOpponent():
			return self.ctx.item_book.isItemInInventory_opponent(descr)
		else:
			return self.ctx.item_book.isItemInInventory(descr)




	def isRecipeFinished(self):
		return self.curRecipe.getProgress(self.bondedIngredients) == 1


	def canStartNewRecipe(self):
		return not self.isBaseItem() and self.isAvailableForCrafting()


	def getRecipes(self, checkClassAvailability=True):
		recipes = []
		for recipe in (self.descriptor.recipes if self.descriptor.recipes.__class__ is list else _iter(self.descriptor.recipes)):

			recipes.append(recipe)
		return recipes



	def breakBondVisual(self, toItem):
		bondIndex = _find(self.bondedIngredients, toItem)
		if bondIndex != - 1:
			pass



	def removeBondedBaseItem(self):
		self.setBoundAsIngredient(False)


	def removeBondedIngredient(self, item):

		self.breakBondVisual(item)


		if self.fusing:
			return

		self.showProgressLabel()

		if (not self.bondedIngredients):
			pass

		else:
			self.updateBondVisuals()


	def removeAllIngredients(self):



		self.showProgressLabel()












	def considerAsBond(self, neighbor):
		_div__loc = _div
		score = 0.0
		recipe = None
		if self.curRecipe:
			if self.isRecipeFinished():
				return None

			if self.curRecipe.checkNeighbor(self.bondedIngredients, neighbor):
				progressBefore = self.curRecipe.getProgress(self.bondedIngredients)
				progressWithNeighbor = _div__loc(len(self.bondedIngredients) + 1, float(self.curRecipe.getNumIngredients()))
				score = progressWithNeighbor + 0.1 * progressBefore
				recipe = self.curRecipe
		else:
			bestScore = 0.0
			for r in _iter(self.getRecipes()):
				if r.checkNeighbor([], neighbor):
					s = _div__loc(1.0, r.getNumIngredients())
					if s > bestScore:
						bestScore = s
						recipe = r

			score = bestScore

		if recipe:
			return [recipe, score]
		else:
			return None


	def addBondedIngredient(self, forRecipe, neighbor):
		if self.curRecipe:

			pass
		else:
			pass

		self.createBondVisual(neighbor)
		self.updateBondVisuals()
		self.playBondAnimation()

		if neighbor.placedByPlayer or self.placedByPlayer:
			self.showProgressLabel()


	def addToBaseItem(self, baseItem):
		self.setBoundAsIngredient(True)
		self.playBondAnimation()


	def playBondAnimation(self):

		catalyst = False
		if self.bondedBaseItem != None:
			if self.bondedBaseItem.curRecipe != None:
				catalyst = self.bondedBaseItem.curRecipe.isCatalystRecipe()
		else:
			if self.curRecipe != None:
				catalyst = self.curRecipe.isCatalystRecipe()

		if catalyst:
			pass
		else:
			pass


	def playBondFailedAnimation(self):
		pass


	def isCatalystBond(self, bondedItem):
		if self.curRecipe == None:
			return False

		return self.curRecipe.isNeighborCatalyst(bondedItem)


	def isLocked(self):
		return self.locked


	def canLockBag(self):
		return False


	def canBeLocked(self):
		return False

	def setLocked(self, _locked, showLabel=True):

		if self.locked == _locked:
			return

		if _locked:
			self.lockCombining(showLabel)
		else:
			self.unlockCombining()


	def unlockCombining(self, playAni=True):
		pass

	def lockCombining(self, showLabel=True):
		pass

	def showLockLabel(self):
		pass

	def getLockPosition(self):
		return Vector2.ZERO

	def setBoundAsIngredient(self, _bound):
		pass



	def canPreviewFusions(self):
		pass

	def getCraftingPreviewPosition(self):
		pass

	def previewFusions(self):
		pass

	def previewRecipeIngredients(self):
		pass

	def previewFusionToItem(self, hoveredIngredient):
		pass

	def hasShopItemCraftCandidates(self):
		return False

	def typeInIngredients(self, candidate, ingredients):
		for ingredient in (ingredients if ingredients.__class__ is list else _iter(ingredients)):
			if candidate.hasType(ingredient):
				return True
		return False


	def getTextEffect(self):
		return self.descriptor.textEffect


	def getFusionItemName(self):
		return self.curRecipe.fusedItem.getTranslatedName()


	def showProgressLabel(self):
		pass

	def onCraftingLabelReturned(self):
		pass


	def createBondVisual(self, bondNeighbor):
		pass

	def updateBondVisuals(self):
		pass

	def fuse(self):
		pass

	def onFusingAsIngredient(self):
		pass


	def onFusingAsCatalystFinished(self):
		self.clearSpriteMaterial()
		self.setBoundAsIngredient(False)


	def createCraftedShockwave(self, fusedItem):
		pass

	def finishFusing(self):
		pass

	def allowGeneratingFusionItem(self):
		return True


	def catalystFusingFinished(self):
		pass

	def onFusingFinished(self, validBonds):
		pass

	def onCraftedFrom(self, baseItem, ingredients):
		pass


	def getCraftingOffset(self, _forDirection):
		return Vector2.ZERO



	def playCraftedAnimation(self, originPosition):
		pass

	def onRestoreSnapshot(self):
		self.finishMoveback()


	def getShopPriority(self):
		return _H_4




	SignalConnection = SignalConnection


_R.reg("res://gd_core_items/Item.gd", Item_2)
_R.reg("Item", Item_2)
_R.reg("Item", Item_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StackChangeType
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_10 = _R.C("CoreConst").Owner.Shop
except AttributeError as _he:
	_H_10 = _HoistPending(_he)
try:
	_H_11 = _R.C("CoreConst").StatModified.No
except AttributeError as _he:
	_H_11 = _HoistPending(_he)
try:
	_H_12 = _R.C("CoreConst").CraftingPriority.Gem
except AttributeError as _he:
	_H_12 = _HoistPending(_he)
try:
	_H_13 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_13 = _HoistPending(_he)
try:
	_H_14 = _R.C("CoreConst").Owner.Socket
except AttributeError as _he:
	_H_14 = _HoistPending(_he)
try:
	_H_15 = _R.C("CoreConst").Owner.Tooltip
except AttributeError as _he:
	_H_15 = _HoistPending(_he)
try:
	_H_16 = _R.C("CoreConst").CraftingPriority.Mixed
except AttributeError as _he:
	_H_16 = _HoistPending(_he)
try:
	_H_17 = _R.C("CoreConst").FaceDirection.UP
except AttributeError as _he:
	_H_17 = _HoistPending(_he)
try:
	_H_18 = _R.C("CoreConst").FaceDirection.DOWN
except AttributeError as _he:
	_H_18 = _HoistPending(_he)
try:
	_H_19 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_19 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").ItemStat
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_20 = _R.C("CoreConst").Affected.Tertiary
except AttributeError as _he:
	_H_20 = _HoistPending(_he)
try:
	_H_21 = _R.C("CoreConst").Owner.ItemLibrary
except AttributeError as _he:
	_H_21 = _HoistPending(_he)
try:
	_H_22 = _R.C("CoreConst").Affected.Lightning
except AttributeError as _he:
	_H_22 = _HoistPending(_he)
try:
	_H_23 = _R.C("CoreConst").Type
except AttributeError as _he:
	_H_23 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").CraftingPriority.NonGem
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreConst").Priority.Normal
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreConst").Owner.BuildViewer
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
try:
	_H_6 = _R.C("CoreConst").Owner.PlayerStorageBox
except AttributeError as _he:
	_H_6 = _HoistPending(_he)
try:
	_H_7 = _R.C("CoreConst").Owner.PlayerInventory
except AttributeError as _he:
	_H_7 = _HoistPending(_he)
try:
	_H_8 = _R.C("CoreConst").Owner.Opponent
except AttributeError as _he:
	_H_8 = _HoistPending(_he)
try:
	_H_9 = _R.C("CoreConst").Owner.GridStorage
except AttributeError as _he:
	_H_9 = _HoistPending(_he)
