# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Pot(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Pot.gd"

	def _init_fields(self):
		super()._init_fields()
		self._numFood = 0
		self.foodPotionSpeed = None
		self.heat = None
		self.regen = None

	@property
	def numFood(self):
		return self._numFood
	@numFood.setter
	def numFood(self, v):
		self._numFood = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1)


	def canAffect_secondary(self, item):
		return item.hasType(_H_2)


	def onPrepare(self):
		self.numFood = self.getNumAffectedItems(_H_3)
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


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Potion
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Food
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
