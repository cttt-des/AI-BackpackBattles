# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpellScrollDark(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpellScrollDark.gd"

	def _init_fields(self):
		super()._init_fields()
		self._numActivations = 0
		self.speedBonus = None
		self.darkSpeed = None
		self.maxActivations = None

	@property
	def numActivations(self):
		return self._numActivations
	@numActivations.setter
	def numActivations(self, v):
		self._numActivations = int(v)

	def canAffect(self, item):
		return item.hasCooldown()


	def canAffect_secondary(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		self.numActivations = 0
		self.addSpeed(self.getNumAffectedItems(_H_3) * self.darkSpeed)


	def doCooldownEffect(self):
		self.numActivations += 1
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.speedBonus)
		self.giveStacks(self.character(), _H_2, 1)

		if self.numActivations == self.maxActivations:
			self.onAfterEffectFinished()
		else:
			self.activate()

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedBonus = _div__loc(self.getP('speed'), 100.0)
		self.darkSpeed = _div__loc(self.getP('speed_dark'), 100.0)
		self.maxActivations = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/SpellScrollDark.gd", Exclusive__SpellScrollDark)
_R.reg("SpellScrollDark", Exclusive__SpellScrollDark)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").EventType.Blind
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
