# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__PuzzlebagZ(_R.C("res://gd_core_items/Bag.gd")):

	resource_path = "res://gd_core_items/Exclusive/PuzzlebagZ.gd"


	def canApplyEffect(self, toItem):
		return toItem.inflictsDebuffs()


	def onPrepare(self):
		for item in _iter(self.getAffectedItemsInside()):
			item.changeAmplificiationChancePercent_allDebuffs(self.getChance())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/PuzzlebagZ.gd", Exclusive__PuzzlebagZ)
_R.reg("PuzzlebagZ", Exclusive__PuzzlebagZ)
