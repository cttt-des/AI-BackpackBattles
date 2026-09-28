# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SmellyBarrier(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SmellyBarrier.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockAcc = 0
		self.boostedGarlic = 0
		self.garlicDescriptor = None
		self.garlicBlockBonus = None
		self.blockForPoison = None
		self.poisonForBlock = None


	def canAffect(self, item):
		return item.isA(self.garlicDescriptor) or item.canBlock()


	def onBought(self):
		self.boostedGarlic = 3


	def getData(self):
		return self.boostedGarlic


	def setData(self, data):
		if data != None:
			self.boostedGarlic = data


	def onPrepare(self):
		self.blockAcc = 0

		for item in _iter(self.getAffectedItems()):
			if item.isA(self.garlicDescriptor):
				item.addBonusBlock(self.garlicBlockBonus)
			if item.canBlock():
				self.connectForCombat(item, "gave_block", "onItemGaveBlock")


	def onItemGaveBlock(self, amount, event):
		self.blockAcc += amount
		poison = _div(self.blockAcc, self.blockForPoison)
		self.blockAcc %= self.blockForPoison
		if poison > 0:
			self.inflictPoison(poison * self.poisonForBlock, event)
			self.activate()


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.garlicDescriptor:
			self.boostedGarlic -= 1


	def _readyInit(self):
		super()._readyInit()
		self.garlicDescriptor = self.ctx.item_book.getDescriptor("Garlic")
		self.garlicBlockBonus = int(self.getP("blockbonus"))
		self.blockForPoison = int(self.getP("blockt"))
		self.poisonForBlock = int(self.getP("poison"))


_R.reg("res://gd_core_items/Exclusive/SmellyBarrier.gd", Exclusive__SmellyBarrier)
_R.reg("SmellyBarrier", Exclusive__SmellyBarrier)
