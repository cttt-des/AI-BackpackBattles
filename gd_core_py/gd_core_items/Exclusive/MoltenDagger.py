# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MoltenDagger(_R.C("res://gd_core_items/Dagger.gd")):

	resource_path = "res://gd_core_items/Exclusive/MoltenDagger.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heatNeeded = None
		self.bonusDam = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.character().getHeat() >= self.heatNeeded:
			self.addBonusDamage(self.bonusDam)
			self.useHeat(self.heatNeeded)

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = int(self.getP1())
		self.bonusDam = int(self.getP2())


_R.reg("res://gd_core_items/Exclusive/MoltenDagger.gd", Exclusive__MoltenDagger)
_R.reg("MoltenDagger", Exclusive__MoltenDagger)
