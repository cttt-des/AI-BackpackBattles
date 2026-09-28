# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__VineweaveBasket(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/VineweaveBasket.gd"

	def _init_fields(self):
		super()._init_fields()
		self.salesRound1 = None
		self.salesRound2 = None
		self.salesChance = None
		self.salesParticles = None


	def canApplyEffect(self, toItem):
		return toItem.hasType(_R.C("CoreConst").Type.Nature)


	def onPrepare(self):
		healAmp = self.getP("healamp")
		healAmp += self.getP("ampbonus") * self.getNumAffectedInside()
		self.character().addHealingEfficiency(_div(healAmp, 100.0))


	def onShopOpened(self):
		if self.ctx.cur_round == self.salesRound1 or self.ctx.cur_round == self.salesRound2:
			pass


	def onSaleRoll(self, _item):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.salesRound1 = int(self.getP("round1"))
		self.salesRound2 = int(self.getP("round2"))
		self.salesChance = _div(self.getP('sales'), 100.0)
		if self.ownerType == _R.C("CoreConst").Owner.PlayerInventory:
			pass



_R.reg("res://gd_core_items/Exclusive/VineweaveBasket.gd", Exclusive__VineweaveBasket)
_R.reg("VineweaveBasket", Exclusive__VineweaveBasket)
