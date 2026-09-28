# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Fedora(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Fedora.gd"

	def _init_fields(self):
		super()._init_fields()
		self.luckPerNature = None
		self.luckPerTreasure = None
		self.luckNeeded = None
		self.numBuffs = None
		self.bonusChance = None


	def canAffect(self, item):
		return item.isTreasure() or item.hasType(_R.C("CoreConst").Type.Nature)


	def canAffect_secondary(self, item):
		return item.canModifyChance()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Secondary)):
			item.addBonusChance(self.bonusChance)


	def onCombatStart(self):
		numNature = 0
		numTreasure = 0
		for item in _iter(self.getAffectedItems()):
			if item.isTreasure():
				numTreasure += 1
			if item.hasType(_R.C("CoreConst").Type.Nature):
				numNature += 1

		self.giveLucky(numNature * self.luckPerNature + numTreasure * self.luckPerTreasure)
		self.activate()


	def doCooldownEffect(self):
		if self.character().getLucky() >= self.luckNeeded:
			event = self.useLucky(self.luckNeeded)
			buffs = _R.C("CoreConst").getBuffs()
			_erase(buffs, _R.C("CoreConst").EventType.Lucky)
			self.stealRandomBuff(self.numBuffs, event, buffs)
		self.activate()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 5

	def _readyInit(self):
		super()._readyInit()
		self.luckPerNature = int(self.getP("luck"))
		self.luckPerTreasure = int(self.getP("luck2"))
		self.luckNeeded = int(self.getP("luckt"))
		self.numBuffs = int(self.getP("buffs"))
		self.bonusChance = self.getP("chance")


_R.reg("res://gd_core_items/Exclusive/Fedora.gd", Exclusive__Fedora)
_R.reg("Fedora", Exclusive__Fedora)
