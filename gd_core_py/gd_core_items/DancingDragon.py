# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class DancingDragon(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/DancingDragon.gd"


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Magic)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckyChanged")


	def onCombatStart(self):
		numAffected = self.getNumAffectedItems()
		if numAffected > 0:
			self.giveHeat(self.getP2() * numAffected)
			self.giveLucky(self.getP3() * numAffected)


	def onHeatChanged(self, amount, _event):
		self.changeVaryingDamage(self.getP1() * amount)


	def onLuckyChanged(self, amount, event):
		self.character().changeDebuffResistChances(self.getChance() * amount)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/DancingDragon.gd", DancingDragon)
_R.reg("DancingDragon", DancingDragon)
