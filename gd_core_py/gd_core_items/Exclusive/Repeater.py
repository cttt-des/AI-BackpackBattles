# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Repeater(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Repeater.gd"


	def canAffect(self, item):
		return item.hasStartofBattle()


	def doCooldownEffect(self):
		for item in _iter(self.getAffectedItems()):
			item.repeatCombatStart()
		self.onAfterEffectFinished()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Repeater.gd", Exclusive__Repeater)
_R.reg("Repeater", Exclusive__Repeater)
