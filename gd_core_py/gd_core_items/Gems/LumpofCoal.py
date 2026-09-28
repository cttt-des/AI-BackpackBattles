# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Gems__LumpofCoal(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/Gems/LumpofCoal.gd"

	gemColor = Color(0.132813, 0.132813, 0.132813)

	def canBlock(self):
		return False


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "pre_deal_damage_early", "preAttack")


	def preAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			damageRes.damage += self.getP1()
			self.miniActivate()


	def prepareArmor(self):
		self.character().changeDebuffResistStacks(round(self.getGemPower()))


	def combatStartArmor(self):
		self.giveBlock(round(self.getGemPower() * self.getBlock()))
		self.miniActivate()


	def doCooldownEffect(self):
		self.giveRandomBuffs(1)
		self.inflictRandomDebuffs(1)
		self.onAfterEffectFinished()


	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Gems/LumpofCoal.gd", Gems__LumpofCoal)
_R.reg("LumpofCoal", Gems__LumpofCoal)
