# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ChainWhip(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/ChainWhip.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffsPurged = 0


	def onPrepare(self):
		self.buffsPurged = 0
		self.connectToOpponentBuffs("onOpponentBuffsChanged")


	def onOpponentBuffsChanged(self, amount, event):
		if amount < 0:
			if isinstance(event.getOrigin(), _R.C("Item")) and event.getOrigin().character() == self.character():
				self.buffsPurged += - amount
				self.addBonusDamage( - amount * self.getP3())


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.removeRandomBuffs(self.getP1())
			if self.character().isBattleRaging():
				self.heal()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ChainWhip.gd", Exclusive__ChainWhip)
_R.reg("ChainWhip", Exclusive__ChainWhip)
