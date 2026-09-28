# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PoisonGrenade(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/PoisonGrenade.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poisonCritActive = False
		self.tween = None
		self.poison = None
		self.selfPoison = None
		self.cdAdvance = None
		self.luckNeeded = None
		self.light = None
		self.lightAni = None


	def onPrepare(self):
		self.setState(False)

		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckChanged")


	def doCooldownEffect(self):
		self.inflictPoison(self.poison)
		self.selfInflictPoison(self.selfPoison)
		self.onAfterEffectFinished()



	def onChargeReceived(self, _charge):
		self.advanceCooldownSeconds(self.cdAdvance)
		self.miniActivate()


	def onLuckChanged(self, amount, event):
		if amount > 0 and not self.poisonCritActive and self.character().getLucky() >= self.luckNeeded:
			self.opponent().changePoisonCritChancePercent(self.getChance())
			self.setState(True)

		elif amount < 0 and self.poisonCritActive and self.character().getLucky() < self.luckNeeded:
			self.opponent().changePoisonCritChancePercent( - self.getChance())
			self.setState(False)


	def onShopEntered(self):
		pass

	def onStateChanged(self, _poisonCritActive):
		self.poisonCritActive = _poisonCritActive
		if self.poisonCritActive:
			pass

		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.poison = int(self.getP("poison"))
		self.selfPoison = int(self.getP("poison2"))
		self.cdAdvance = self.getP("cdadvance")
		self.luckNeeded = int(self.getP("luckt"))


_R.reg("res://gd_core_items/Exclusive/PoisonGrenade.gd", Exclusive__PoisonGrenade)
_R.reg("PoisonGrenade", Exclusive__PoisonGrenade)
