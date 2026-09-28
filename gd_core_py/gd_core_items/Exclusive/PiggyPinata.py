# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PiggyPinata(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/PiggyPinata.gd"

	def _init_fields(self):
		super()._init_fields()
		self.piggybankDescriptor = None


	def onItemRoll(self, descr):
		pass

	def canAffect(self, item):
		return item.canDamage()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addCritChancePercent(self.getChance())


	def canAffect_global(self, item):
		return item.isA(self.piggybankDescriptor)

	def _readyInit(self):
		super()._readyInit()
		self.piggybankDescriptor = self.ctx.item_book.getDescriptor("Piggybank")


_R.reg("res://gd_core_items/Exclusive/PiggyPinata.gd", Exclusive__PiggyPinata)
_R.reg("PiggyPinata", Exclusive__PiggyPinata)
