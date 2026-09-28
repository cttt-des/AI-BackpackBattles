# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Gigawatz(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Gigawatz.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numSpeedboosts = 0
		self.curDamageBonus = 0
		self.maxNumSpeedBoosts = None
		self.speedBonus = None
		self.damageBonus = None
		self.blind = None


	def onPrepare(self):
		self.curDamageBonus = 0
		self.numSpeedboosts = 0


	def onChargeReceived(self, _charge):
		if self.numSpeedboosts < self.maxNumSpeedBoosts:
			self.addSpeed(self.speedBonus)
			self.numSpeedboosts += 1


	def doCooldownEffect(self):
		self.inflictBlind(self.blind)
		dam = self.descriptor.minDam + self.curDamageBonus
		res = self.dealEffectDamage(dam)
		self.activate()
		self.curDamageBonus += self.damageBonus


	def _readyInit(self):
		super()._readyInit()
		self.maxNumSpeedBoosts = int(self.getP("max"))
		self.speedBonus = _div(self.getP('speed'), 100.0)
		self.damageBonus = self.getP("damincrease")
		self.blind = int(self.getP("blind"))
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/Gigawatz.gd", Exclusive__Gigawatz)
_R.reg("Gigawatz", Exclusive__Gigawatz)
