# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__MagicCollar(_R.C("res://gd_core_items/RangerCollar.gd")):

	resource_path = "res://gd_core_items/Exclusive/MagicCollar.gd"

	def _init_fields(self):
		super()._init_fields()
		self.mana = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		for item in _iter(self.affectedItems):
			self.connectForCombat(item, "attacked", "onWeaponAttacked")


	def onWeaponAttacked(self, damageRes):
		if damageRes.triggerOnHit():
			totalChance = self.getChance() * self.character().getLucky()
			if self.rollChance(totalChance):
				self.giveMana(self.mana, damageRes.event)
				self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Exclusive/MagicCollar.gd", Exclusive__MagicCollar)
_R.reg("MagicCollar", Exclusive__MagicCollar)
