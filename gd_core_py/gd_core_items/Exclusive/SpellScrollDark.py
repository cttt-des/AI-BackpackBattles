# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpellScrollDark(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpellScrollDark.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.speedBonus = None
		self.darkSpeed = None
		self.maxActivations = None


	def canAffect(self, item):
		return item.hasCooldown()


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Dark)


	def onPrepare(self):
		self.numActivations = 0
		self.addSpeed(self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary) * self.darkSpeed)


	def doCooldownEffect(self):
		self.numActivations += 1
		for item in _iter(self.getAffectedItems()):
			item.addSpeed(self.speedBonus)
		self.giveStacks(self.character(), _R.C("CoreConst").EventType.Blind, 1)

		if self.numActivations == self.maxActivations:
			self.onAfterEffectFinished()
		else:
			self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = _div(self.getP('speed'), 100.0)
		self.darkSpeed = _div(self.getP('speed_dark'), 100.0)
		self.maxActivations = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/SpellScrollDark.gd", Exclusive__SpellScrollDark)
_R.reg("SpellScrollDark", Exclusive__SpellScrollDark)
