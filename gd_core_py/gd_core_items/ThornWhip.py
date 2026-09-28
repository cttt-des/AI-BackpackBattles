# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class ThornWhip(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/ThornWhip.gd"


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.giveSpikes(1)


	def onSpikesChanged(self, amount, _event):
		self.changeVaryingDamage(self.getP1() * amount)

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/ThornWhip.gd", ThornWhip)
_R.reg("ThornWhip", ThornWhip)
