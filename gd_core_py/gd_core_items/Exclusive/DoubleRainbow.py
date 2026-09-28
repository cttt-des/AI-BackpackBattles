# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DoubleRainbow(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DoubleRainbow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedPerHolyItem = None


	def canAffect(self, item):
		return item.gainsBuffs()


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def doCooldownEffect(self):
		self.giveRandomBuffs(1)
		self.activate()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.changeAmplificiationChancePercent_allBuffs(self.getChance())

		self.addSpeed(self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary) * self.speedPerHolyItem)

	def _readyInit(self):
		super()._readyInit()
		self.speedPerHolyItem = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/DoubleRainbow.gd", Exclusive__DoubleRainbow)
_R.reg("DoubleRainbow", Exclusive__DoubleRainbow)
