# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gems__Emerald(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Gems/Emerald.gd"

	gemColor = Color(0.8, 3, 0.8)

	def doCooldownEffect(self):
		self.giveRegeneration(self.getP3())
		self.onAfterEffectFinished()


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "attacked", "onAttack")


	def onAttack(self, damageRes):
		if damageRes.hasHit():
			if self.rollChance():
				self.inflictPoison(self.getP1(), damageRes.event)
				self.miniActivate()


	def prepareArmor(self):
		self.character().changeResistChance(_R.C("CoreConst").EventType.Poison, self.getGemPower() * self.getP2())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Gems/Emerald.gd", Gems__Emerald)
_R.reg("Emerald", Gems__Emerald)
