# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HeavyDrinking(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/HeavyDrinking.gd"

	def _init_fields(self):
		super()._init_fields()
		self.allPotions = []
		self.boostedPotions = 0
		self.potionSpeed = None


	def getData(self):
		return self.boostedPotions


	def setData(self, data):
		if data != None:
			self.boostedPotions = data


	def onBought(self):
		self.boostedPotions = 3


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return color == _R.C("CoreConst").Affected.Primary


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Potion)


	def canAffect_global(self, item):
		return item.hasType(_R.C("CoreConst").Type.Potion)


	def onPrepare(self):
		self.addSpeed(self.getNumDistinctAffectedItems() * self.potionSpeed)

		self.allPotions.clear()
		for item in _iter(self.inventory.getItems()):
			if item.hasType(_R.C("CoreConst").Type.Potion) and item != self:
				self.allPotions.append(item)


	def doCooldownEffect(self):
		if not (not self.allPotions):
			potionToTrigger = self.ctx.util.pickRandomElement(self.allPotions)
			potionToTrigger.triggerPotion()
			potionToTrigger.miniActivate()

		self.activate()


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr.hasType(_R.C("CoreConst").Type.Potion):
			self.boostedPotions -= 1

	def _readyInit(self):
		super()._readyInit()
		self.potionSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/HeavyDrinking.gd", Exclusive__HeavyDrinking)
_R.reg("HeavyDrinking", Exclusive__HeavyDrinking)
