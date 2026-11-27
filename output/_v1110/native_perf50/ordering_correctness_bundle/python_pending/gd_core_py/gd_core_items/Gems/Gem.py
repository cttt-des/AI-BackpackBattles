# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import (  # noqa: F401

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
	from ..._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from ... import _registry as _R
if "_base_cls_Gem" not in globals():
	from ..Item import Item_2 as _base_cls_Gem





class Gem(_base_cls_Gem):

	resource_path = "res://gd_core_items/Gems/Gem.gd"

	GemMode = EnumDict("GemMode", {"Weapon": 0, "Armor": 1, "Inventory": 2, "Inactive": 3})



	def _init_fields(self):
		super()._init_fields()
		self.hoveredSocket = None
		self.socket = None
		self.movebackSocket = None
		self.dropTween = None
		self.gemPower = 1.0
		self.dropPosition = None
		self.dropRotation = None
		self.quantizedRotation = None
		self.socketDetectionArea = None
		self.gemAnimation = None


	def isGem(self):
		return True


	def isOwnable(self):
		if self.socket != None:
			return self.socket.getItem().isOwnable()
		else:
			return super().isOwnable()


	def isOwnedByOpponent(self):
		if self.socket != None:
			return self.socket.getItem().isOwnedByOpponent()
		else:
			return super().isOwnedByOpponent()


	def getEffectiveOwnerType(self):
		if self.socket != None:
			return self.socket.getItem().getEffectiveOwnerType()
		else:
			return super().getEffectiveOwnerType()


	def getInventory(self):
		if self.socket != None:
			return self.socket.getItem().getInventory()
		else:
			return super().getInventory()


	def getItem(self):
		if self.socket != None:
			return self.socket.getItem()
		else:
			return None


	def isPlaced(self):
		if self.socket != None:
			return self.socket.getItem().isPlaced()
		else:
			return self.placed


	def isInInventory(self):
		if self.socket != None:
			return self.socket.getItem().isInInventory()
		else:
			return super().isInInventory()


	def getGemMode(self):
		if self.socket != None:
			if self.getItem().isWeapon():
				return self.GemMode.Weapon
			else:
				return self.GemMode.Armor
		else:
			if self.placed:
				return self.GemMode.Inventory
			else:
				return self.GemMode.Inactive


	def getGemPower(self):
		return max(0.0, self.gemPower)


	def changeGemPower(self, amount):
		self.gemPower += amount


	def getHoverPriority(self):
		if self.dragged:
			return self.DRAG_PRIORITY
		else:
			return 1


	def character(self):
		if self.getGemMode() == self.GemMode.Inactive:
			return self.ctx.player
		elif self.getGemMode() == self.GemMode.Inventory:
			return super().character()
		else:
			return self.getItem().character()


	def _process(self, _delta):
		pass

	def previewCellCollision(self):
		if ( not self.hoveredSocket and 
			( not self.movebackSocket or self.ctx.frame_counter > self.pickupFrame + 1)):
			super().previewCellCollision()


	def gainFocus(self):
		super().gainFocus()

	def loseFocus(self):
		super().loseFocus()

	def prepareLerpToSocket(self):
		pass

	def drop(self):
		return 0

	def lerpToSocket(self, interpolationPoint):
		pass

	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)


		if self.socket != None:
			self.killDropTween()
			self.movebackSocket = self.socket
			self.hoveredSocket = self.socket
			if self.socket.getItem().ownerType == _H_1:
				self.setFaceDirection(_H_2)
			else:
				self.faceDirection = self.getGlobalFaceDirection()

			self.socket.onPickupGem()


	def addToSocket(self, _socket):
		pass

	def unsocket(self):
		self.killDropTween()
		s = self.socket
		self.socket.onPickupGem()
		s.hideSocket()


	def removeFromSocket(self):
		pass

	def killDropTween(self):
		pass

	def returnToSocket(self, movebackDur=0.1):
		pass

	def hasCooldown(self):
		gemMode = self.getGemMode()
		return ((gemMode == self.GemMode.Inventory or 
					gemMode == self.GemMode.Inactive) and 
					super().hasCooldown())


	def miniActivate(self):
		super().miniActivate()
		self.playActivationAnimation_Scale(1.5)


	def prepareInventory(self):
		pass


	def prepareWeapon(self):
		pass


	def prepareArmor(self):
		pass


	def onPrepare(self):

		if self.getGemMode() == self.GemMode.Inventory:
				self.prepareInventory()
		elif self.getGemMode() == self.GemMode.Weapon:
				self.prepareWeapon()
		elif self.getGemMode() == self.GemMode.Armor:
				self.prepareArmor()


	def combatStartInventory(self):
		pass


	def combatStartWeapon(self):
		pass


	def combatStartArmor(self):
		pass


	def combatStart(self):
		super().combatStart()
		self.iterationCooldown = self.adjustCooldown()
		self.triggerTime = self.iterationCooldown

		if self.getGemMode() == self.GemMode.Inventory:
				self.combatStartInventory()
		elif self.getGemMode() == self.GemMode.Weapon:
				self.combatStartWeapon()
		elif self.getGemMode() == self.GemMode.Armor:
				self.combatStartArmor()


	def combatEndInventory(self):
		pass


	def combatEndWeapon(self):
		pass


	def combatEndArmor(self):
		pass


	def combatEnd(self):
		super().combatEnd()
		if self.getGemMode() == self.GemMode.Inventory:
				self.combatEndInventory()
		elif self.getGemMode() == self.GemMode.Weapon:
				self.combatEndWeapon()
		elif self.getGemMode() == self.GemMode.Armor:
				self.combatEndArmor()


	def shopEntered(self, craft):
		super().shopEntered(craft)
		self.gemPower = 1.0


	def getBaseDescription(self, wrapInColor=True):
		return super().getDescription(wrapInColor)


	def getDescription(self, wrapInColor=True):
		descr = self.getBaseDescription(wrapInColor)
		colors = [self.ctx.util.inactiveColor, self.ctx.util.inactiveColor, self.ctx.util.inactiveColor]
		gemMode = self.getGemMode()
		if gemMode != self.GemMode.Inactive:
			colors[gemMode] = self.ctx.util.modifiedColor
		return self.getModeDescription(descr, colors, True, wrapInColor)


	def onHotSwapHoverWithGem(self):
		pass


	def onHotSwapHoverWithGemEnd(self):
		pass


	def createGemParticles(self):
		pass


	def canPreviewFusions(self):
		if self.socket:
			return self.socket.getItem().canPreviewFusions()
		else:
			return super().canPreviewFusions()


	def canModifyChance(self):
		return False


	def getNeighborItemsAndGems(self):
		if self.socket:
			if self.getItem().ownerType == _H_1:
				return []



			neighbors = [self.getItem()]
			neighbors.extend(self.getItem().getNeighborItemsAndGems())
			_erase(neighbors, self)
			return neighbors
		else:
			return super().getNeighborItemsAndGems()


	def canCombine(self):
		if self.socket:
			return True
		else:
			return super().canCombine()


	def shift(self, direction):
		if not self.socket:
			super().shift(direction)


	def isMovingBack(self):
		return False

	def addToStorageBox(self, addImpulse=True, tweenBouncyness=True, checkCollisions=True, targetPos=None, speed=1.0, secondCheck=False):
		if self.socket:
			s = self.socket
			super().addToStorageBox(addImpulse, tweenBouncyness, 
				checkCollisions, targetPos, speed, secondCheck)
			s.onPickupGem()
			s.hideSocket()
		else:
			super().addToStorageBox(addImpulse, tweenBouncyness, 
				checkCollisions, targetPos, speed, secondCheck)


	def discard(self, discardGems=True):
		super().discard(discardGems)
		if self.socket != None:
			self.socket.gem = None
			self.socket.hideSocket()
			self.socket = None
			self.movebackSocket = None

	def _readyInit(self):
		super()._readyInit()
		if self.descriptor.gateItem == self.ctx.item_book.getDescriptor("Box of Riches"):
			if (not self.specificDragParticles):
				pass



_R.reg("res://gd_core_items/Gems/Gem.gd", Gem)
_R.reg("Gem", Gem)
_R.reg("Gem", Gem)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Owner.PlayerStorageBox
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").FaceDirection.UP
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
