# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Snowcake(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/Snowcake.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cold = None
		self.coldNeeded = None
		self.effectDam = None


	def doCooldownEffect(self):
		self.inflictCold(self.cold)
		if self.opponent().getCold() >= self.coldNeeded:
			self.character().changeEffectDamageFactor(self.effectDam)
			dam = self.descriptor.minDam
			damageRes = self.dealEffectDamage(dam)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.cold = int(self.getP("cold"))
		self.coldNeeded = int(self.getP("coldt"))
		self.effectDam = _div(self.getP('damfactor'), 100.0)
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/Snowcake.gd", Exclusive__Snowcake)
_R.reg("Snowcake", Exclusive__Snowcake)
