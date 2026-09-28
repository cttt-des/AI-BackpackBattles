# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DoomCap(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/DoomCap.gd"

	def _init_fields(self):
		super()._init_fields()
		self.poison = None
		self.healingDebuff = None


	def doCooldownEffect(self):
		self.inflictPoison(self.poison)
		self.opponent().reduceHealingEfficiency(self.healingDebuff)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.poison = int(self.getP("poison"))
		self.healingDebuff = _div(self.getP('healreduction'), 100.0)


_R.reg("res://gd_core_items/Exclusive/DoomCap.gd", Exclusive__DoomCap)
_R.reg("DoomCap", Exclusive__DoomCap)
