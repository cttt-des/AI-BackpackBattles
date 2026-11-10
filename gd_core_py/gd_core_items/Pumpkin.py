# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Pumpkin_2(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Pumpkin.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heat = None
		self.normalTexture = None


	def doCooldownEffect(self):
		if self.useStamina() == _H_1:
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
		self.damageSource = _H_2().setItem(self)



_R.reg("res://gd_core_items/Pumpkin.gd", Pumpkin_2)
_R.reg("Pumpkin", Pumpkin_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StaminaResult.Sufficient
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
_H_2 = _R.C("CoreDamageSource")
