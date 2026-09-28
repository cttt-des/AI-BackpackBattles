# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class MagicStaff(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/MagicStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaCost = None
		self.tempDamBonus = None
		self.permDamBonus = None


	def onPreDealDamage_early(self, damageRes):
		event = self.tryUseMana(self.manaCost)
		if event != None:
			damageRes.damage += self.tempDamBonus
			self.addBonusDamage(self.permDamBonus)

	def _readyInit(self):
		super()._readyInit()
		self.manaCost = self.getP1()
		self.tempDamBonus = self.getP2()
		self.permDamBonus = self.getP3()


_R.reg("res://gd_core_items/MagicStaff.gd", MagicStaff)
_R.reg("MagicStaff", MagicStaff)
