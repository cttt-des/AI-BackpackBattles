# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gems__Topaz(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Gems/Topaz.gd"

	gemColor = Color(2, 1.8, 0.8)

	def prepareInventory(self):
		self.character().giveStaminaRegeneration(_div(self.getP2(), 100.0))


	def prepareWeapon(self):
		self.socket.getItem().addSpeed(_div(self.getP1(), 100))


	def prepareArmor(self):
		self.character().changeStunResistance(self.getGemPower() * self.getChance())
		self.character().changeCritResistance(self.getGemPower() * self.getChance2())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Gems/Topaz.gd", Gems__Topaz)
_R.reg("Topaz", Gems__Topaz)
