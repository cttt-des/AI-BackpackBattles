# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BurningBlade(_R.C("res://gd_core_items/Exclusive/BurningSword.gd")):

	resource_path = "res://gd_core_items/Exclusive/BurningBlade.gd"


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.giveHeat(self.heatOnHit)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/BurningBlade.gd", Exclusive__BurningBlade)
_R.reg("BurningBlade", Exclusive__BurningBlade)
