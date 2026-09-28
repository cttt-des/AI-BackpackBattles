# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__EmeraldWhelp(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/EmeraldWhelp.gd"


	def onCombatStart(self):
		self.giveLucky(self.getP1())
		self.activate(None, False)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.inflictPoison(self.getP2())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/EmeraldWhelp.gd", Exclusive__EmeraldWhelp)
_R.reg("EmeraldWhelp", Exclusive__EmeraldWhelp)
