# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LeafBadge(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/LeafBadge.gd"


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass

	def canAffect(self, item):
		return item.canDamage()


	def onPrepare(self):
		if not (not self.getAffectedItems()):
			self.connectForCombat(self.character(), "character_lucky_changed", "onLuckyChanged")


	def onLuckyChanged(self, amount, _event):
		for item in _iter(self.getAffectedItems()):
			item.changeCritChancePercent(amount * self.getChance())


	def doCooldownEffect(self):
		self.giveLucky(1)
		self.activate()


	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 3

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/LeafBadge.gd", Exclusive__LeafBadge)
_R.reg("LeafBadge", Exclusive__LeafBadge)
