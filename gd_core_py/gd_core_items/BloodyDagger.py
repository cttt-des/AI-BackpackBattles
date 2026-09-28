# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BloodyDagger(_R.C("res://gd_core_items/Dagger.gd")):

	resource_path = "res://gd_core_items/BloodyDagger.gd"

	def _init_fields(self):
		super()._init_fields()
		self.vampirismStacks = 0


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Vampiric)


	def onPrepare(self):
		self.vampirismStacks = 0


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.vampirismStacks < self.getP2():
				self.giveVampirism(self.getP1())
				self.vampirismStacks += self.getP1()

			numAffected = self.getNumAffectedItems()
			if numAffected > 0:
				self.heal(numAffected * self.getP_m("heal"))

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/BloodyDagger.gd", BloodyDagger)
_R.reg("BloodyDagger", BloodyDagger)
