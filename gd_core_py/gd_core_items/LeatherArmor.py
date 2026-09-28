# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class LeatherArmor(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/LeatherArmor.gd"


	def onPreCombatStart(self):
		self.character().changeDebuffResistStacks(self.getP1())


	def onCombatStart(self):
		self.giveBlock()
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/LeatherArmor.gd", LeatherArmor)
_R.reg("LeatherArmor", LeatherArmor)
