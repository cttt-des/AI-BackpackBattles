# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LightningPotion(_R.C("res://gd_core_items/Potion.gd")):

	resource_path = "res://gd_core_items/Exclusive/LightningPotion.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blind = None
		self.lightningAni = None


	def canAffect_secondary(self, item):
		return item.hasType(_R.C("CoreConst").Type.Holy)


	def onTriggerPotion(self, triggerEvent=None):
		dam = self.descriptor.minDam
		res = self.dealEffectDamage(dam)


		self.giveStacksTemporary(self.opponent(), _R.C("CoreConst").EventType.Blind, 
			self.blind, self.getP_m("dur_blind"), triggerEvent)

		self.heal(self.getP_m("heal") * self.getNumAffectedItems(_R.C("CoreConst").Affected.Secondary))


	def onPrepare(self):
		self.baseCooldownOverride = self.ctx.rng.randf_range(
			self.getBaseCooldownIndex(0), self.getBaseCooldownIndex(1))




	def doCooldownEffect(self):
		self.consumePotion(None, False)
		self.onAfterEffectFinished()


	def fill(self):
		super().fill()


	def empty(self):
		super().empty()

	def _readyInit(self):
		super()._readyInit()
		self.blind = int(self.getP("blind"))
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/LightningPotion.gd", Exclusive__LightningPotion)
_R.reg("LightningPotion", Exclusive__LightningPotion)
