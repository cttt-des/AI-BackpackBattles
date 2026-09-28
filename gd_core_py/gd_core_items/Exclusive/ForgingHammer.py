# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ForgingHammer(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/ForgingHammer.gd"


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_empower_changed", "onEmpowerChanged")


	def onEmpowerChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.getP1())

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ForgingHammer.gd", Exclusive__ForgingHammer)
_R.reg("ForgingHammer", Exclusive__ForgingHammer)
