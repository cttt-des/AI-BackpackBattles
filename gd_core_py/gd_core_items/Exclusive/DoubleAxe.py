# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DoubleAxe(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/DoubleAxe.gd"

	def _init_fields(self):
		super()._init_fields()
		self.enteredRage = False


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():

			if self.enteredRage:
				self.addBonusDamage(self.getP2())
			else:
				self.addBonusDamage(self.getP1())


	def onPrepare(self):
		self.enteredRage = False
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")


	def onBattleRageStarted(self, event):
		self.doCooldownEffect()
		self.enteredRage = True

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/DoubleAxe.gd", Exclusive__DoubleAxe)
_R.reg("DoubleAxe", Exclusive__DoubleAxe)
