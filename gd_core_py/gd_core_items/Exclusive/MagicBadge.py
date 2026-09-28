# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MagicBadge(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MagicBadge.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana = None


	def onAddToInventory(self):
		pass

	def onRemoveFromInventory(self):
		pass

	def canAffect(self, item):
		return item.gainsStack(_R.C("CoreConst").Stack.Mana)


	def onCombatStart(self):
		self.giveMana(self.mana)
		self.activate()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.changeAmplificiationChancePercent(_R.C("CoreConst").EventType.Mana, self.getChance())


	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 4

	def _readyInit(self):
		super()._readyInit()
		self.mana = self.getP("mana")


_R.reg("res://gd_core_items/Exclusive/MagicBadge.gd", Exclusive__MagicBadge)
_R.reg("MagicBadge", Exclusive__MagicBadge)
