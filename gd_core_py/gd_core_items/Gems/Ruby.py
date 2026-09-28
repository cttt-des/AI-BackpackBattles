# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gems__Ruby(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Gems/Ruby.gd"

	gemColor = Color(3, 0.8, 0.8)

	def doCooldownEffect(self):
		self.stealLife(self.getP3(), _div(self.getP_m('lifesteal_factor'), 100.0))
		self.onAfterEffectFinished()


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit():
			self.heal(ceil(_div(damageRes.damage * self.getP_m('lifesteal_weapon'), 100.0)), damageRes.event)
			self.miniActivate()


	def prepareArmor(self):
		self.character().addHealingEfficiency(_div(self.getGemPower() * self.getP2(), 100.0))

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Gems/Ruby.gd", Gems__Ruby)
_R.reg("Ruby", Gems__Ruby)
