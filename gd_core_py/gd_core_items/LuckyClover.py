# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class LuckyClover(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/LuckyClover.gd"


	def onCombatStart(self):
		self.giveLucky(self.getP1())
		self.consume()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/LuckyClover.gd", LuckyClover)
_R.reg("LuckyClover", LuckyClover)
