# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class SpikedShield(_R.C("res://gd_core_items/Shield.gd")):

	resource_path = "res://gd_core_items/SpikedShield.gd"

	def _init_fields(self):
		super()._init_fields()
		self.spikesGiven = 0
		self.spikes = None
		self.maxSpikes = None


	def onPrepare(self):
		self.spikesGiven = 0


	def beforeBlock(self):
		super().beforeBlock()
		spikesLeft = self.maxSpikes - self.spikesGiven
		if spikesLeft > 0:
			spikesToGive = min(spikesLeft, self.spikes)
			self.spikesGiven += spikesToGive
			self.giveSpikes(spikesToGive)


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))
		self.maxSpikes = int(self.getP("maxspikes"))


_R.reg("res://gd_core_items/SpikedShield.gd", SpikedShield)
_R.reg("SpikedShield", SpikedShield)
