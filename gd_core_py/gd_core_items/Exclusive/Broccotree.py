# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Broccotree(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/Broccotree.gd"

	def _init_fields(self):
		super()._init_fields()
		self.staminaPerRegen = 0.0
		self.luck = None
		self.luckNeeded = None
		self.regen = None


	def doCooldownEffect(self):
		self.giveLucky(self.luck)

		if self.character().getLucky() >= self.luckNeeded:
			self.giveRegeneration(self.regen)

		self.activate()


	def onPrepare(self):
		baseStaminaRegen = self.character().baseStaminaRegen
		self.staminaPerRegen = _div(self.getP('stamina') * baseStaminaRegen, 100.0)
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")


	def onRegenChanged(self, amount, event):
		if amount > 0:
			self.character().giveStaminaRegeneration(amount * self.staminaPerRegen)

	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.luckNeeded = int(self.getP("luckt"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/Broccotree.gd", Exclusive__Broccotree)
_R.reg("Broccotree", Exclusive__Broccotree)
