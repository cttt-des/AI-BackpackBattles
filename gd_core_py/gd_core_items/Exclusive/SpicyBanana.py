# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpicyBanana(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpicyBanana.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaUsed = 0.0
		self.boostedBananas = 0
		self.bananaDescriptor = None
		self.manananaDescriptor = None
		self.heatPerActivation = None
		self.staminaForHeal = None


	def canAffect(self, item):
		return item.isA(self.bananaDescriptor) or item.isA(self.manananaDescriptor)


	def onBought(self):
		self.boostedBananas = 3


	def getData(self):
		return self.boostedBananas


	def setData(self, data):
		if data != None:
			self.boostedBananas = data


	def onPrepare(self):

		for banana in _iter(self.getAffectedItems()):
			self.connectForCombat(banana, "activated", "onBananaActivated")

		self.staminaUsed = 0
		self.connectForCombat(self.character(), "character_used_stamina", "onStaminaUsed")


	def onBananaActivated(self, event):
		if self.rollChance():
			self.giveHeat(self.heatPerActivation, event)
			self.activate()


	def onStaminaUsed(self, amount):
		self.staminaUsed += amount
		healTicks = floor(_div(self.staminaUsed, self.staminaForHeal))
		if healTicks > 0:
			self.heal(healTicks * self.getP_m("heal"))
			self.staminaUsed -= healTicks * self.staminaForHeal
			self.miniActivate()


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.bananaDescriptor:
			self.boostedBananas -= 1

	def _readyInit(self):
		super()._readyInit()
		self.bananaDescriptor = self.ctx.item_book.getDescriptor("Banana")
		self.manananaDescriptor = self.ctx.item_book.getDescriptor("Mananana")
		self.heatPerActivation = int(self.getP("heat"))
		self.staminaForHeal = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/SpicyBanana.gd", Exclusive__SpicyBanana)
_R.reg("SpicyBanana", Exclusive__SpicyBanana)
