# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__TwineBadge(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/TwineBadge.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusSpeed = None


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass

	def canAffect(self, item):
		return item.isCrafted() and (item.hasCooldown() or item.gainsBuffs())


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.bonusSpeed)
			item.changeAmplificiationChancePercent_allBuffs(self.getChance())


	def getRelatedItems(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.bonusSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/TwineBadge.gd", Exclusive__TwineBadge)
_R.reg("TwineBadge", Exclusive__TwineBadge)
