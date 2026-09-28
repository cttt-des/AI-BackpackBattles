# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Coil(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Coil.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numActivations = 0
		self.numBuffs = None
		self.maxActivations = None


	def onPrepare(self):
		self.numActivations = 0


	def onChargeReceived(self, _charge):
		if self.numActivations < self.maxActivations:
			self.numActivations += 1
			self.stealRandomBuff(self.numBuffs)
			if self.numActivations == self.maxActivations:
				self.consumed = True
			self.miniActivate()


































	def _readyInit(self):
		super()._readyInit()
		self.numBuffs = int(self.getP("buffs"))
		self.maxActivations = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/Coil.gd", Exclusive__Coil)
_R.reg("Coil", Exclusive__Coil)
