# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HeroicPotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/HeroicPotion.gd"


	def onTriggerPotion(self, triggerEvent=None):
		self.giveStamina(self.getP1(), triggerEvent)
		self.giveEmpower(self.getP2(), triggerEvent)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_pre_use_stamina", "checkStamina")


	def checkStamina(self, amount):
		if self.isEmpty():
			return

		if self.character().getCurrentStamina() < amount:
			self.consumePotion()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/HeroicPotion.gd", HeroicPotion)
_R.reg("HeroicPotion", HeroicPotion)
