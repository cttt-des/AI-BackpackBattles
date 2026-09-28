# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class RubyWhelp(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/RubyWhelp.gd"


	def onPreCombatStart(self):
		self.giveReflectStacks(self.getP2())


	def onCombatStart(self):
		self.giveHeat(self.getP1())
		self.activate(None, False)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/RubyWhelp.gd", RubyWhelp)
_R.reg("RubyWhelp", RubyWhelp)
