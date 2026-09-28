# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Snowball(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Snowball.gd"

	def _init_fields(self):
		super()._init_fields()
		self.cold = None
		self.maxHealthReduction = None


	def onPrepare(self):
		self.opponent().changeMaxHealthGain(self.maxHealthReduction)


	def onCombatStart(self):
		self.inflictCold(self.cold)
		self.consume()

	def _readyInit(self):
		super()._readyInit()
		self.cold = int(self.getP("cold"))
		self.maxHealthReduction = _div(-self.getP('healthreduction'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Snowball.gd", Exclusive__Snowball)
_R.reg("Snowball", Exclusive__Snowball)
