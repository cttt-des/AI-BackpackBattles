# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Ultima(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Ultima.gd"

	def _init_fields(self):
		super()._init_fields()
		self.typesDict = None
		self.speedPerSpell = None


	def canAffect(self, item):
		return (item.hasType(_H_1) or 
				item.hasType(_H_2) or 
				item.hasType(_H_3) or 
				item.hasType(_H_4) or 
				item.hasType(_H_5))


	def onPrepare(self):
		self.typesDict = self.countTypes(self.getAffectedItems())

		if self.typesDict[_H_5] > 0:
			self.addSpeed(self.speedPerSpell * self.typesDict[_H_5])


	def doCooldownEffect(self):

		if self.typesDict[_H_1] > 0:
			self.giveLucky(self.typesDict[_H_1] * self.getP("luck"))
			self.giveSpikes(self.typesDict[_H_1] * self.getP("spikes"))

		if self.typesDict[_H_2] > 0:
			self.giveBlock(self.typesDict[_H_2] * self.getBlock())
			self.inflictCold(self.typesDict[_H_2] * self.getP("cold"))

		if self.typesDict[_H_3] > 0:
			self.giveRegeneration(self.typesDict[_H_3] * self.getP("regen"))

		if self.typesDict[_H_4] > 0:
			self.stealRandomBuff(self.typesDict[_H_4])

		self.onAfterEffectFinished()


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if not self.placed:
			descr = descr.replace("$n_nature", "")
			descr = descr.replace("$n_ice", "")
			descr = descr.replace("$n_holy", "")
			descr = descr.replace("$n_dark", "")

			return descr

		self.typesDict = self.countTypes(self.getAffectedItems())

		descr = self.insertCounter(descr, "n_nature", self.typesDict[_H_1])
		descr = self.insertCounter(descr, "n_ice", self.typesDict[_H_2])
		descr = self.insertCounter(descr, "n_holy", self.typesDict[_H_3])
		descr = self.insertCounter(descr, "n_dark", self.typesDict[_H_4])


		return descr

	def _readyInit(self):
		super()._readyInit()
		self.speedPerSpell = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Ultima.gd", Exclusive__Ultima)
_R.reg("Ultima", Exclusive__Ultima)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Type.Holy
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
try:
    _H_5 = _R.C("CoreConst").Type.Spell
except AttributeError as _he:
    _H_5 = _HoistPending(_he)
