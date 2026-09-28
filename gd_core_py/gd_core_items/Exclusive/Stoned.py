# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Stoned(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Stoned.gd"

	def _init_fields(self):
		super()._init_fields()
		self.protectionActive = False
		self.boostedStones = 0
		self.damReductionGiven = 0.0
		self.stoneDescriptor = None
		self.stoneGolemDescriptor = None
		self.stoneArmorDescriptor = None
		self.blockFactor = None
		self.damReduction = None


	def getData(self):
		return self.boostedStones


	def setData(self, data):
		if data != None:
			self.boostedStones = data


	def onBought(self):
		self.boostedStones = 4


	def canBlock(self):
		return True


	def canAffect_global(self, item):
		return item.hasTag(_R.C("CoreConst").Tag.Stone) or item.isA(self.stoneGolemDescriptor)


	def onPrepare(self):

		self.connectForCombat(self.character(), "character_block_changed", "onBlockChanged")
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")
		self.protectionActive = False
		self.damReductionGiven = 0.0

		for item in _iter(self.inventory.getItems()):
			if self.canAffect_global(item):
				self.connectForCombat(item, "attacked", "onStoneAttacked")


	def onStoneAttacked(self, damageRes):
		if damageRes.hasHit():
			self.giveBlock(ceil(damageRes.damage * self.blockFactor), True, damageRes.event)
			self.miniActivate()


	def onDamaged(self, _healthChange, _event):
		self.checkBlock()


	def onBlockChanged(self, _amount, _event):
		self.checkBlock()


	def checkBlock(self):
		if self.protectionActive:
			if self.character().getBlock() == 0:
				self.protectionActive = False

				self.character().changeDamageResistance( - self.damReduction)
				self.damReductionGiven -= self.damReduction
		else:
			if self.character().getBlock() > 0:
				self.protectionActive = True

				self.character().changeDamageResistance(self.damReduction)
				self.damReductionGiven += self.damReduction






	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		if descr == self.stoneDescriptor:
			self.boostedStones -= 1

	def _readyInit(self):
		super()._readyInit()
		self.stoneDescriptor = self.ctx.item_book.getDescriptor("Stone")
		self.stoneGolemDescriptor = self.ctx.item_book.getDescriptor("Stone Golem")
		self.stoneArmorDescriptor = self.ctx.item_book.getDescriptor("Stone Armor")
		self.blockFactor = _div(self.getP('blockfordam'), 100.0)
		self.damReduction = self.getP("damreduction")


_R.reg("res://gd_core_items/Exclusive/Stoned.gd", Exclusive__Stoned)
_R.reg("Stoned", Exclusive__Stoned)
