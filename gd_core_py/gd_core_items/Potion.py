# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Potion(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Potion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.potionColor = Color()
		self.fluidTween = None
		self.isFull = True
		self.connector = None
		self.fluid = None
		self.fluidGradientTex = None
		self.fluidGradient = None
		self.baseFoaminess = None
		self.baseScroll = None
		self.baseLevel = None


	def prepare(self):
		super().prepare()
		self.setState(True)


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Potion)


	def isEmpty(self):
		return not self.isFull


	def fill(self):
		self.isFull = True


	def empty(self):
		self.isFull = False


	def drink(self):
		self.setState(False, True)


	def consumePotion(self, event=None, withActivate=True):
		if self.isEmpty():
			return

		self.drink()

		self.triggerPotion(event)

		affected = self.getAffectedItems()
		if not (not affected):
			affected[0].triggerPotion()
			affected[0].miniActivate()

		if withActivate:
			self.activate()


	def onTriggerPotion(self, triggerEvent=None):
		pass


	def triggerPotion(self, triggerEvent=None):
		self.onTriggerPotion(triggerEvent)
		self.playActivationAnimation()
		self.ctx.bus.emitSignal(self, "potion_triggered", [self])


	def onStateChanged(self, _isFull):
		if _isFull:
			self.fill()
		else:
			self.empty()

		self.isFull = _isFull


	def activate(self, damageRes=None, playCombatAni=True, consume=False, animationOverride=None, emitSignal=True):

		super().activate(damageRes, playCombatAni, consume, None)

		if emitSignal:
			self.ctx.bus.emitSignal(self, "potion_emptied", [self])


	def shopEntered(self, craft):
		super().shopEntered(craft)
		if not self.isFull:
			self.fill()


	def getAffectedCellsAfterRotate_primary(self, rotatedCells):




		if self.faceDirection == _R.C("CoreConst").FaceDirection.DOWN:
			return [rotatedCells[1] + Vector2.UP]
		else:
			return [rotatedCells[0] + Vector2.UP]


	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		super().addToInventory(_inventory, _occupiedCells, _placedByPlayer)
		self.updateConnector()


	def onRemoveFromInventory(self):
		self.resetGradient()


	def onFusingAsIngredient(self):
		self.resetGradient()


	def onAffectedItemAdded(self, item, color):
		if color == _R.C("CoreConst").Affected.Primary:
			self.updateConnector()


	def onAffectedItemRemoved(self, item, color):
		if color == _R.C("CoreConst").Affected.Primary:
			self.updateConnector()


	def updateConnector(self):
		pass

	def resetGradient(self):
		pass


	def discard(self, discardGems=True):
		if self.pooled:
			self.resetGradient()
		super().discard(discardGems)


	def getStarPosition(self):
		return Vector2.ZERO

	def _readyInit(self):
		super()._readyInit()
		pass







_R.reg("res://gd_core_items/Potion.gd", Potion)
_R.reg("Potion", Potion)
_R.reg("Potion", Potion)
