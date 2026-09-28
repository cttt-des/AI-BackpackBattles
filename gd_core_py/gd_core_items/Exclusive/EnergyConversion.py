# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__EnergyConversion(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/EnergyConversion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stackTypes = None
		self.heat = None
		self.heatThreshold = None
		self.numBuffs = None
		self.speedPerFood = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food)


	def onPrepare(self):
		self.addSpeed(self.getNumAffectedItems() * self.speedPerFood)


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			if self.character().getHeat() >= self.heatThreshold:
				self.giveRandomBuffs(self.numBuffs, None, self.stackTypes)
			else:
				self.giveHeat(self.heat)

			self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.heat = int(self.getP("heat"))
		self.heatThreshold = int(self.getP("heatt"))
		self.numBuffs = int(self.getP("buffs"))
		self.speedPerFood = _div(self.getP('speed'), 100.0)
		self.stackTypes = _R.C("CoreConst").getBuffs()
		_erase(self.stackTypes, _R.C("CoreConst").EventType.Heat)



_R.reg("res://gd_core_items/Exclusive/EnergyConversion.gd", Exclusive__EnergyConversion)
_R.reg("EnergyConversion", Exclusive__EnergyConversion)
