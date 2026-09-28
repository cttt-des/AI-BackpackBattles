# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ElectricTorch(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ElectricTorch.gd"

	def _init_fields(self):
		super()._init_fields()
		self.light = None
		self.blindAmount = None
		self.speedBonus = None


	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)



	def drop(self):
		res = super().drop()
		return res


	def canAffect(self, item):
		return item.hasCooldown()


	def onPrepare(self):
		self.setState(False)


	def doCooldownEffect(self):
		duration = self.getP_m("dur_blind")
		self.giveStacksTemporary(self.opponent(), _R.C("CoreConst").EventType.Blind, 
			self.blindAmount, duration)

		self.onAfterEffectFinished()


	def onChargeReceived(self, _charge):
		if self.numCharges == 1:
			self.setState(True)
			for item in _iter(self.getAffectedItems()):
				item.addSpeed(self.speedBonus)


	def onChargeLeft(self, _charge):
		if self.numCharges == 0:
			self.setState(False)
			for item in _iter(self.getAffectedItems()):
				item.reduceSpeed(self.speedBonus)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, charged):
		if charged:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.blindAmount = int(self.getP("blind"))
		self.speedBonus = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ElectricTorch.gd", Exclusive__ElectricTorch)
_R.reg("ElectricTorch", Exclusive__ElectricTorch)
