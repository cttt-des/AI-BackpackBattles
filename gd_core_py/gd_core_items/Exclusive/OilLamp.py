# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__OilLamp(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/OilLamp.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusDam = None
		self.bonusAcc = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onCombatStart(self):
		self.giveHeat(self.getP("heat"))
		self.activate()


	def doCooldownEffect(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusDamage(self.bonusDam)
			item.addAccuracy(self.bonusAcc)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.bonusDam = self.getP("dam")
		self.bonusAcc = self.getP("accuracy")


_R.reg("res://gd_core_items/Exclusive/OilLamp.gd", Exclusive__OilLamp)
_R.reg("OilLamp", Exclusive__OilLamp)
