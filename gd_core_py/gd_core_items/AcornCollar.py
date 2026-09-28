# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class AcornCollar(_R.C("res://gd_core_items/RangerCollar.gd")):

	resource_path = "res://gd_core_items/AcornCollar.gd"


	def canAffect(self, item):
		return item.canDamage()


	def onPrepare(self):
		if not (not self.affectedItems):
			self.connectForCombat(self.character(), "character_lucky_changed", "onLuckyChanged")


	def onLuckyChanged(self, amount, _event):
		for item in _iter(self.affectedItems):
			item.changeCritChancePercent(amount * self.getChance())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/AcornCollar.gd", AcornCollar)
_R.reg("AcornCollar", AcornCollar)
