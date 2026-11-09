# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BuytheHolyLight(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/BuytheHolyLight.gd"

	def _init_fields(self):
		super()._init_fields()
		self.oilLamp = None
		self.djinnLamp = None
		self.holySpeed = None
		self.salesChance = None


	def canAffect(self, item):
		return (item.hasType(_H_1) and item.hasCooldown()) or self.isLamp(item)


	def canAffect_global(self, item):
		return self.isLamp(item)


	def isLamp(self, item):
		return item.isA(self.oilLamp) or item.isA(self.djinnLamp)


	def onItemInstantiated(self, item):
		if (self.placed and 
			self.isLamp(item) and 
			item.isOwnable()):
				item.addDynamicType(_H_1, self)


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.holySpeed)


	def onSaleRoll(self, item):
		pass

	def onAddToInventory(self):
		self.ctx.defer(self, "onAddToInventory_deferred", [])


	def onAddToInventory_deferred(self):
		pass

	def onRemoveFromInventory(self):
		self.ctx.defer(self, "onRemoveFromInventory_deferred", [])


	def onRemoveFromInventory_deferred(self):
		pass

	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.oilLamp = self.ctx.item_book.getDescriptor("Oil Lamp")
		self.djinnLamp = self.ctx.item_book.getDescriptor("Djinn Lamp")
		self.holySpeed = _div(self.getP('speed'), 100.0)
		self.salesChance = _div(self.getP('sales'), 100.0)


_R.reg("res://gd_core_items/Exclusive/BuytheHolyLight.gd", Exclusive__BuytheHolyLight)
_R.reg("BuytheHolyLight", Exclusive__BuytheHolyLight)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
