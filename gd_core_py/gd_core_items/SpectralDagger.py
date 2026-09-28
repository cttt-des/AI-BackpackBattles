# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class SpectralDagger(_R.C("res://gd_core_items/Dagger.gd")):

	resource_path = "res://gd_core_items/SpectralDagger.gd"


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			event = self.tryUseMana(self.getP1())
			if event:
				damageRes.damage += self.getP2()
				damageRes.damageSource.makeSpectral()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/SpectralDagger.gd", SpectralDagger)
_R.reg("SpectralDagger", SpectralDagger)
