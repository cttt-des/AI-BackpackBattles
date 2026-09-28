# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Boomerang(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Boomerang.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaReduction = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.changeStaminaFactor( - self.staminaReduction)
			if self.rollChance():
				self.stealRandomBuff(1)

	def _readyInit(self):
		super()._readyInit()
		self.staminaReduction = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/Boomerang.gd", Exclusive__Boomerang)
_R.reg("Boomerang", Exclusive__Boomerang)
