# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LuckyShortbow(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/LuckyShortbow.gd"


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.giveLucky(1)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/LuckyShortbow.gd", Exclusive__LuckyShortbow)
_R.reg("LuckyShortbow", Exclusive__LuckyShortbow)
