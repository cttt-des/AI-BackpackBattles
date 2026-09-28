# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Chainsaw(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Chainsaw.gd"

	def _init_fields(self):
		super()._init_fields()
		self.sawFrame = 0
		self.sawTween = None
		self.removeBuffs = None
		self.slowdown = None
		self.sawAnimation = None

	sawSpeed = 8.0

	def onPrepare(self):
		self.setState(False)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.numCharges > 0:
				self.stealBuffsFraction(self.removeBuffs, 1000)
			else:
				self.removeBuffsFraction(self.removeBuffs, 1000)

			self.reduceSpeed(self.slowdown)


	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)


	def drop(self):
		res = super().drop()

		return res


	def setSawTexture(self):
		self.sawFrame += 1
		self.sawFrame %= 4
		self.updateShadowTexture()


	def onChargeReceived(self, _charge):
		if self.numCharges == 1:
			self.setState(True)
			self.playPickupSound()


	def onChargeLeft(self, _charge):
		if self.numCharges == 0:
			self.setState(False)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, charged):
		if charged:
			pass
		else:
			pass


	def playPickupSound(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.removeBuffs = _div(self.getP('buffs'), 100.0)
		self.slowdown = _div(self.getP('slow'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Chainsaw.gd", Exclusive__Chainsaw)
_R.reg("Chainsaw", Exclusive__Chainsaw)
