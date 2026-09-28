# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__StoneGloves(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/StoneGloves.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedReduction = None
		self.damBonusFactor = None


	def canAffect(self, item):
		return item.canBeEmpowered()


	def onPrepare(self):
		for weapon in _iter(self.getAffectedItems()):
			self.connectForCombat(weapon, "attacked", "onWeaponAttacked")


	def onCombatStart(self):
		for item in _iter(self.getAffectedItems()):
			item.reduceSpeed(self.speedReduction)
			item.addBonusDamageFactor(self.damBonusFactor)
		self.activate()


	def onWeaponAttacked(self, damageRes):
		if damageRes.hasHit():
			self.giveBlock(self.getBlock(), True, damageRes.event)
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.speedReduction = _div(self.getP('speedreduction'), 100.0)
		self.damBonusFactor = _div(self.getP('dambonus'), 100.0)


_R.reg("res://gd_core_items/Exclusive/StoneGloves.gd", Exclusive__StoneGloves)
_R.reg("StoneGloves", Exclusive__StoneGloves)
