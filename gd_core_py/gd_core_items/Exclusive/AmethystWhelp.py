# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmethystWhelp(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmethystWhelp.gd"


	def onCombatStart(self):
		self.inflictRandomDebuffs(self.getP1())
		self.activate(None, False)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.removeRandomBuffs(1)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/AmethystWhelp.gd", Exclusive__AmethystWhelp)
_R.reg("AmethystWhelp", Exclusive__AmethystWhelp)
