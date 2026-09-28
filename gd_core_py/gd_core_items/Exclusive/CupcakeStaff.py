# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__CupcakeStaff(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/CupcakeStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.numBuffs = None
		self.damPerBuff = None


	def onPrepare(self):
		self.connectToCharacterBuffs("onBuffsChanged")


	def onPreDealDamage_early(self, damageRes):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveMostBuffs(self.numBuffs, event)


	def onBuffsChanged(self, amount, event):
		self.changeVaryingDamage(amount * self.damPerBuff)




















	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.numBuffs = int(self.getP("buffs"))
		self.damPerBuff = self.getP("dam")


_R.reg("res://gd_core_items/Exclusive/CupcakeStaff.gd", Exclusive__CupcakeStaff)
_R.reg("CupcakeStaff", Exclusive__CupcakeStaff)
