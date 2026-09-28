# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofAgility(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofAgility.gd"

	def _init_fields(self):
		super()._init_fields()
		self.usedStacks = {}
		self.bonusSpeed = None
		self.buffTimer = None
		self.refund = None

	amuletColor = Color(0.639216, 0.635294, 0.215686)

	def onPrepare(self):
		self.connectToCharacterBuffs("onBuffChanged")
		for buff in _iter(_R.C("CoreConst").getBuffs()):
			self.usedStacks[buff] = 0.0


	def canAffect(self, item):
		return item.hasCooldown()


	def onCombatStart(self):
		self.buffTimer.start(self.getP_m("dur"))
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.bonusSpeed)
		self.activate()


	def onBuffTimeout(self):
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.bonusSpeed)


	def onBuffChanged(self, amount, event):
		if amount < 0 and event.getParam("used", False):
			used = - amount
			buffType = event.getType()
			self.usedStacks[buffType] += used * self.refund
			toRefund = int(round(self.usedStacks[buffType]))

			if toRefund > 0:
				self.usedStacks[buffType] -= toRefund
				self.giveStacks(self.character(), buffType, toRefund, event)
				self.miniActivate()


	def onCombatEnd(self):
		self.buffTimer.stop()

	def _readyInit(self):
		super()._readyInit()
		self.bonusSpeed = _div(self.getP('speed'), 100.0)
		self.buffTimer = self.newItemTimer("BuffTimer", "onBuffTimeout", True)
		self.refund = _div(self.getP('refund'), 100.0)
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofAgility.gd", Exclusive__AmuletofAgility)
_R.reg("AmuletofAgility", Exclusive__AmuletofAgility)
