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
		return (item.getRarity() == _R.C("CoreConst").Rarity.Unique or 
			item.isA(self.ctx.item_book.getDescriptor("Platin Customer Card")) or 
			item.isA(self.ctx.item_book.getDescriptor("Customer Card")))


	def onPrepare(self):
		affectedItems = self.getAffectedItems()
		if not (not affectedItems):
			affectedItems[0].addSpeed(self.baseSpeed + self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary) * self.bonusSpeed)


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.ctx.item_book.getDescriptor("Customer Card"):
			self.boosted -= 1

	def _readyInit(self):
		super()._readyInit()
		self.baseSpeed = _div(self.getP('speed'), 100.0)
		self.bonusSpeed = _div(self.getP('speed2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/UniquelyUnique.gd", Exclusive__UniquelyUnique)
_R.reg("UniquelyUnique", Exclusive__UniquelyUnique)
