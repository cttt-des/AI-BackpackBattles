# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SewingCase(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/SewingCase.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusSpeed = None


	def canApplyEffect(self, toItem):
		return toItem.isCrafted() and (toItem.hasCooldown() or toItem.gainsBuffs())


	def onPrepare(self):
		for item in _iter(self.getAffectedItemsInside()):
			item.addSpeed(self.bonusSpeed)
			item.changeAmplificiationChancePercent_allBuffs(self.getChance())

	def _readyInit(self):
		super()._readyInit()
		self.bonusSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/SewingCase.gd", Exclusive__SewingCase)
_R.reg("SewingCase", Exclusive__SewingCase)
