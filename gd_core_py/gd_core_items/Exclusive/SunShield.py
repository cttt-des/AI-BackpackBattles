# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SunShield(_R.C("res://gd_core_items/Shield.gd")):

	resource_path = "res://gd_core_items/Exclusive/SunShield.gd"

	def _init_fields(self):
		super()._init_fields()
		self._blockAcc = 0
		self._bonusDamagePerTick = 0
		self._damagePerTick = 0
		self._blockPerTick = 0
		self.activationParticles = None

	@property
	def blockAcc(self):
		return self._blockAcc
	@blockAcc.setter
	def blockAcc(self, v):
		self._blockAcc = int(v)
	@property
	def bonusDamagePerTick(self):
		return self._bonusDamagePerTick
	@bonusDamagePerTick.setter
	def bonusDamagePerTick(self, v):
		self._bonusDamagePerTick = int(v)
	@property
	def damagePerTick(self):
		return self._damagePerTick
	@damagePerTick.setter
	def damagePerTick(self, v):
		self._damagePerTick = int(v)
	@property
	def blockPerTick(self):
		return self._blockPerTick
	@blockPerTick.setter
	def blockPerTick(self, v):
		self._blockPerTick = int(v)

	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "gave_block", "onItemGaveBlock")
		self.bonusDamagePerTick = 0


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		self.activate()


	def onItemGaveBlock(self, amount, event):
		self.blockAcc += amount
		ticks = _div(self.blockAcc, self.blockPerTick)
		if ticks > 0:
			self.blockAcc %= self.blockPerTick
			dam = ticks * (self.damagePerTick + self.bonusDamagePerTick)
			damageRes = self.dealEffectDamage(dam, event)
			self.miniActivate()




	def canBlockDamageRes(self, damageRes):
		return damageRes.triggerOnAttacked()


	def addBonusDamageOnTick(self, dam):
		self.bonusDamagePerTick += dam

	def _readyInit(self):
		super()._readyInit()
		self.damagePerTick = self.getP4()
		self.blockPerTick = self.getP3()
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)
		self.damageSource.unsetFlag(_R.C("CoreDamageSource").Flags.CanCrit)



_R.reg("res://gd_core_items/Exclusive/SunShield.gd", Exclusive__SunShield)
_R.reg("SunShield", Exclusive__SunShield)
