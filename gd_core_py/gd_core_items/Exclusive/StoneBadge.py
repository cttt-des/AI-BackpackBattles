# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StoneBadge(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/StoneBadge.gd"

	def _init_fields(self):
		super()._init_fields()
		self.goldValue = None


	def onAddToInventory(self):
		pass

	def onAddedToStorageBox(self):
		pass

	def discard(self, discardGems=True):
		super().discard(discardGems)

	def doCooldownEffect(self):
		self.giveBlock()
		self.activate()


	def onShopEntered(self):
		pass

	def getItemsMaxCost(self, maxCost):
		pass

	def getRelatedItems(self):
		return self.getItemsMaxCost(self.goldValue)


	def getRelatedItemColumns(self):
		return 4

	def _readyInit(self):
		super()._readyInit()
		self.goldValue = int(self.getP("goldvalue"))


_R.reg("res://gd_core_items/Exclusive/StoneBadge.gd", Exclusive__StoneBadge)
_R.reg("StoneBadge", Exclusive__StoneBadge)
