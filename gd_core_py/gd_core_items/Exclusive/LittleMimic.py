# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LittleMimic(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/LittleMimic.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numBuffs = None
		self.speedPerGold = None


	def canAffect(self, item):
		return True


	def getCounterValue(self):
		gold = 0
		if self.placed:
			for item in _iter(self.getAffectedItems()):
				gold += item.getPrice()
		else:
			for item in _iter(self.getAffectedItems_nocache()):
				gold += item.getPrice()
		return gold


	def onPrepare(self):
		self.addSpeed(self.getCounterValue() * self.speedPerGold)


	def doCooldownEffect(self):
		self.giveMostBuffs(self.numBuffs)
		self.activate()


	def onCalcTradeChance(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.numBuffs = int(self.getP("buffs"))
		self.speedPerGold = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/LittleMimic.gd", Exclusive__LittleMimic)
_R.reg("LittleMimic", Exclusive__LittleMimic)
