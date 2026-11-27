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
if "_base_cls_Bag_2" not in globals():
	from .Item import Item_2 as _base_cls_Bag_2





class Bag_2(_base_cls_Bag_2):

	resource_path = "res://gd_core_items/Bag.gd"

	BagTiles = EnumDict("BagTiles", {"Default": 2, "CanAdd": 6, "CannotAdd": 5})



	def _init_fields(self):
		super()._init_fields()
		self.bagTilemapPosition = None
		self.cachedAffectedInsideItems = []
		self.cachedInsideItems = []
		self.bagTilemap = None
		self.border = None


	def getHoverPriority(self):
		if self.dragged:
			return self.DRAG_PRIORITY
		else:
			return - 1


	def isBag(self):
		return True


	def showBagBorderForItem(self, item):
		return not item.isBag() and self.canApplyEffect(item)


	def canApplyEffect(self, _toItem):
		return False


	def canBePicked(self):
		return False

	def canBeLocked(self):
		return False

	def resetZ(self):
		pass

	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		super().addToInventory(_inventory, _occupiedCells, _placedByPlayer)

	def getBagLayerPriority(self):
		if self.getRarity() == _H_1:
			return 2
		if self.hasBagEffect():
			return 1
		return 0


	def hasBagEffect(self):
		return self.border != None


	def _process(self, delta):
		if self.dragged:
			if self.ctx.player.INVENTORY.canAddBag(self):
				pass

			else:
				pass


	def reactToDropResult(self, result):
		super().reactToDropResult(result)

	def onRemoveFromInventory(self):
		pass


	def getTopLeftGlobal(self):
		return Vector2.ZERO

	def getBottomRightGlobal(self):
		return Vector2.ZERO

	def isEmpty(self):
		return (not self.getItemsInside())


	def getItemsInside(self):
		if not (not self.cachedInsideItems):
			return self.cachedInsideItems

		return self.inventory.getItemsInCells(self.occupiedCells)


	def getEmptyCells(self):
		emptyCells = []
		for cell in (self.occupiedCells if self.occupiedCells.__class__ is list else _iter(self.occupiedCells)):
			if self.inventory.isCellEmpty(cell):
				emptyCells.append(cell)
		return emptyCells


	def getEmptyGlobalPositions(self):
		positions = []
		for cell in _iter(self.getEmptyCells()):
			positions.append(self.inventory.cellToGlobalPos(cell, True))
		return positions


	def getAffectedItemsInside(self):
		if not self.placed:
			return []

		if not (not self.cachedAffectedInsideItems):
			return self.cachedAffectedInsideItems

		affected = []
		for item in _iter(self.getItemsInside()):
			if self.canApplyEffect(item):
				affected.append(item)

		return affected


	def previewCanAffect(self):
		pass

	def prepare(self):
		self.cachedInsideItems = self.getItemsInside()

		for item in (self.cachedInsideItems if self.cachedInsideItems.__class__ is list else _iter(self.cachedInsideItems)):
			if self.canApplyEffect(item):
				self.cachedAffectedInsideItems.append(item)

		super().prepare()


	def combatToShop(self):
		self.cachedAffectedInsideItems.clear()
		self.cachedInsideItems.clear()
		super().combatToShop()



	def getCraftableNeighbors(self):
		craftableItems = []
		for item in _iter(self.getItemsInside()):
			if item.isAvailableForCrafting():
				craftableItems.append(item)
		return craftableItems








	def onItemAdded(self, item):
		super().onItemAdded(item)
		if item in self.getItemsInside() and self.canApplyEffect(item):
			if item.placedByPlayer:
				pass
			self.onAffectedItemInsideAdded(item)


	def onAffectedItemInsideAdded(self, _item):
		pass


	def onItemRemoved(self, item):
		super().onItemRemoved(item)
		if item in self.getItemsInside() and self.canApplyEffect(item):
			self.onAffectedItemInsideRemoved(item)



	def onAffectedItemInsideRemoved(self, _item):
		pass


	def pushItemsInsideToStorage(self):
		pass

	def onDraggedWithParentStart(self, bag):
		super().onDraggedWithParentStart(bag)

	def onDraggedWithParentEnd(self):
		super().onDraggedWithParentEnd()
		if self.dragged:
			pass
		else:
			self.resetZ()


	def getNumAffectedInside(self):
		num = 0
		for item in _iter(self.getAffectedItemsInside()):
			num += 1
		return num



	def getNumAffectedInside_type(self, type):
		type = int(type)
		num = 0
		for item in _iter(self.getAffectedItemsInside()):
			num += item.getTypeMultiplicity(type)
		return num


	def getBagMultiplicity(self, forItem):
		return 1


	def discard(self, discardGems=True):
		if self.pooled:
			pass

		super().discard(discardGems)


	def _readyInit(self):
		super()._readyInit()
		if self.bagTilemapPosition == None:
			pass



_R.reg("res://gd_core_items/Bag.gd", Bag_2)
_R.reg("Bag", Bag_2)
_R.reg("Bag", Bag_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Rarity.Unique
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
