# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MageHat(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/MageHat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana = None
		self.damReduction = None


	def canAffect(self, item):
		return item.getRarity() == _R.C("CoreConst").Rarity.Common


	def canAffect_secondary(self, item):
		return item.getRarity() == _R.C("CoreConst").Rarity.Rare


	def canAffect_tertiary(self, item):
		return item.getRarity() == _R.C("CoreConst").Rarity.Epic


	def onCombatStart(self):
		numCommon = self.getNumAffectedItems(_R.C("CoreConst").Affected.Primary)
		numRare = self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary)
		numEpic = self.getNumAffectedItems(_R.C("CoreConst").Affected.Tertiary)
		if numCommon > 0:
			self.giveBlock(self.getBlock() * numCommon)
		if numRare > 0:
			self.giveMana(self.mana * numRare)
		if numEpic > 0:
			self.opponent().changeEffectDamageFactor( - self.damReduction * numEpic)

		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP("mana"))
		self.damReduction = _div(self.getP('damreduction'), 100.0)


_R.reg("res://gd_core_items/Exclusive/MageHat.gd", Exclusive__MageHat)
_R.reg("MageHat", Exclusive__MageHat)
