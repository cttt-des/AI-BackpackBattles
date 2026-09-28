# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Halberd(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Halberd.gd"

	def _init_fields(self):
		super()._init_fields()
		self.totalBlockRemoval = 0
		self.dam = None
		self.blockRemoval = None
		self.blockFactor = None


	def canBlock(self):
		return True


	def affectsEmpty(self, color):
		return True


	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		self.totalBlockRemoval = self.blockRemoval * (self.getNumAffectedItems() + self.getNumEmptyAffectedCells())

		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_R.C("CoreConst").EventType.Block, self.blockFactor)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.addBonusDamage(self.dam)


	def onPreDealDamage_late(self, damageRes):

		curBlock = self.opponent().getBlock()
		toRemove = min(curBlock, self.totalBlockRemoval)
		self.removeBlock(toRemove, damageRes.event)
		toGive = self.totalBlockRemoval - toRemove
		if toGive > 0:
			self.giveBlock(toGive, True, damageRes.event)

	def _readyInit(self):
		super()._readyInit()
		self.dam = self.getP("dam")
		self.blockRemoval = self.getP("blockremoval")
		self.blockFactor = _div(self.getP('blockfactor'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Halberd.gd", Exclusive__Halberd)
_R.reg("Halberd", Exclusive__Halberd)
