# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__CapofBrilliance(_R.C("res://gd_core_items/LeatherHelm.gd")):

	resource_path = "res://gd_core_items/Exclusive/CapofBrilliance.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana = None


	def canAffect(self, item):
		return item.gainsStack(_R.C("CoreConst").Stack.Mana)


	def onPrepare(self):
		super().onPrepare()
		for item in _iter(self.getAffectedItems()):
			item.changeAmplificiationChancePercent(_R.C("CoreConst").EventType.Mana, self.getChance2())


	def onCombatStart(self):
		self.giveMana(self.mana)
		super().onCombatStart()

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Exclusive/CapofBrilliance.gd", Exclusive__CapofBrilliance)
_R.reg("CapofBrilliance", Exclusive__CapofBrilliance)
