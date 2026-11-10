# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__UniquelyUnique(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/UniquelyUnique.gd"

	def _init_fields(self):
		super()._init_fields()
		self.boosted = 0
		self.baseSpeed = None
		self.bonusSpeed = None


	def onBought(self):
		self.boosted = 2


	def getData(self):
		return self.boosted


	def setData(self, data):
		if data != None:
			self.boosted = data


	def canAffect(self, item):
		return item.hasCooldown()


	def canAffect_secondary(self, item):
		return (item.getRarity() == _H_1 or 
			item.isA(self.ctx.item_book.getDescriptor("Platin Customer Card")) or 
			item.isA(self.ctx.item_book.getDescriptor("Customer Card")))


	def onPrepare(self):
		affectedItems = self.getAffectedItems()
		if not (not affectedItems):
			affectedItems[0].addSpeed(self.baseSpeed + self.getNumAffectedItems(_H_2) * self.bonusSpeed)


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.ctx.item_book.getDescriptor("Customer Card"):
			self.boosted -= 1

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.baseSpeed = _div__loc(self.getP('speed'), 100.0)
		self.bonusSpeed = _div__loc(self.getP('speed2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/UniquelyUnique.gd", Exclusive__UniquelyUnique)
_R.reg("UniquelyUnique", Exclusive__UniquelyUnique)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Rarity.Unique
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
