# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__CriticalPoison(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/CriticalPoison.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageAcc = 0
		self.damagePerPoison = 0
		self.poison = 0


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		for weapon in _iter(self.getAffectedItems()):
			self.connectForCombat(weapon, "attacked", "onWeaponAttacked")
		self.connectForCombat(self.character(), "character_lucky_changed", "onLuckChanged")


	def onWeaponAttacked(self, damageRes):
		if damageRes.hasHit():
			self.damageAcc += damageRes.damage

			poisonStacks = _div(self.damageAcc, self.damagePerPoison)
			if poisonStacks > 0:
				self.inflictPoison(poisonStacks * self.poison, damageRes.event)
				self.damageAcc %= self.damagePerPoison
				self.miniActivate()


	def onLuckChanged(self, amount, event):
		self.opponent().changePoisonCritChancePercent(amount * self.getChance())

	def _readyInit(self):
		super()._readyInit()
		self.damagePerPoison = self.getP("damt")
		self.poison = self.getP("poison")


_R.reg("res://gd_core_items/Exclusive/CriticalPoison.gd", Exclusive__CriticalPoison)
_R.reg("CriticalPoison", Exclusive__CriticalPoison)
