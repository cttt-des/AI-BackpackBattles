# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class HeroSword(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/HeroSword.gd"


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.addBonusDamage(self.getP1())
		self.activate(None, False, False, self.ActivationAni.Jump)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/HeroSword.gd", HeroSword)
_R.reg("HeroSword", HeroSword)
