# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__InnerPower(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/InnerPower.gd"

	def _init_fields(self):
		super()._init_fields()
		self.healAmpAcc = 0.0
		self.speedAcc = 0.0
		self.luck = None
		self.empower = None
		self.healAmpPerLuck = None
		self.speedPerEmpower = None
		self.healAmpMax = None
		self.speedMax = None


	def canAffect(self, item):
		return item.hasCooldown() or item.canHealOrLifesteal()


	def onCombatStart(self):
		self.giveLucky(self.luck)
		self.giveEmpower(self.empower)
		self.activate()


	def onPrepare(self):
		self.healAmpAcc = 0
		self.speedAcc = 0
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckChanged")
		self.connectForCombat(self.character(), "character_empower_changed", "onEmpowerChanged")


	def onLuckChanged(self, amount, event):
		before = min(self.healAmpAcc, self.healAmpMax)
		dif = amount * self.healAmpPerLuck
		self.healAmpAcc += dif

		healAmpToGive = min(self.healAmpAcc, self.healAmpMax) - before
		if healAmpToGive != 0:
			for item in _iter(self.getAffectedItems()):
				item.changeHealAmp(healAmpToGive)



	def onEmpowerChanged(self, amount, event):
		before = min(self.speedAcc, self.speedMax)
		dif = amount * self.speedPerEmpower
		self.speedAcc += dif

		speedToGive = min(self.speedAcc, self.speedMax) - before
		if speedToGive != 0:
			for item in _iter(self.getAffectedItems()):
				item.addSpeed(speedToGive)


	def _readyInit(self):
		super()._readyInit()
		self.luck = int(self.getP("luck"))
		self.empower = int(self.getP("empower"))
		self.healAmpPerLuck = _div(self.getP('healamp'), 100.0)
		self.speedPerEmpower = _div(self.getP('speed'), 100.0)
		self.healAmpMax = _div(self.getP('max1'), 100.0)
		self.speedMax = _div(self.getP('max2'), 100.0)


_R.reg("res://gd_core_items/Exclusive/InnerPower.gd", Exclusive__InnerPower)
_R.reg("InnerPower", Exclusive__InnerPower)
