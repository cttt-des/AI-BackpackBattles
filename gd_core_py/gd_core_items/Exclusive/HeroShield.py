# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__HeroShield(_R.C("res://gd_core_items/WoodenBuckler.gd")):

	resource_path = "res://gd_core_items/Exclusive/HeroShield.gd"

	def _init_fields(self):
		super()._init_fields()
		self.flatDam = None
		self.damFactor = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusDamage(self.flatDam)
			item.addBonusDamageFactor(self.damFactor)
		self.activate()


	def _readyInit(self):
		super()._readyInit()
		self.flatDam = self.getP("dam")
		self.damFactor = _div(self.getP('damfactor'), 100.0)


_R.reg("res://gd_core_items/Exclusive/HeroShield.gd", Exclusive__HeroShield)
_R.reg("HeroShield", Exclusive__HeroShield)
