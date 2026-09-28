# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Dagger(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Dagger.gd"


	def prepare(self):
		super().prepare()
		self.connectForCombat(self.opponent(), "character_stunned", "onStun")


	def onStun(self, triggerEvent):
		self.attack(triggerEvent)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Dagger.gd", Dagger)
_R.reg("Dagger", Dagger)
_R.reg("Dagger", Dagger)
