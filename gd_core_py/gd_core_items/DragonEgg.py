# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class DragonEgg(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/DragonEgg.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hatchParticles = None
		self.firePulse = None
		self.whelpName = None
		self.roundsToHatch = None
		self.reflectionStacks = None


	def getData(self):
		return self.roundsToHatch


	def setData(self, data):
		self.roundsToHatch = data
		self.updateEgg()


	def updateEgg(self):
		if self.canHatch():
			self.showCooldownSmooth(1.0, False)
		else:
			self.showCooldownSmooth(1.0 - _div(self.roundsToHatch, self.getP2()), False)


	def isNextToNest(self):
		if self.placed:
			for item in _iter(self.inventory.getItems()):
				if item.getName() == "Dragon Nest":
					return self in item.getAffectedItems()

		return False


	def readyToTransform(self):
		return self.canHatch()


	def canHatch(self):
		return (self.roundsToHatch == 0 or 
				(self.roundsToHatch == 1 and self.isNextToNest()))


	def shopEntered(self, craft):
		super().shopEntered(craft)

	def startHatching(self):
		self.ctx.util.callDelayed(self, "hatch", self.TRANSFORMATION_DUR - 0.1)
		for shadow in _iter(self.shadows):
			shadow.offset = Vector2(0, - 138)


	def hatch(self):
		self.ctx.defer(self, "hatch_deferred", [])


	def hatch_deferred(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.roundsToHatch = self.getP2()
		self.updateEgg()



_R.reg("res://gd_core_items/DragonEgg.gd", DragonEgg)
_R.reg("DragonEgg", DragonEgg)
_R.reg("DragonEgg", DragonEgg)
