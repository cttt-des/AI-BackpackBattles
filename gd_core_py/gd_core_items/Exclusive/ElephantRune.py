# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ElephantRune(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Exclusive/ElephantRune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stunReadyTime = 0.0
		self.debuffResistChance = 0.0
		self.debuffResistTimer = None
		self.stunCd = None

	gemColor = Color(0.466766, 0.625994, 0.742188)

	def prepareWeapon(self):
		self.connectForCombat(self.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			if self.ctx.time >= self.stunReadyTime:
				self.stunReadyTime = self.ctx.time + self.stunCd
				self.stun(self.getP_m("dur_stun"), damageRes.event)
				self.miniActivate()


	def prepareArmor(self):
		self.debuffResistChance = self.getGemPower() * self.getChance2()
		self.character().changeDebuffResistChances(self.debuffResistChance)


	def combatStartArmor(self):
		self.debuffResistTimer.start(self.getP_m("dur_resist"))


	def removeDebuffResistance(self):
		self.character().changeDebuffResistChances( - self.debuffResistChance)


	def combatEndArmor(self):
		self.debuffResistTimer.stop()



	def hasCooldown(self):
		return False


	def combatStartInventory(self):
		self.giveMaxHealth()
		self.consume()


	def onHotSwapHoverWithGemEnd(self):
		pass


	def hasInventoryDuration(self):
		return False

	def _readyInit(self):
		super()._readyInit()
		self.debuffResistTimer = self.newItemTimer("DebuffResistTimer", "removeDebuffResistance", False)
		self.stunCd = self.getBaseCooldown()


_R.reg("res://gd_core_items/Exclusive/ElephantRune.gd", Exclusive__ElephantRune)
_R.reg("ElephantRune", Exclusive__ElephantRune)
