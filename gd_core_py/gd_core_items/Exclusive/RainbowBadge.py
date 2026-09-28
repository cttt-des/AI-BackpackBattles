# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RainbowBadge(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/RainbowBadge.gd"


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass

	def doCooldownEffect(self):
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.giveStacks(self.character(), buff, 1)
		self.onAfterEffectFinished()


	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 6


	def getRelatedItemHeight(self):
		return 100

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/RainbowBadge.gd", Exclusive__RainbowBadge)
_R.reg("RainbowBadge", Exclusive__RainbowBadge)
