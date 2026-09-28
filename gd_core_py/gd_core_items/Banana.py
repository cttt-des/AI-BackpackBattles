# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Banana(_R.C("res://gd_core_items/Food.gd")):

	resource_path = "res://gd_core_items/Banana.gd"


	def doCooldownEffect(self):
		self.heal()
		self.giveStamina()
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Banana.gd", Banana)
_R.reg("Banana", Banana)
