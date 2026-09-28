# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Bloodthorne(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Bloodthorne.gd"

	def _init_fields(self):
		super()._init_fields()
		self.regenNeeded = None
		self.vampirism = None
		self.spikes = None


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onVampirismChanged(self, amount, _event):
		self.changeVaryingDamage(amount)


	def onSpikesChanged(self, amount, _event):
		self.changeVaryingDamage(amount)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			numRegen = self.character().getRegeneration()
			if numRegen >= self.regenNeeded:
				event = self.useRegeneration(self.regenNeeded)
				self.giveVampirism(self.vampirism, event)
				self.giveSpikes(self.spikes, event)

	def _readyInit(self):
		super()._readyInit()
		self.regenNeeded = int(self.getP1())
		self.vampirism = int(self.getP2())
		self.spikes = int(self.getP3())


_R.reg("res://gd_core_items/Bloodthorne.gd", Bloodthorne)
_R.reg("Bloodthorne", Bloodthorne)
