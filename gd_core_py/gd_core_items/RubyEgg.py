# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class RubyEgg(_R.C("res://gd_core_items/DragonEgg.gd")):

	resource_path = "res://gd_core_items/RubyEgg.gd"

	def _init_fields(self):
		super()._init_fields()
		self.reflects = None
		self.heat = None


	def onPreCombatStart(self):
		self.giveReflectStacks(self.reflects)


	def onCombatStart(self):
		self.doCooldownEffect(False)



	def doCooldownEffect(self, withReflectStacks=True):
		if withReflectStacks:
			self.giveReflectStacks(self.reflects)
		self.giveHeat(self.heat)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.reflects = int(self.getP1())
		self.heat = int(self.getP3())


_R.reg("res://gd_core_items/RubyEgg.gd", RubyEgg)
_R.reg("RubyEgg", RubyEgg)
