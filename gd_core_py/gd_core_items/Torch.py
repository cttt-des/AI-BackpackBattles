# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Torch(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Torch.gd"

	def _init_fields(self):
		super()._init_fields()
		self.permDamBonus = None


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.addBonusDamage(self.permDamBonus)

	def _readyInit(self):
		super()._readyInit()
		self.permDamBonus = self.getP1()


_R.reg("res://gd_core_items/Torch.gd", Torch)
_R.reg("Torch", Torch)
