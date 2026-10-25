# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class MoonShield_2(_R.C("res://gd_core_items/Shield.gd")):

	resource_path = "res://gd_core_items/MoonShield.gd"

	def _init_fields(self):
		super()._init_fields()
		self._blockAcc = 0
		self._blockForMana = 0

	@property
	def blockAcc(self):
		return self._blockAcc
	@blockAcc.setter
	def blockAcc(self, v):
		self._blockAcc = int(v)
	@property
	def blockForMana(self):
		return self._blockForMana
	@blockForMana.setter
	def blockForMana(self, v):
		self._blockForMana = int(v)

	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_R.C('CoreConst').EventType.Block, _div(self.getP3(), 100.0))
			self.connectForCombat(item, "gave_block", "onItemGaveBlock")
		self.blockAcc = 0


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		self.activate()


	def onItemGaveBlock(self, amount, event):
		self.blockAcc += amount
		mana = _div(self.blockAcc, self.blockForMana)
		self.blockAcc %= self.blockForMana
		if mana > 0:
			self.giveMana(mana, event)
			self.miniActivate()



	def canBlockDamageRes(self, damageRes):
		return damageRes.triggerOnAttacked()

	def _readyInit(self):
		super()._readyInit()
		self.blockForMana = self.getP4()


_R.reg("res://gd_core_items/MoonShield.gd", MoonShield_2)
_R.reg("MoonShield", MoonShield_2)
