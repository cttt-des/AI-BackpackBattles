# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Thornbloom(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/Thornbloom.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikes = 0
		self.empower = 0
		self.damPerSpike = None


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_empower_changed", "onEmpowerChanged")
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onSpikesChanged(self, amount, _event):
		self.changeVaryingDamage(self.damPerSpike * amount)


	def onEmpowerChanged(self, amount, event):
		if amount > 0:
			self.giveMaxHealth(self.getP_m("maxhealth") * amount, event)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.giveSpikes(self.spikes)

			if self.rollChance():
				self.giveEmpower(self.empower)
			else:
				pass

	def _readyInit(self):
		super()._readyInit()
		self.spikes = self.getP("spikes")
		self.empower = self.getP("empower")
		self.damPerSpike = self.getP("damperspike")


_R.reg("res://gd_core_items/Exclusive/Thornbloom.gd", Exclusive__Thornbloom)
_R.reg("Thornbloom", Exclusive__Thornbloom)
