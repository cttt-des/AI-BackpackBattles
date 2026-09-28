# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FlameBadge(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/FlameBadge.gd"


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass

	def onCombatStart(self):
		self.giveHeat(self.getP1())
		self.consume()


	def onShopEntered(self):
		pass

	def getRelatedItems(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/FlameBadge.gd", Exclusive__FlameBadge)
_R.reg("FlameBadge", Exclusive__FlameBadge)
