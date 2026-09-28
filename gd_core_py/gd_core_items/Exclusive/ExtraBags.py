# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ExtraBags(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ExtraBags.gd"

	def _init_fields(self):
		super()._init_fields()
		self.freeSlotSpeed = None
		self.salesChance = None
		self.bagWeight = None


	def canAffect(self, item):
		return item.hasCooldown()


	def affectsEmpty(self, color):
		return color == _R.C("CoreConst").Affected.Secondary


	def canAffect_secondary(self, item):
		return False


	def onPrepare(self):
		freeSlotSpeed_total = self.getNumEmptyAffectedCells(_R.C("CoreConst").Affected.Secondary) * self.freeSlotSpeed
		if freeSlotSpeed_total > 0:
			for item in _iter(self.getAffectedItems()):
				item.addSpeed(freeSlotSpeed_total)


	def onSaleRoll(self, item):
		pass

	def onItemRoll(self, descr):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.freeSlotSpeed = _div(self.getP('speed'), 100.0)
		self.salesChance = _div(self.getP('sales'), 100.0)
		self.bagWeight = self.getP("bagweight")


_R.reg("res://gd_core_items/Exclusive/ExtraBags.gd", Exclusive__ExtraBags)
_R.reg("ExtraBags", Exclusive__ExtraBags)
