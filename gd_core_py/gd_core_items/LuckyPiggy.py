# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class LuckyPiggy(_R.C("res://gd_core_items/Piggybank.gd")):

	resource_path = "res://gd_core_items/LuckyPiggy.gd"


	def canAffect(self, item):
		return item.canModifyChance()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusChance(self.getP3())


	def onCombatStart(self):
		self.giveLucky(self.getP2())
		self.activate()


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 5


	def explodeRandomly(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/LuckyPiggy.gd", LuckyPiggy)
_R.reg("LuckyPiggy", LuckyPiggy)
