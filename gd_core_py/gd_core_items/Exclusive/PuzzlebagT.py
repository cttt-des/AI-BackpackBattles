# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PuzzlebagT(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/PuzzlebagT.gd"

	def _init_fields(self):
		super()._init_fields()
		self.usedStacks = {}
		self.affectedInside = []
		self.refund = None


	def canApplyEffect(self, toItem):
		return toItem.usesBuffs()


	def onPrepare(self):
		self.affectedInside = self.getAffectedItemsInside()
		if not (not self.affectedInside):
			self.connectToCharacterBuffs("onBuffChanged")
			for buff in _iter(_R.C("CoreConst").getBuffs()):
				self.usedStacks[buff] = 0.0


	def onBuffChanged(self, amount, event):
		if (amount < 0 and event.getParam("used", False) and 
			event.origin in self.affectedInside):
			used = - amount
			buffType = event.getType()
			self.usedStacks[buffType] += used * self.refund
			toRefund = int(round(self.usedStacks[buffType]))

			if toRefund > 0:
				self.usedStacks[buffType] -= toRefund
				self.giveStacks(self.character(), buffType, toRefund, event)
				self.miniActivate()


	def getBagEffect(self, number):
		descr = self.ctx.util.tra(self.getName() + "_BAGEFFECT")
		descr = self.insertParameter(descr, "p_buff", self.getP("buff") * number)
		return descr

	def _readyInit(self):
		super()._readyInit()
		self.refund = _div(self.getP('buff'), 100.0)


_R.reg("res://gd_core_items/Exclusive/PuzzlebagT.gd", Exclusive__PuzzlebagT)
_R.reg("PuzzlebagT", Exclusive__PuzzlebagT)
