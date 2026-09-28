# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PoweroftheMoon(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/PoweroftheMoon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.moonArmorDescriptor = None
		self.moonShieldDescriptor = None
		self.manaOrbDescriptor = None
		self.timeAdvance = None
		self.blind = None


	def canAffect(self, item):
		return item.isA(self.moonArmorDescriptor) or item.isA(self.moonShieldDescriptor)


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def onBought(self):
		self.boosted = 1


	def onPostCombatStart(self):
		self.ctx.combat.advanceTime(self.timeAdvance)


	def onPrepare(self):
		self.connectForCombat(self.ctx.combat, "fatigue_start", "onFatigueStarted")

		for item in _iter(self.getAffectedItems()):
			if item.isA(self.moonArmorDescriptor):

				self.connectForCombat(item, "activated", "onMoonArmorActivated")
			else:

				self.connectForCombat(item, "activated", "onMoonShiedActivated")


	def onFatigueStarted(self):
		bonusHealth = _div(self.getP_m('maxhealth'), 100.0) * self.character().getMaxHealth()
		self.giveMaxHealth(bonusHealth)
		self.activate()


	def onMoonArmorActivated(self, event):
		self.inflictBlind(self.blind, event)


	def onMoonShiedActivated(self, event):
		self.giveReflectStacks(1)


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.manaOrbDescriptor:
			self.boosted -= 1

	def _readyInit(self):
		super()._readyInit()
		self.moonArmorDescriptor = self.ctx.item_book.getDescriptor("Moon Armor")
		self.moonShieldDescriptor = self.ctx.item_book.getDescriptor("Moon Shield")
		self.manaOrbDescriptor = self.ctx.item_book.getDescriptor("Mana Orb")
		self.timeAdvance = self.getP("time")
		self.blind = int(self.getP("blind"))


_R.reg("res://gd_core_items/Exclusive/PoweroftheMoon.gd", Exclusive__PoweroftheMoon)
_R.reg("PoweroftheMoon", Exclusive__PoweroftheMoon)
