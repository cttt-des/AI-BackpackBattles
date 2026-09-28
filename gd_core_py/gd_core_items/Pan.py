# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Pan(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Pan.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusDamage = 0


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Food)


	def onPreCombatStart(self):
		self.addBonusDamage(self.getP1() * self.getNumAffectedItems())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Pan.gd", Pan)
_R.reg("Pan", Pan)
