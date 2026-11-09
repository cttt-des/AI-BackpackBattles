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
		return item.isTreasure() or item.hasType(_H_3)


	def canAffect_secondary(self, item):
		return item.canModifyChance()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems(_H_4)):
			item.addBonusChance(self.bonusChance)


	def onCombatStart(self):
		numNature = 0
		numTreasure = 0
		for item in _iter(self.getAffectedItems()):
			if item.isTreasure():
				numTreasure += 1
			if item.hasType(_H_3):
				numNature += 1

		self.giveLucky(numNature * self.luckPerNature + numTreasure * self.luckPerTreasure)
		self.activate()


	def doCooldownEffect(self):
		if self.character().getLucky() >= self.luckNeeded:
			event = self.useLucky(self.luckNeeded)
			buffs = _H_1.getBuffs()
			_erase(buffs, _H_5)
			self.stealRandomBuff(self.numBuffs, event, buffs)
		self.activate()


	def getTriggerPriority(self):
		return _H_2 + 5

	def _readyInit(self):
		super()._readyInit()
		self.luckPerNature = int(self.getP("luck"))
		self.luckPerTreasure = int(self.getP("luck2"))
		self.luckNeeded = int(self.getP("luckt"))
		self.numBuffs = int(self.getP("buffs"))
		self.bonusChance = self.getP("chance")


_R.reg("res://gd_core_items/Exclusive/Fedora.gd", Exclusive__Fedora)
_R.reg("Fedora", Exclusive__Fedora)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreConst")
try:
    _H_2 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Type.Nature
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
try:
    _H_5 = _R.C("CoreConst").EventType.Lucky
except AttributeError as _he:
    _H_5 = _HoistPending(_he)
