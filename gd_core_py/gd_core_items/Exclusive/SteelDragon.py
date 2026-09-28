# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SteelDragon(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/SteelDragon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.reflectStacks = None
		self.blockFactor = None
		self.dam = None


	def canAffect(self, item):
		return item.canBeEmpowered() or item.canBlock()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_R.C("CoreConst").EventType.Block, self.blockFactor)


	def onPreCombatStart(self):
		self.giveReflectStacks(self.reflectStacks)


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusDamage(self.dam)
		self.activate(None, False)

	def _readyInit(self):
		super()._readyInit()
		self.reflectStacks = int(self.getP("reflect"))
		self.blockFactor = _div(self.getP('blockfactor'), 100.0)
		self.dam = self.getP("dam")


_R.reg("res://gd_core_items/Exclusive/SteelDragon.gd", Exclusive__SteelDragon)
_R.reg("SteelDragon", Exclusive__SteelDragon)
