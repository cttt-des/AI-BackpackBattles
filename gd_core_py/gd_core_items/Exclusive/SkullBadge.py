# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SkullBadge(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SkullBadge.gd"


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass

	def doCooldownEffect(self):
		self.inflictRandomDebuffs(1)
		self.activate()


	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 3

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/SkullBadge.gd", Exclusive__SkullBadge)
_R.reg("SkullBadge", Exclusive__SkullBadge)
