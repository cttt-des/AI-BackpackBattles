# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Hammer(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Hammer.gd"


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit() and self.rollChance():
			self.stun(self.getP_m("dur_stun"), damageRes.event)


	def onFusingAsCatalystFinished(self):
		super().onFusingAsCatalystFinished()
		self.playActivationAnimation()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Hammer.gd", Hammer)
_R.reg("Hammer", Hammer)
