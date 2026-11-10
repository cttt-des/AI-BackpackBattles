# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HeartofDarkness_2(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/HeartofDarkness.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.regenNeeded = None
		self.numStealedBuffs = None
		self.fillAnimation = None


	def canAffect(self, item):
		return item.hasType(_H_2)


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")
		self.addSpeed(_div(self.getNumAffectedItems() * self.getP('darkspeed'), 100.0))


	def doCooldownEffect(self):
		self.stealRandomBuff(self.numStealedBuffs, None, _H_3.getBuffs(), _H_4)
		self.activate()


	def onRegenChanged(self, amount, event):
		if amount > 0 and not self.activated and self.character().getRegeneration() >= self.regenNeeded:
			self.setState(True, True)
			self.useRegeneration(self.regenNeeded, event)
			self.giveMaxHealth(self.getP_m("maxhealth"), event)
			self.giveEmpower(self.getP("empower"), event)
			self.opponent().reduceHealingEfficiency(_div(self.getP('healreduction'), 100.0))


	def onShopEntered(self):
		self.onStateChanged(False)


	def getTriggerPriority(self):
		return _H_1


	def onStateChanged(self, filled):
		if self.activated == filled:
			return
		self.activated = filled

		if filled:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.regenNeeded = int(self.getP("regent"))
		self.numStealedBuffs = int(self.getP("buffsteal"))


_R.reg("res://gd_core_items/HeartofDarkness.gd", HeartofDarkness_2)
_R.reg("HeartofDarkness", HeartofDarkness_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
_H_3 = _R.C("CoreConst")
try:
	_H_4 = _R.C("CoreConst").EventType.Regeneration
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
