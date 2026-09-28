# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BadgerRune(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Exclusive/BadgerRune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.attackSpeedBonus = None
		self.damageReduction = 0
		self.staminaReduction = None

	gemColor = Color(0.845703, 0.420593, 0.062767)

	def isBattleRageItem(self):
		return self.getGemMode() == self.GemMode.Armor


	def prepareWeapon(self):
		self.connectForCombat(self.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit():
			self.getItem().addSpeed(self.attackSpeedBonus)
			self.miniActivate()


	def prepareArmor(self):
		self.connectForCombat(self.character(), "pre_take_damage", "preTakeDamage")


	def preTakeDamage(self, damageRes):
		if damageRes.triggerOnAttacked() and self.character().isBattleRaging():
			damageRes.applyDamageReduction(round(self.getGemPower() * self.damageReduction), self)
			self.miniActivate()


	def hasCooldown(self):
		return False


	def prepareInventory(self):
		for item in _iter(self.inventory.getItems()):

			item.changeStaminaFactor( - self.staminaReduction)











	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.attackSpeedBonus = _div(self.getP('attackspeed'), 100.0)
		self.damageReduction = self.getP("damreduction")
		self.staminaReduction = self.getP("stamina")


_R.reg("res://gd_core_items/Exclusive/BadgerRune.gd", Exclusive__BadgerRune)
_R.reg("BadgerRune", Exclusive__BadgerRune)
