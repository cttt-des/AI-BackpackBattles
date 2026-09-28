# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__VampiricPotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/Exclusive/VampiricPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healthThreshold = None
		self.dam = None
		self.vampirism = None


	def onPrepare(self):

		self.connectForCombat(self.character(), "character_damaged", "onPlayerDamaged")
		self.connectForCombat(self.opponent(), "character_damaged", "onPlayerDamaged")



	def onPlayerDamaged(self, _healthChange, event):
		if self.isEmpty():
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			relHealth2 = self.opponent().getRelativeHealth()
			if relHealth2 < self.healthThreshold:
				self.consumePotion()


	def onTriggerPotion(self, triggerEvent=None):

		self.stealLife(self.dam, _div(self.getP_m('lifesteal'), 100.0), triggerEvent)
		self.giveVampirism(self.vampirism, triggerEvent)


	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0)
		self.dam = self.getP3()
		self.vampirism = int(self.getP2())


_R.reg("res://gd_core_items/Exclusive/VampiricPotion.gd", Exclusive__VampiricPotion)
_R.reg("VampiricPotion", Exclusive__VampiricPotion)
