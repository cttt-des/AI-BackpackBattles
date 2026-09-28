# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ManaPotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/ManaPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthThreshold = None


	def onTriggerPotion(self, event=None):
		self.giveMana(self.getP2(), event)

		self.giveMaxHealth()


	def onPrepare(self):

		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _healthChange, event):
		if self.isEmpty():
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.consumePotion(event)


	def onManaChanged(self, amount, event):
		if self.isEmpty():
			return

		if (amount < 0 and 
			isinstance(event.getOrigin(), _R.C("Item")) and 
			event.getOrigin().character() == self.character()):
				self.consumePotion(event)

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001


_R.reg("res://gd_core_items/ManaPotion.gd", ManaPotion)
_R.reg("ManaPotion", ManaPotion)
