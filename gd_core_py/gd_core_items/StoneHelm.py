# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class StoneHelm(_R.C("res://gd_core_items/LeatherHelm.gd")):

	resource_path = "res://gd_core_items/StoneHelm.gd"


	def getStunProtectChance(self):
		return self.getChance2()


	def onCombatStart(self):
		self.giveBlock()
		super().onCombatStart()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/StoneHelm.gd", StoneHelm)
_R.reg("StoneHelm", StoneHelm)
