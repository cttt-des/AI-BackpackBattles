# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class VillainSword(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/VillainSword.gd"


	def canAffect(self, item):
		return item.canBeEmpowered() and item.descriptor.isMeleeWeapon()


	def onPreCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.reduceBonusDamage(self.getP1())
			self.addBonusDamage(self.getP2())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/VillainSword.gd", VillainSword)
_R.reg("VillainSword", VillainSword)
