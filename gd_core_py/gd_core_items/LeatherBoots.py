# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class LeatherBoots(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/LeatherBoots.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.healthThreshold = None


	def onPrepare(self):
		self.hasActivated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True
			self.giveLucky(self.getP2(), event)
			self.giveEmpower(self.getP3(), event)
			self.giveBlock(self.getBlock(), True, event)
			self.consume()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 2

	def _readyInit(self):
		super()._readyInit()
		self.healthThreshold = _div(self.getP1(), 100.0) - 0.0001


_R.reg("res://gd_core_items/LeatherBoots.gd", LeatherBoots)
_R.reg("LeatherBoots", LeatherBoots)
