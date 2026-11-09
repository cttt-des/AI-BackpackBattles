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
			color = _H_1
		return color == _H_1


	def canAffect(self, item):
		return item.hasType(_H_2)


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


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Pet
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
