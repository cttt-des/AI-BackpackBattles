# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class PoisonGoobert(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/PoisonGoobert.gd"


	def doCooldownEffect(self):
		self.heal()
		self.inflictPoison(self.getP3())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/PoisonGoobert.gd", PoisonGoobert)
_R.reg("PoisonGoobert", PoisonGoobert)
