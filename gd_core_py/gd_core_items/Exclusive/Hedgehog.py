# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Hedgehog(_R.C("res://gd_core_items/Exclusive/ForestFriend.gd")):

	resource_path = "res://gd_core_items/Exclusive/Hedgehog.gd"

	def _init_fields(self):
		super()._init_fields()
		self.hasActivated = False
		self.spikes = None
		self.damagePerSpike = None
		self.healthThreshold = None


	def doCooldownEffect(self):
		dam = self.descriptor.minDam + self.character().getSpikes() * self.damagePerSpike
		res = self.dealEffectDamage(dam)
		self.activate(res)


	def onPrepare(self):
		self.hasActivated = False
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.hasActivated:
			return

		relHealth = self.character().getRelativeHealth()
		if relHealth < self.healthThreshold:
			self.hasActivated = True
			self.onHPLow(event)


			self.miniActivate()


	def onHPLow(self, event):
		self.giveSpikes(self.spikes, event)
		self.giveBlock(self.getBlock(), True, event)
		self.spawnSpikeParticles()


	def spawnSpikeParticles(self):
		pass


	def getTriggerPriority(self):
		return _R.C("CoreConst").Priority.High + 3

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))
		self.damagePerSpike = self.getP("dam_spikes")
		self.healthThreshold = _div(self.getP('healtht'), 100.0) - 0.0001
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/Hedgehog.gd", Exclusive__Hedgehog)
_R.reg("Hedgehog", Exclusive__Hedgehog)
