# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Everburning(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Everburning.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numFlames = None
		self.burningSwordDescr = None
		self.burningBladeDescr = None
		self.staminaReduction = None


	def onPrepare(self):
		self.numFlames = self.countAllInInventoryOfType(self.ctx.item_book.getDescriptor("Flame"))

		for item in _iter(self.getAllInInventoryOfType(self.burningSwordDescr)):
			item.changeStaminaFactor(self.staminaReduction)

		for item in _iter(self.getAllInInventoryOfType(self.burningBladeDescr)):
			item.changeStaminaFactor(self.staminaReduction)


	def doCooldownEffect(self):
		if self.numFlames > 0:
			self.giveHeat(self.getP("heat") * self.numFlames)
		self.onAfterEffectFinished()


	def canAffect_global(self, item):
		return (item.isA(self.ctx.item_book.getDescriptor("Flame")) or 
				item.isA(self.burningBladeDescr) or 
				item.isA(self.burningSwordDescr))

	def _readyInit(self):
		super()._readyInit()
		self.burningSwordDescr = self.ctx.item_book.getDescriptor("Burning Sword")
		self.burningBladeDescr = self.ctx.item_book.getDescriptor("Burning Blade")
		self.staminaReduction = - self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/Everburning.gd", Exclusive__Everburning)
_R.reg("Everburning", Exclusive__Everburning)
