# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CursedDagger(_R.C("res://gd_core_items/Dagger.gd")):

	resource_path = "res://gd_core_items/CursedDagger.gd"


	def canAffect(self, item):
		return item.canDamage()


	def onPrepare(self):
		self.connectToOpponentDebuffs("onOpponentDebuffsChanged")


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.inflictRandomDebuffs(self.getP1())


	def onOpponentDebuffsChanged(self, amount, _event):
		extraCritChance = amount * self.getChance()
		extraAccuracy = amount * self.getP2()
		self.addCritChancePercent(extraCritChance)
		self.addAccuracy(extraAccuracy)

		for item in _iter(self.getAffectedItems()):
			item.addCritChancePercent(extraCritChance)
			if item.isWeapon():
				item.addAccuracy(extraAccuracy)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/CursedDagger.gd", CursedDagger)
_R.reg("CursedDagger", CursedDagger)
