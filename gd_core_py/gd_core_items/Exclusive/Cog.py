# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Cog(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Cog.gd"


	def canAffect(self, item):
		return item.isCrafted()


	def onCombatStart(self):
		numAffected = self.getNumAffectedItems()
		if numAffected > 0:
			self.giveBlock(self.getBlock() * numAffected)
			self.activate()


	def onSold(self):
		pass

	def getSellPrice(self):
		return 0

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Cog.gd", Exclusive__Cog)
_R.reg("Cog", Exclusive__Cog)
