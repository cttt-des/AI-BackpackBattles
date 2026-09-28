# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__FireShelly(_R.C("res://gd_core_items/Exclusive/Shelly.gd")):

	resource_path = "res://gd_core_items/Exclusive/FireShelly.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heat = None


	def doCooldownEffect(self):
		self.giveHeat(self.heat)
		super().doCooldownEffect()

	def _readyInit(self):
		super()._readyInit()
		self.heat = int(self.getP("heat"))


_R.reg("res://gd_core_items/Exclusive/FireShelly.gd", Exclusive__FireShelly)
_R.reg("FireShelly", Exclusive__FireShelly)
