# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PiggyofRiches(_R.C("res://gd_core_items/BoxofRiches.gd")):

	resource_path = "res://gd_core_items/Exclusive/PiggyofRiches.gd"


	def onCombatStart(self):
		self.giveMaxHealth(self.inventory.countSocketedGems() * self.getP_m("maxhealth"))
		self.consume()


	def getRelatedItems(self):
		return self.ctx.item_book.getDescriptor("Box of Riches").gatedItems

	def _readyInit(self):
		super()._readyInit()
		self.numGems = 2



_R.reg("res://gd_core_items/Exclusive/PiggyofRiches.gd", Exclusive__PiggyofRiches)
_R.reg("PiggyofRiches", Exclusive__PiggyofRiches)
