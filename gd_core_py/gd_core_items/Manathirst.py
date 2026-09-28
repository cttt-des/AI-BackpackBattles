# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Manathirst(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Manathirst.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaGained = 0
		self.fillingTween = None
		self.filling = None
		self.fillingGlow = None
		self.fillingHeight = None
		self.fillingAnimation = None
		self.manaNeededForLifesteal = None
		self.dam = None
		self.mana = None


	def onPrepare(self):
		self.manaGained = 0

		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")
		self.tweenFilling(0)


	def tweenFilling(self, relHeight):
		pass

	def onManaChanged(self, amount, event):
		if amount > 0:
			self.manaGained += amount
			if self.manaGained >= self.manaNeededForLifesteal:
				self.manaGained -= self.manaNeededForLifesteal
				self.stealLife(self.dam + self.character().getVampirism(), _div(self.getP_m('lifesteal'), 100.0), event)

			relHeight = _div(self.manaGained, self.manaNeededForLifesteal)
			self.tweenFilling(relHeight)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.giveMana(self.mana, damageRes.event)


	def onShopEntered(self):
		self.tweenFilling(1)

	def _readyInit(self):
		super()._readyInit()
		self.manaNeededForLifesteal = self.getP1()
		self.dam = self.getP("dam")
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Manathirst.gd", Manathirst)
_R.reg("Manathirst", Manathirst)
