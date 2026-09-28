# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Bow(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Bow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedWeapon = None
		self.activationParticles = None
		self.light = None


	def canAffect(self, item):
		return item.isWeapon()


	def prepare(self):
		self.affectedWeapon = self.getFirstAffectedItem()
		if self.affectedWeapon != None:
			self.connectForCombat(self.affectedWeapon, "attacked", "onWeaponAttacked")
		super().prepare()


	def onWeaponAttacked(self, damageRes):
		pass


	def combatEnd(self):
		super().combatEnd()
		self.affectedWeapon = None

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Bow.gd", Bow)
_R.reg("Bow", Bow)
_R.reg("Bow", Bow)
