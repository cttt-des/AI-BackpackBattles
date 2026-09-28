# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpiritBells(_R.C("res://gd_core_items/LeatherHelm.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpiritBells.gd"

	def _init_fields(self):
		super()._init_fields()
		self.pets = {}
		self.boostedCompanions = 0
		self.buffFactor = None


	def onBought(self):
		self.boostedCompanions = 1


	def getData(self):
		return self.boostedCompanions


	def setData(self, data):
		if data != None:
			self.boostedCompanions = data


	def isAffectingDistinct(self, color=GD_DEFAULT):
		if color is GD_DEFAULT:
			color = _R.C("CoreConst").Affected.Primary
		return color == _R.C("CoreConst").Affected.Primary


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Pet)


	def getBuffDur(self):
		dur = self.getP_m("dur_base")
		dur += self.getP_m("dur_bonus") * self.getNumDistinctAffectedItems()
		return dur


	def doCooldownEffect(self):
		self.multiplyBuffsLimit(self.buffFactor, 1000)
		self.onAfterEffectFinished()


	def onItemRoll(self, descr):
		pass

	def onItemRolled(self, descr):
		pass

	def getRelatedItems(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.buffFactor = _div(self.getP('buffs'), 100.0)


_R.reg("res://gd_core_items/Exclusive/SpiritBells.gd", Exclusive__SpiritBells)
_R.reg("SpiritBells", Exclusive__SpiritBells)
