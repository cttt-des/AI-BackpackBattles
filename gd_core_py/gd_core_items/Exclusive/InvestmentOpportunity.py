# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__InvestmentOpportunity(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/InvestmentOpportunity.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItemsDict = {}
		self.healthAcc = 0.0


	def onShopEntered(self):
		self.giveGold(self.getP1())


	def canAffect(self, item):
		return item.usesBuffs()


	def onPrepare(self):
		self.healthAcc = 0
		self.affectedItemsDict.clear()
		for item in _iter(self.getAffectedItems()):
			self.affectedItemsDict[item] = True
		self.connectToCharacterBuffs("onBuffChanged")


	def onBuffChanged(self, amount, event):
		if event.getOrigin() in self.affectedItemsDict:
			if amount < 0 and event.getParam("used", False):
				self.healthAcc += abs(amount) * self.getP_m("maxhealth")
				health = round(self.healthAcc)
				self.healthAcc -= health
				self.giveMaxHealth(health, event)
				self.miniActivate()


	def getShopPriority(self):
		return _R.C("CoreConst").Priority.Lowest

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/InvestmentOpportunity.gd", Exclusive__InvestmentOpportunity)
_R.reg("InvestmentOpportunity", Exclusive__InvestmentOpportunity)
