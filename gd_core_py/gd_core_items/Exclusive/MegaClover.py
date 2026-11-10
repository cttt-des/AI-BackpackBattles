# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MegaClover(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MegaClover.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stackTypes = None
		self.activated = False
		self.sales = None
		self._luckNeeded = 0
		self._numBuffs = 0

	@property
	def luckNeeded(self):
		return self._luckNeeded
	@luckNeeded.setter
	def luckNeeded(self, v):
		self._luckNeeded = int(v)
	@property
	def numBuffs(self):
		return self._numBuffs
	@numBuffs.setter
	def numBuffs(self, v):
		self._numBuffs = int(v)

	def onShopEntered(self):
		pass

	def onPrepare(self):
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckyChanged")
		self.activated = False


	def onLuckyChanged(self, amount, event):
		if not self.activated and self.character().getLucky() >= self.luckNeeded:
			self.activated = True

			self.giveRandomBuffs(self.numBuffs, event, self.stackTypes)
			self.activate()


	def onSaleRoll(self, _item):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.sales = _div(self.getP('sales'), 100.0)
		self.luckNeeded = self.getP("luckneeded")
		self.numBuffs = self.getP("buffs")
		self.stackTypes = _H_1.getBuffs()
		_erase(self.stackTypes, _H_2)



_R.reg("res://gd_core_items/Exclusive/MegaClover.gd", Exclusive__MegaClover)
_R.reg("MegaClover", Exclusive__MegaClover)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreConst")
try:
	_H_2 = _R.C("CoreConst").EventType.Lucky
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
