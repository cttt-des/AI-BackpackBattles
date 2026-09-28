# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Wrench(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Wrench.gd"


	def canAffect(self, item):
		return item.gainsBuffs()


	def canAffect_secondary(self, item):
		return item.canDamage()


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			item1 = self.getFirstAffectedItem(_R.C("CoreConst").Affected.Primary)
			if item1 != None:
				item1.changeAmplificiationChancePercent_allBuffs(self.getChance())

			item2 = self.getFirstAffectedItem(_R.C("CoreConst").Affected.Secondary)
			if item2 != None:
				item2.changeCritChancePercent(self.getChance2())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Wrench.gd", Exclusive__Wrench)
_R.reg("Wrench", Exclusive__Wrench)
