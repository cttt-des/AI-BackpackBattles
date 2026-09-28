# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RelicCase(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/RelicCase.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damBonusFactor = None
		self.staminaReduction = None


	def canApplyEffect(self, toItem):
		return toItem.isWeapon()


	def doCooldownEffect(self):
		for item in _iter(self.getAffectedItemsInside()):
			if item.canBeEmpowered():
				item.addBonusDamageFactor(self.damBonusFactor)
			item.changeStaminaFactor( - self.staminaReduction)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.damBonusFactor = _div(self.getP('bonusdam'), 100.0)
		self.staminaReduction = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/RelicCase.gd", Exclusive__RelicCase)
_R.reg("RelicCase", Exclusive__RelicCase)
