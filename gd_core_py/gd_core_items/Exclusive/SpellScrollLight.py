# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpellScrollLight(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpellScrollLight.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedBonus = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def onPrepare(self):
		self.addSpeed(self.speedBonus * self.getNumAffectedItems())


	def doCooldownEffect(self):
		self.cleanseRandomDebuffs(1)
		if self.character().getDebuffStacks() == 0:
			self.heal()
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.speedBonus = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/SpellScrollLight.gd", Exclusive__SpellScrollLight)
_R.reg("SpellScrollLight", Exclusive__SpellScrollLight)
