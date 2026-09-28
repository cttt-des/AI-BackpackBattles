# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Bag(_R.C("res://gd_core_items/Item.gd")):

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
		if self.getRarity() == _R.C("CoreConst").Rarity.Unique:
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
		for cell in _iter(self.occupiedCells):
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

		for item in _iter(self.cachedInsideItems):
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



_R.reg("res://gd_core_items/Bag.gd", Bag)
_R.reg("Bag", Bag)
_R.reg("Bag", Bag)
