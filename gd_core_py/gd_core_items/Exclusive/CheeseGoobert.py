# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__CheeseGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/Exclusive/CheeseGoobert.gd"


	def doCooldownEffect(self):
		self.giveMaxHealth()
		self.giveRandomBuffs(self.getP3())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/CheeseGoobert.gd", Exclusive__CheeseGoobert)
_R.reg("CheeseGoobert", Exclusive__CheeseGoobert)
