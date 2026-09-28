# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HeartContainer(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/HeartContainer.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.regenNeeded = None
		self.fillAnimation = None


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")


	def doCooldownEffect(self):
		self.giveRegeneration(self.getP1())
		self.activate()


	def onRegenChanged(self, amount, event):
		if amount > 0 and not self.activated and self.character().getRegeneration() >= self.regenNeeded:
			self.setState(True, True)
			self.useRegeneration(self.regenNeeded, event)
			self.giveMaxHealth(self.getP_m("maxhealth"), event)
			self.giveEmpower(self.getP4(), event)
			self.character().addHealingEfficiency(_div(self.getP5(), 100.0))


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, filled):
		if self.activated == filled:
			return
		self.activated = filled

		if filled:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.regenNeeded = int(self.getP2())


_R.reg("res://gd_core_items/HeartContainer.gd", HeartContainer)
_R.reg("HeartContainer", HeartContainer)
