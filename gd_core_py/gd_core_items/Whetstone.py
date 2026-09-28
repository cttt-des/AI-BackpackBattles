# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Whetstone(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Whetstone.gd"

	def _init_fields(self):
		super()._init_fields()
		self.dam = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusDamage(self.dam)
		self.activate()


	def _readyInit(self):
		super()._readyInit()
		self.dam = self.getP("dam")


_R.reg("res://gd_core_items/Whetstone.gd", Whetstone)
_R.reg("Whetstone", Whetstone)
