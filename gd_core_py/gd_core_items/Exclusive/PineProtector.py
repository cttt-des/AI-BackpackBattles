# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PineProtector(_R.C("res://gd_core_items/SpikedShield.gd")):

	resource_path = "res://gd_core_items/Exclusive/PineProtector.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damblockIncrease = 0
		self.damblock2 = None
		self.maxblock = None


	def getDamageBlock(self):
		return self.getParamModified("damblock", self.getP("damblock") + self.damblockIncrease)


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food)


	def onPrepare(self):
		super().onPrepare()
		self.damblockIncrease = 0
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onItemActivated")

		self.maxSpikes = self.getP("maxspikes") + self.getP("maxspikes_food") * self.getNumAffectedItems()


	def onItemActivated(self, event):
		if self.damblockIncrease < self.maxblock:
			self.damblockIncrease += min(self.damblock2, self.maxblock - self.damblockIncrease)
		self.heal()

	def _readyInit(self):
		super()._readyInit()
		self.damblock2 = self.getP("damblock2")
		self.maxblock = self.getP("maxblock")


_R.reg("res://gd_core_items/Exclusive/PineProtector.gd", Exclusive__PineProtector)
_R.reg("PineProtector", Exclusive__PineProtector)
