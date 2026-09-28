# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BurningTorch(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/BurningTorch.gd"

	def _init_fields(self):
		super()._init_fields()
		self.permDamBonus = None


	def onCombatStart(self):
		self.giveHeat(self.getP1())
		self.activate(None, False)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.addBonusDamage(self.permDamBonus)

	def _readyInit(self):
		super()._readyInit()
		self.permDamBonus = self.getP2()


_R.reg("res://gd_core_items/BurningTorch.gd", BurningTorch)
_R.reg("BurningTorch", BurningTorch)
