# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CursedHairComb(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/CursedHairComb.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Vampiric)


	def onPrepare(self):
		self.character().addHealingEfficiency(_div(self.getP3(), 100.0))


		for weapon in _iter(self.getAffectedItems()):
			self.connectForCombat(weapon, "attacked", "onAffectedAttacked")


	def onCombatStart(self):
		self.giveVampirism(self.getP1())
		self.activate()


	def onAffectedAttacked(self, damageRes):
		if damageRes.hasHit():
			bonusLifesteal = self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary) * self.getP_m("lifesteal_scaling")
			self.heal(ceil(damageRes.damage * (self.getP_m("lifesteal") + bonusLifesteal) / 100.0), 
				damageRes.event)










	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/CursedHairComb.gd", CursedHairComb)
_R.reg("CursedHairComb", CursedHairComb)
