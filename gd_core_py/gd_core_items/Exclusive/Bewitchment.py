# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Bewitchment(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Bewitchment.gd"

	def _init_fields(self):
		super()._init_fields()
		self.typesDict = None
		self.manaNeeded = None
		self.numDebuffs = None
		self.bonusPoison = None
		self.bonusBlind = None
		self.bonusCold = None


	def canAffect(self, item):
		return (item.hasType(_H_1) or 
				item.hasType(_H_2) or 
				item.hasType(_H_3))


	def onPrepare(self):
		self.typesDict = self.countTypes(self.getAffectedItems())


	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		if not self.placed:
			descr = descr.replace("$n_nature", "")
			descr = descr.replace("$n_dark", "")
			descr = descr.replace("$n_ice", "")
			return descr

		self.typesDict = self.countTypes(self.getAffectedItems())

		descr = self.insertCounter(descr, "n_nature", self.typesDict[_H_1])
		descr = self.insertCounter(descr, "n_dark", self.typesDict[_H_2])
		descr = self.insertCounter(descr, "n_ice", self.typesDict[_H_3])

		return descr


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)

			leastStacks = self.getLeastStacks(self.numDebuffs, self.opponent(),
				_H_4.getDebuffs())

			if self.rollChance(self.getChance() * self.typesDict[_H_1]):
				self.ctx.util.dictAdd(leastStacks, _H_5, self.bonusPoison)

			if self.rollChance(self.getChance() * self.typesDict[_H_2]):
				self.ctx.util.dictAdd(leastStacks, _H_6, self.bonusBlind)

			if self.rollChance(self.getChance() * self.typesDict[_H_3]):
				self.ctx.util.dictAdd(leastStacks, _H_7, self.bonusCold)

			for debuffType in (leastStacks if leastStacks.__class__ is list else _iter(leastStacks)):
				self.giveStacks(self.opponent(), debuffType, leastStacks[debuffType], event)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.numDebuffs = int(self.getP("debuffs"))
		self.bonusPoison = int(self.getP("poison"))
		self.bonusBlind = int(self.getP("blind"))
		self.bonusCold = int(self.getP("cold"))


_R.reg("res://gd_core_items/Exclusive/Bewitchment.gd", Exclusive__Bewitchment)
_R.reg("Bewitchment", Exclusive__Bewitchment)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Type.Ice
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
_H_4 = _R.C("CoreConst")
try:
    _H_5 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
    _H_5 = _HoistPending(_he)
try:
    _H_6 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
    _H_6 = _HoistPending(_he)
try:
    _H_7 = _R.C("CoreConst").EventType.Cold
except AttributeError as _he:
    _H_7 = _HoistPending(_he)
