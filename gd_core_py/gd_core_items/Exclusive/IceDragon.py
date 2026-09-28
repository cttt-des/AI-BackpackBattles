# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__IceDragon(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/IceDragon.gd"

	def _init_fields(self):
		super()._init_fields()
		self.gaveBlock = False
		self.coldOnHit = 0
		self.coldThreshold = 0
		self.damReduction = None


	def onPrepare(self):
		self.gaveBlock = False
		self.connectForCombat(self.opponent(), "character_cold_changed", "onOpponentColdChanged")


	def onOpponentColdChanged(self, amount, event):
		if not self.gaveBlock and self.opponent().getCold() >= self.coldThreshold:
			self.gaveBlock = True
			self.giveBlock(self.getBlock(), True, event)
			self.opponent().changeEffectDamageFactor( - self.damReduction)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.inflictCold(self.coldOnHit)

	def _readyInit(self):
		super()._readyInit()
		self.coldOnHit = self.getP("cold")
		self.coldThreshold = self.getP("coldt")
		self.damReduction = _div(self.getP('damfactor'), 100.0)


_R.reg("res://gd_core_items/Exclusive/IceDragon.gd", Exclusive__IceDragon)
_R.reg("IceDragon", Exclusive__IceDragon)
