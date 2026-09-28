# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gems__Skull(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Gems/Skull.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.healthThreshold = None

	gemColor = Color(0.912109, 0.904984, 0.904984)

	def prepareInventory(self):
		self.activated = False
		self.connectForCombat(self.opponent(), "character_damaged", "onOpponentDamaged")


	def onOpponentDamaged(self, _healthChange, event):
		if not self.activated:
			if self.opponent().getRelativeHealth() <= self.healthThreshold:
				self.activated = True
				self.heal(self.getP_m("heal"), event)
				self.giveEmpower(self.getP3(), event)
				self.activate()


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance2():
			self.stealRandomBuff(1)
			self.miniActivate()


	def prepareArmor(self):
		self.character().changeDebuffResistChances(self.getGemPower() * self.getChance())
		self.character().changeCritResistance(self.getGemPower() * self.getChance())


	def hasCooldown(self):
		return False

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001


_R.reg("res://gd_core_items/Gems/Skull.gd", Gems__Skull)
_R.reg("Skull", Gems__Skull)
