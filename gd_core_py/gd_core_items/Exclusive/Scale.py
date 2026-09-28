# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Scale(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Scale.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regen = None
		self.mana = None
		self.speedPerGold = None
		self.maxGoldDif = None
		self.equilibriumSpeed = None
		self.leftCounter = None
		self.rightCounter = None
		self.leftCounterDefaultPos = None
		self.rightCounterDefaultPos = None


	def ready_deferred(self):
		super().ready_deferred()
		self.updateCounterPositions()


	def canAffect(self, item):
		return True


	def canAffect_secondary(self, item):
		return True


	def getCounterValue(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		gold = 0
		if self.placed:
			for item in _iter(self.getAffectedItems(color)):
				gold += item.getPrice()
		else:
			for item in _iter(self.getAffectedItems_nocache(color)):
				gold += item.getPrice()
		return gold


	def getCounterValue2(self):
		return self.getCounterValue(_R.C("CoreConst").Affected.Secondary)


	def onPrepare(self):
		c1 = self.getCounterValue()
		c2 = self.getCounterValue2()
		self.addSpeed(self.speedPerGold * min(c1, c2))
		if abs(c1 - c2) <= self.maxGoldDif:
			for item in _iter(self.getAffectedItems()):
				item.addSpeed(self.equilibriumSpeed)
			for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
				item.addSpeed(self.equilibriumSpeed)


	def doCooldownEffect(self):
		curRegen = self.character().getRegeneration()
		curMana = self.character().getMana()
		if curMana < curRegen:
			self.giveMana(self.mana)
		elif curRegen < curMana:
			self.giveRegeneration(self.regen)
		else:
			if self.ctx.util.flip():
				self.giveMana(self.mana)
			else:
				self.giveRegeneration(self.regen)
		self.activate()


	def updateScale(self):
		c1 = self.getCounterValue()
		c2 = self.getCounterValue2()
		if abs(c1 - c2) <= self.maxGoldDif:
			pass
		elif c1 > c2:
			pass
		else:
			pass


	def onAffectedItemAdded(self, item, color):
		self.updateScale()


	def onAffectedItemRemoved(self, item, color):
		self.updateScale()


	def onAddToInventory(self):
		self.updateScale()


	def onRemoveFromInventory(self):
		pass


	def updateCounterPositions(self):
		pass


	def rotateTo(self, targetRotation, duration=0.15):
		super().rotateTo(targetRotation, duration)
		self.updateCounterPositions()


	def onDraggedWithParentEnd(self):
		super().onDraggedWithParentEnd()
		self.updateCounterPositions()


	def onCalcTradeChance(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.regen = int(self.getP("regen"))
		self.mana = int(self.getP("mana"))
		self.speedPerGold = _div(self.getP('speed'), 100.0)
		self.maxGoldDif = int(self.getP("gold"))
		self.equilibriumSpeed = _div(self.getP('speed2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Scale.gd", Exclusive__Scale)
_R.reg("Scale", Exclusive__Scale)
