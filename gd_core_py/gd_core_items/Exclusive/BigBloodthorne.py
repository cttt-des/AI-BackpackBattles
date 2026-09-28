# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__BigBloodthorne(_R.C("res://gd_core_items/Greatsword.gd")):

	resource_path = "res://gd_core_items/Exclusive/BigBloodthorne.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damPerVampOrSpike = None
		self.regenNeeded = None
		self.vampirism = None
		self.spikes = None


	def onPrepare(self):
		super().onPrepare()
		self.connectForCombat(self.character(), "character_vampirism_changed", "onVampirismChanged")
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def onVampirismChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.damPerVampOrSpike)


	def onSpikesChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.damPerVampOrSpike)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			if self.character().getRegeneration() >= self.regenNeeded:
				self.useRegeneration(self.regenNeeded)
				self.giveVampirism(self.vampirism)
				self.giveSpikes(self.spikes)

	def _readyInit(self):
		super()._readyInit()
		self.damPerVampOrSpike = self.getP("dam")
		self.regenNeeded = int(self.getP("regent"))
		self.vampirism = int(self.getP("vampirism"))
		self.spikes = int(self.getP("spikes"))


_R.reg("res://gd_core_items/Exclusive/BigBloodthorne.gd", Exclusive__BigBloodthorne)
_R.reg("BigBloodthorne", Exclusive__BigBloodthorne)
