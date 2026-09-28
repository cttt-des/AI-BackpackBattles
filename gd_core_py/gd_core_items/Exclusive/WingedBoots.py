# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__WingedBoots(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/WingedBoots.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.healthThreshold = None
		self.empower = None
		self.debuffs = None
		self.dodges = None


	def onPrepare(self):
		self.hasActivated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True
			self.giveEmpower(self.empower, event)
			self.cleanseRandomDebuffs(self.debuffs)
			self.character().changeDodgeStacks(self.dodges)
			self.consume()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 2

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP('healtht'), 100.0) - 0.0001
		self.empower = int(self.getP("empower"))
		self.debuffs = int(self.getP("cleanse"))
		self.dodges = int(self.getP("dodge"))


_R.reg("res://gd_core_items/Exclusive/WingedBoots.gd", Exclusive__WingedBoots)
_R.reg("WingedBoots", Exclusive__WingedBoots)
