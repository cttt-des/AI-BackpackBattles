# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Pot(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Pot.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numFood = 0
		self.foodPotionSpeed = None
		self.heat = None
		self.regen = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Potion)


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food)


	def onPrepare(self):
		self.numFood = self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary)
		self.addSpeed(self.foodPotionSpeed * (self.getNumAffectedItems() + self.numFood))

		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "potion_triggered", "onPotionTriggered")


	def doCooldownEffect(self):
		self.giveHeat(self.heat)
		self.giveRegeneration(self.regen)
		self.onAfterEffectFinished()


	def onPotionTriggered(self, _potion):
		self.heal(self.getP_m("heal") + self.getP_m("heal_food") * self.numFood)

	def _readyInit(self):
		super()._readyInit()
		self.foodPotionSpeed = _div(self.getP('speed'), 100.0)
		self.heat = int(self.getP("heat"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/Pot.gd", Exclusive__Pot)
_R.reg("Pot", Exclusive__Pot)
