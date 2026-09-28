# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpellScrollNature(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpellScrollNature.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaAcc = 0.0
		self.staminaNeeded = None
		self.stamina = None
		self.manaNeeded = None


	def canAffect(self, item):
		return item.canUseStamina()


	def onPrepare(self):
		self.staminaAcc = 0.0
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "used_stamina", "onItemUsedStamina")


	def onItemUsedStamina(self, amount):
		self.staminaAcc += amount
		activating = False

		while self.staminaAcc >= self.staminaNeeded - 0.0001:
			if self.character().getMana() >= self.manaNeeded:
				event = self.useMana(self.manaNeeded)
				self.giveStamina(self.stamina, event)
				self.activate()
				activating = True
			self.staminaAcc -= self.staminaNeeded

		self.showCooldownSmooth(_div(self.staminaAcc, self.staminaNeeded), activating)

	def _readyInit(self):
		super()._readyInit()
		self.staminaNeeded = self.getP("staminat")
		self.stamina = self.getP("stamina")
		self.manaNeeded = self.getP("mana")


_R.reg("res://gd_core_items/Exclusive/SpellScrollNature.gd", Exclusive__SpellScrollNature)
_R.reg("SpellScrollNature", Exclusive__SpellScrollNature)
