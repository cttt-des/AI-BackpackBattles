# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gems__Sapphire(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Gems/Sapphire.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaCounter = 0
		self.spectral = False
		self.manaNeeded = None

	gemColor = Color(0.8, 0.8, 3)

	def doCooldownEffect(self):
		self.inflictCold(self.getP5())
		self.onAfterEffectFinished()


	def prepareWeapon(self):
		self.spectral = False
		self.connectForCombat(self.socket.getItem(), "pre_deal_damage_late", "preAttack")
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def preAttack(self, damageRes):

		self.spectral = self.rollChance()
		if self.spectral:
			damageRes.damageSource.makeSpectral()


	def onAttack(self, damageRes):
		if self.spectral and damageRes.hasHit():
			self.giveMana(self.getP1(), damageRes.event)
			self.inflictCold(self.getP4(), damageRes.event)
			self.miniActivate()


	def prepareArmor(self):
		self.manaCounter = 0
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onManaChanged(self, amount, event):
		if amount > 0:
			self.manaCounter += amount
			relMana = _div(self.manaCounter, self.manaNeeded)
			block = relMana * self.getP3()
			self.manaCounter %= self.manaNeeded
			if block > 0:
				self.giveBlock(self.getGemPower() * block, event)
				self.miniActivate()
				self.showCooldownSmooth(relMana, True)
			else:
				self.showCooldownSmooth(relMana, False)

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP2())


_R.reg("res://gd_core_items/Gems/Sapphire.gd", Gems__Sapphire)
_R.reg("Sapphire", Gems__Sapphire)
