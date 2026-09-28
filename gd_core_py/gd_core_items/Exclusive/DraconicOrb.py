# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__DraconicOrb(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/DraconicOrb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.counter = 0
		self.activationParticles = None
		self.heatThreshold = 0
		self.spikeRemoval = 0
		self.heatPerSpike = 0


	def onPrepare(self):
		self.counter = 0
		self.connectForCombat(self.character(), "character_heat_changed", "onHeatChanged")


	def onHeatChanged(self, amount, event):
		if self.counter < self.heatThreshold:
			self.counter += amount

			if self.counter >= self.heatThreshold:
				self.giveCritTokens(self.getP2())


	def doCooldownEffect(self):
		oppoSpikes = self.opponent().getSpikes()
		if oppoSpikes > 0:
			event = self.opponent().loseSpikes(self.spikeRemoval, self)
			self.giveHeat(min(oppoSpikes, self.spikeRemoval) * self.heatPerSpike, event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.heatThreshold = self.getP1()
		self.spikeRemoval = self.getP3()
		self.heatPerSpike = self.getP4()


_R.reg("res://gd_core_items/Exclusive/DraconicOrb.gd", Exclusive__DraconicOrb)
_R.reg("DraconicOrb", Exclusive__DraconicOrb)
