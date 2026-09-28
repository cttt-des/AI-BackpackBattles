# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Frostbite(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Frostbite.gd"

	def _init_fields(self):
		super()._init_fields()
		self.gaveVampirism = False
		self.damagePerCold = None
		self.coldNeeded = None
		self.vampirism = None


	def onPrepare(self):
		self.gaveVampirism = False
		self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")
		self.connectForCombat(self.opponent(), "character_cold_changed", "onOpponentColdChanged")


	def onVampirismChanged(self, amount, _event):
		self.changeVaryingDamage(amount)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.inflictCold(self.getP1())


	def onOpponentColdChanged(self, amount, event):
		self.changeVaryingDamage(self.damagePerCold * amount)

		if not self.gaveVampirism and self.opponent().getCold() >= self.coldNeeded:
			self.gaveVampirism = True
			self.giveVampirism(self.vampirism, event)

	def _readyInit(self):
		super()._readyInit()
		self.damagePerCold = self.getP2()
		self.coldNeeded = int(self.getP3())
		self.vampirism = int(self.getP4())


_R.reg("res://gd_core_items/Exclusive/Frostbite.gd", Exclusive__Frostbite)
_R.reg("Frostbite", Exclusive__Frostbite)
