# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FurciferPrime(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/FurciferPrime.gd"

	def _init_fields(self):
		super()._init_fields()
		self.active = False
		self.salesChance = None
		self.goldCost = None


	def getData(self):
		return self.active


	def setData(self, data):
		self.active = data


	def onSwitchToCombat(self):
		self.active = False


	def onShopEntered(self):
		pass

	def onSaleRoll(self, _item):
		pass

	def onSaleRoll_storage(self, _item):
		self.onSaleRoll(_item)


	def getGatedDescriptor(self, rarity):
		pass

	def onGateItemRoll(self):
		if self.active:
			super().onGateItemRoll()


	def onGateItemRoll_storage(self):
		self.onGateItemRoll()

	def _readyInit(self):
		super()._readyInit()
		self.salesChance = _div(self.getP('sales'), 100.0)
		self.goldCost = int(self.getP("gold"))


_R.reg("res://gd_core_items/Exclusive/FurciferPrime.gd", Exclusive__FurciferPrime)
_R.reg("FurciferPrime", Exclusive__FurciferPrime)
