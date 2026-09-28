# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PoisonDagger(_R.C("res://gd_core_items/Dagger.gd")):

	resource_path = "res://gd_core_items/PoisonDagger.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poison = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.inflictPoison(self.poison)

	def _readyInit(self):
		super()._readyInit()
		self.poison = int(self.getP1())


_R.reg("res://gd_core_items/PoisonDagger.gd", PoisonDagger)
_R.reg("PoisonDagger", PoisonDagger)
