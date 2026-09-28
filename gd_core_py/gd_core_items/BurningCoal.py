# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BurningCoal(_R.C("res://gd_core_items/Gems/Gem.gd")):

	resource_path = "res://gd_core_items/BurningCoal.gd"

	gemColor = Color(1.5, 1, 0.7)

	def canBlock(self):
		return False


	def prepareWeapon(self):
		self.connectForCombat(self.socket.getItem(), "pre_deal_damage_early", "preAttack")


	def preAttack(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			damageRes.damage += self.getP1()
			self.giveHeat(self.getP2())
			self.miniActivate()


	def prepareArmor(self):
		self.character().changeResistStacks(_R.C("CoreConst").EventType.Cold, round(self.getP3() * self.getGemPower()))


	def combatStartArmor(self):
		self.giveBlock(self.getBlock() * self.getGemPower())
		self.miniActivate()


	def doCooldownEffect(self):
		self.giveHeat(self.getP4())
		self.cleanseRandomDebuffs(self.getP5())
		self.onAfterEffectFinished()


	def onHotSwapHoverWithGemEnd(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/BurningCoal.gd", BurningCoal)
_R.reg("BurningCoal", BurningCoal)
