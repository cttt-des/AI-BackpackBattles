# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Pumpkin(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Pumpkin.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heat = None
		self.normalTexture = None


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			res = self.dealDamage()
			self.activate(res)


	def onPrepare(self):
		self.descriptor.activationAni = self.ActivationAni.Throw
		self.connectForCombat(self.ctx.combat, "fatigue_start", "onFatigueStarted")


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.stun(self.getP_m("dur_stun"), damageRes.event)


	def onFatigueStarted(self):
		self.giveHeat(self.heat)
		self.activate()


	def onShopEntered(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.heat = int(self.getP("heat"))
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Pumpkin.gd", Pumpkin)
_R.reg("Pumpkin", Pumpkin)
