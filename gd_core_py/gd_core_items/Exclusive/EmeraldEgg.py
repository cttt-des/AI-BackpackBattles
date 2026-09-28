# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__EmeraldEgg(_R.C("res://gd_core_items/DragonEgg.gd")):

	resource_path = "res://gd_core_items/Exclusive/EmeraldEgg.gd"


	def onCombatStart(self):
		self.doCooldownEffect()


	def doCooldownEffect(self):
		self.giveLucky(self.getP1())
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/EmeraldEgg.gd", Exclusive__EmeraldEgg)
_R.reg("EmeraldEgg", Exclusive__EmeraldEgg)
