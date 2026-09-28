# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Thornburst(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Thornburst.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationsLeft = 0
		self.spikes = None
		self.uses = None
		self.spikeSpeed = None


	def onPrepare(self):
		self.activationsLeft = self.uses
		self.connectForCombat(self.character(), "character_spikes_changed", "onSpikesChanged")


	def doCooldownEffect(self):

		self.stun(self.getP_m("dur_stun"))
		self.giveSpikes(self.spikes)
		self.activationsLeft -= 1
		if self.activationsLeft == 0:
			self.onAfterEffectFinished()
		else:
			self.activate()


	def onSpikesChanged(self, amount, event):
		self.addSpeed(self.spikeSpeed * amount)

	def _readyInit(self):
		super()._readyInit()
		self.spikes = int(self.getP("spikes"))
		self.uses = int(self.getP("max"))
		self.spikeSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Thornburst.gd", Exclusive__Thornburst)
_R.reg("Thornburst", Exclusive__Thornburst)
