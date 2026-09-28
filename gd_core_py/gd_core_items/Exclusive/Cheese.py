# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Cheese(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Exclusive/Cheese.gd"


	def doCooldownEffect(self):
		self.giveMaxHealth()
		self.giveRandomBuffs(self.getP2())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Cheese.gd", Exclusive__Cheese)
_R.reg("Cheese", Exclusive__Cheese)
