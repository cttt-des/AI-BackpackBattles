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
		return (item.hasType(_R.C("CoreConst").Type.Nature) or 
				item.hasType(_R.C("CoreConst").Type.Dark) or 
				item.hasType(_R.C("CoreConst").Type.Ice))


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

		descr = self.insertCounter(descr, "n_nature", self.typesDict[_R.C("CoreConst").Type.Nature])
		descr = self.insertCounter(descr, "n_dark", self.typesDict[_R.C("CoreConst").Type.Dark])
		descr = self.insertCounter(descr, "n_ice", self.typesDict[_R.C("CoreConst").Type.Ice])

		return descr


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)

			leastStacks = self.getLeastStacks(self.numDebuffs, self.opponent(),
				_R.C("CoreConst").getDebuffs())

			if self.rollChance(self.getChance() * self.typesDict[_R.C("CoreConst").Type.Nature]):
				self.ctx.util.dictAdd(leastStacks, _R.C("CoreConst").EventType.Poison, self.bonusPoison)

			if self.rollChance(self.getChance() * self.typesDict[_R.C("CoreConst").Type.Dark]):
				self.ctx.util.dictAdd(leastStacks, _R.C("CoreConst").EventType.Blind, self.bonusBlind)

			if self.rollChance(self.getChance() * self.typesDict[_R.C("CoreConst").Type.Ice]):
				self.ctx.util.dictAdd(leastStacks, _R.C("CoreConst").EventType.Cold, self.bonusCold)

			for debuffType in _iter(leastStacks):
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
