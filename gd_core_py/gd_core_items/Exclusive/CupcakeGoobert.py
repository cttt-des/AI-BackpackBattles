# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__CupcakeGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/Exclusive/CupcakeGoobert.gd"

	def _init_fields(self):
		super()._init_fields()
		self.numBuffs = None


	def doCooldownEffect(self):
		self.heal()
		self.giveMostBuffs(self.numBuffs)





















	def _readyInit(self):
		super()._readyInit()
		self.numBuffs = int(self.getP("buffs"))


_R.reg("res://gd_core_items/Exclusive/CupcakeGoobert.gd", Exclusive__CupcakeGoobert)
_R.reg("CupcakeGoobert", Exclusive__CupcakeGoobert)
