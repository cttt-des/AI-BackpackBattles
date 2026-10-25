# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpellScrollFrostbolt(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpellScrollFrostbolt.gd"

	def _init_fields(self):
		super()._init_fields()
		self._maxUses = 0
		self._uses = 0
		self.coldAmount = None

	@property
	def maxUses(self):
		return self._maxUses
	@maxUses.setter
	def maxUses(self, v):
		self._maxUses = int(v)
	@property
	def uses(self):
		return self._uses
	@uses.setter
	def uses(self, v):
		self._uses = int(v)

	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Ice) and not item.isA(self.descriptor)


	def onPrepare(self):
		self.uses = 0
		self.maxUses = int(self.getP1()) + self.getNumAffectedItems()


	def doCooldownEffect(self):
		if self.uses < self.maxUses:
			self.uses += 1
			dam = self.descriptor.minDam
			damageRes = self.dealEffectDamage(dam)
			self.giveStacksTemporary(self.opponent(), _R.C("CoreConst").EventType.Cold, 
				self.coldAmount, self.getP_m("dur_cold"), damageRes.event)
			if self.uses == self.maxUses:
				self.onAfterEffectFinished()
			else:
				self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.coldAmount = int(self.getP3())
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/SpellScrollFrostbolt.gd", Exclusive__SpellScrollFrostbolt)
_R.reg("SpellScrollFrostbolt", Exclusive__SpellScrollFrostbolt)
