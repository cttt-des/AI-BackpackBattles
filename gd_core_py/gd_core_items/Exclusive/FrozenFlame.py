# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FrozenFlame(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/FrozenFlame.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affected2Item = None
		self.heatCounter = 0
		self.gatedItems = { "Spell Scroll Frostbolt": 2, "Book of Ice": 2, "Frostbite": 1, "Frozen Buckler": 1, "Ice Armor": 1, "Ice Dragon": 1, "Spell Scroll Ice": 1, "Magic Mirror": 1, "Ice Flower": 1, "Devouring Sphere": 1, "Snowmaster": 1 }
		self.heatNeeded = 0
		self.coldPerHeat = 0
		self.critSeverityPerCold = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Ice)


	def canAffect_secondary(self, item):
		return item.canDamage()


	def onPrepare(self):
		self.heatCounter = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")

		self.affected2Item = self.getFirstAffectedItem(_R.C("CoreConst").Affected.Secondary)
		if self.affected2Item:
			self.connectForCombat(self.opponent(), "character_cold_changed", "onOpponentColdChanged")


	def onCombatStart(self):
		numAffected = self.getNumAffectedItems()
		if numAffected > 0:
			self.giveBlock(numAffected * self.getBlock())
		self.activate()


	def onHeatChanged(self, amount, event):
		if amount > 0:
			self.heatCounter += amount
			relHeat = _div(float(self.heatCounter), self.heatNeeded)
			cold = int(relHeat) * self.coldPerHeat
			self.heatCounter %= self.heatNeeded
			if cold > 0:
				self.inflictCold(cold, event)
				self.showCooldownSmooth(_div(float(self.heatCounter), self.heatNeeded), True)
			else:
				self.showCooldownSmooth(relHeat, False)


	def onOpponentColdChanged(self, amount, _event):

		self.affected2Item.changeCritChancePercent(amount * self.getChance())
		self.affected2Item.addCritSeverity(amount * self.critSeverityPerCold)


	def getGatedDescriptor(self, rarity):
		return None

	def getRelatedItemColumns(self):
		return 4


	def getRelatedItemHeight(self):
		return 200

	def _readyInit(self):
		super()._readyInit()
		self.heatNeeded = self.getP("heat")
		self.coldPerHeat = self.getP("cold")
		self.critSeverityPerCold = _div(self.getP('critdam'), 100.0)
		pass



_R.reg("res://gd_core_items/Exclusive/FrozenFlame.gd", Exclusive__FrozenFlame)
_R.reg("FrozenFlame", Exclusive__FrozenFlame)
