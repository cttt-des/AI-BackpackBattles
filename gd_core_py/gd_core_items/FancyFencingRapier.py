# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class FancyFencingRapier(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/FancyFencingRapier.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckNeeded = None
		self.bonusDam = None
		self.luck = None


	def onDealtDamage(self, damageRes):

		if damageRes.hasHit():
			if self.tryUseLucky(self.luckNeeded, damageRes.event):
				self.addBonusDamage(self.bonusDam)
		else:
			self.giveLucky(self.luck, damageRes.event)


	def _readyInit(self):
		super()._readyInit()
		self.luckNeeded = int(self.getP("luckt"))
		self.bonusDam = self.getP("dam")
		self.luck = int(self.getP("luck"))


_R.reg("res://gd_core_items/FancyFencingRapier.gd", FancyFencingRapier)
_R.reg("FancyFencingRapier", FancyFencingRapier)
