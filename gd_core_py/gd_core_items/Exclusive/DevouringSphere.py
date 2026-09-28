# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DevouringSphere(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DevouringSphere.gd"

	def _init_fields(self):
		super()._init_fields()
		self.vampirism = None
		self.blindSpeed = None
		self.coldSpeed = None
		self.dam = None
		self.distortion = None


	def onPrepare(self):
		self.connectForCombat(self.opponent(), "character_cold_changed", "onOpponentColdChanged")
		self.connectForCombat(self.opponent(), "character_blind_changed", "onOpponentBlindChanged")


	def doCooldownEffect(self):
		self.giveVampirism(self.vampirism)
		self.stealLife(self.dam, _div(self.getP_m('lifesteal'), 100.0))
		self.activate()


	def onOpponentColdChanged(self, amount, event):
		self.addSpeed(amount * self.coldSpeed)


	def onOpponentBlindChanged(self, amount, event):
		self.addSpeed(amount * self.blindSpeed)


	def pickup(self, pickupType=GD_DEFAULT):
		if pickupType is GD_DEFAULT:
			pickupType = self.PickupType.Grabbed
		super().pickup(pickupType)


	def drop(self):
		res = super().drop()
		return res

	def _readyInit(self):
		super()._readyInit()
		self.vampirism = int(self.getP("vampirism"))
		self.blindSpeed = _div(self.getP('speed_blind'), 100.0)
		self.coldSpeed = _div(self.getP('speed_cold'), 100.0)
		self.dam = self.getP("dam")
		pass



_R.reg("res://gd_core_items/Exclusive/DevouringSphere.gd", Exclusive__DevouringSphere)
_R.reg("DevouringSphere", Exclusive__DevouringSphere)
