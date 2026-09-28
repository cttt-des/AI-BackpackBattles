# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofLife(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofLife.gd"

	amuletColor = Color(0.980469, 0.214478, 0.214478)

	def onPrepare(self):
		self.character().addHealingEfficiency(_div(self.getP('healamp'), 100.0))


	def onCombatStart(self):
		self.giveMaxHealth()
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofLife.gd", Exclusive__AmuletofLife)
_R.reg("AmuletofLife", Exclusive__AmuletofLife)
