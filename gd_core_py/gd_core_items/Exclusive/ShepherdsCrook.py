# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ShepherdsCrook(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ShepherdsCrook.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		self.character().changeBuffProtectionChance(self.getChance())
		self.character().changeResistChance(_R.C("CoreConst").EventType.Blind, self.getChance2())
		self.character().changeResistChance(_R.C("CoreConst").EventType.Cold, self.getChance2())


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusDamage(self.getP1())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ShepherdsCrook.gd", Exclusive__ShepherdsCrook)
_R.reg("ShepherdsCrook", Exclusive__ShepherdsCrook)
