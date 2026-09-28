# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Resistor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Resistor.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heatThreshold = None
		self.heat = None


	def onChargeReceived(self, _charge):
		if self.character().getHeat() < self.heatThreshold:
			self.giveHeat(self.heat)
			self.miniActivate()
		else:
			pass



































	def _readyInit(self):
		super()._readyInit()
		self.heatThreshold = int(self.getP("heatt"))
		self.heat = int(self.getP("heat"))


_R.reg("res://gd_core_items/Exclusive/Resistor.gd", Exclusive__Resistor)
_R.reg("Resistor", Exclusive__Resistor)
