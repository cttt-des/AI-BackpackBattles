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
		return item.gainsStack(_H_1)


	def onCombatStart(self):
		self.giveMana(self.mana)
		self.activate()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.changeAmplificiationChancePercent(_H_2, self.getChance())


	def getRelatedItems(self):
		pass

	def getRelatedItemColumns(self):
		return 4

	def _readyInit(self):
		super()._readyInit()
		self.mana = self.getP("mana")


_R.reg("res://gd_core_items/Exclusive/MagicBadge.gd", Exclusive__MagicBadge)
_R.reg("MagicBadge", Exclusive__MagicBadge)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Stack.Mana
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Mana
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
